#include "main.h"
#include "types.h"
#include <stack>
#include <algorithm>

void indentLine(FILE *fp,int level);


Line *lastLine=NULL;
int lastReturn=-1;
int lastReturnSet=-1;
uchar lastLineLevel=-1;
set<string> structsWritten;
void Struct::writeDeclarationC99(FILE *fp)
{
	fprintf(fp,"struct %s;\n",name.c_str());
}
void Struct::writeC99(FILE *fp)
{
	if(structsWritten.find(name)!=structsWritten.end())
		return;
	for(auto it=members.begin();it!=members.end();it++)
	{
		if(it->second->type->isStruct())
		{
			Struct *s=(Struct*)it->second->type;
			if(structsWritten.find(s->name)==structsWritten.end())
			{
				//structsWritten.insert(s->name);
				s->writeC99(fp);
			}
		}

	}
	fprintf(fp,"struct %s\n{\n",name.c_str());
	for(auto it=members.begin();it!=members.end();it++)
	{
		fprintf(fp,"\t%s %s;\n",it->second->type->getC99Type().c_str(),it->first.c_str());
	}
	fprintf(fp,"};\n\n");
	structsWritten.insert(name);
}


void Scope::writeC99( FILE *fp,int level/*=-1*/ )
{
	if(level==-1)
		level=this->level;
	bool written=0;
	for(map<string,Variable*>::iterator it=variables.begin();it!=variables.end();it++)
	{
		Variable *var=it->second;
		if(var->mode&Ob(100000))
			continue;
		indentLine(fp,level);
		fprintf(fp,"%s %s",var->type->getC99Type().c_str(),var->name.c_str());
		if(var->constant!=NULL)
		{
			fprintf(fp," = %s",var->constant->getC99Constant().c_str());
		}
		fprintf(fp,";\n");
		written=1;
	}
	if(written)
	{
		fprintf(fp,"\n");
		lastLineLevel=level;
	}
}

void Function::printC99Declaration(FILE *fp)
{
	if(ret!=NULL)
	{
		fprintf(fp,"%s ",ret->type->getC99Type().c_str());
	}
	else
		fprintf(fp,"void ");

	bool first=1;

	fprintf(fp,"%s ( ",processedFunctionName.c_str());

	first=1;
	for(int i=0;i<name.size();i++)
	{
		if(name[i]->var!=NULL)
		{
			Variable *var=name[i]->var;
			if(first)
				first=0;
			else
				fprintf(fp,", ");
			fprintf(fp,"%s%s%s",var->type->getC99Type().c_str(),(var->mode&Ob(100))?" *":" ",var->name.c_str());
		}
	}
	fprintf(fp," )");
}

void FunctionCall::printC99(FILE *fp)
{
	if(ret!=NULL)
	{
		if(callee->ret!=NULL && ret->name==callee->ret->name)
			lastReturnSet=line->lineNumber;
		fprintf(fp,"%s =  %s( ",ret->nameC99().c_str(),function->processedFunctionName.c_str());
	}
	else
		fprintf(fp,"%s( ",function->processedFunctionName.c_str());

	for(int k=0;k<arguments.size();k++)
	{
		if(ret!=NULL && function->arguments[k]->mode&Ob(100) && arguments[k]->nameC99()==ret->name)
			lastReturnSet=line->lineNumber;

		fprintf(fp,"%s%s%s",(function->arguments[k]->mode&Ob(100))?"&":"",(arguments[k]->mode&Ob(100))?"*":"",arguments[k]->nameC99().c_str());
		if(k==arguments.size()-1)
			fprintf(fp," ");
		else
			fprintf(fp,", ");
	}

	fprintf(fp,");\n");
}


void fixLevels(FILE *fp,int level,Line *line)
{
	if(lastLine!=NULL && lastLineLevel!=level)
	{
		if(lastLineLevel<level)
		{

			for(int i=lastLineLevel;i<level;i++)
			{
				indentLine(fp,i);
				fprintf(fp,"{\n");
			}
			line->scope->writeC99(fp,level);
		}
		else if(lastLineLevel>level)
		{
			for(int i=lastLineLevel-1;i>=level;i--)
			{
				indentLine(fp,i);
				fprintf(fp,"}\n");
			}
		}
	}
}
bool currentlyInline=0;
string inlineReturnVariableName,inlineReturnLabel;
int Line::printC99(FILE *fp,int replacementLevel/*=-1*/)
{
	if(replacementLevel==-1)
		replacementLevel=level;
	int lastLineNumber=lineNumber;
	Line *line=this;
	fixLevels(fp,replacementLevel,line);
	if(lastLine==NULL)
		line->scope->writeC99(fp,replacementLevel);

	if(line->cString.size())
	{
		indentLine(fp,replacementLevel);
		fprintf(fp,"%s\n",line->cString.c_str());
	}
	else if(line->type==LABEL)
	{
		fprintf(fp,"%s:\n",line->processed.c_str());
	}
	else
	{
		string branchName;
		if(line->commands.back()->function->ret!=NULL && line->commands.back()->function->ret->type->is("branch"))
		{
			branchName=line->scope->getTempName("branch");
			indentLine(fp,replacementLevel);
			fprintf(fp,"l%s:;\n",branchName.c_str());
		}
		for(int j=0;j<line->commands.size();j++)
		{
			FunctionCall *call=line->commands[j];
			if(call->function->internalPrintC99!=NULL)
			{	
				indentLine(fp,replacementLevel);
				call->function->internalPrintC99(fp,call);
			}
			else if(call->function->ret!=NULL && call->function->ret->type->is("branch"))
			{
				//string branchName=line->scope->getTempName("branch");
				indentLine(fp,replacementLevel);
				fprintf(fp,"branch_t %s = ",branchName.c_str());
				call->printC99(fp);
				int k;
				indentLine(fp,replacementLevel);
				fprintf(fp,"if( %s.labelId==%i )\n",branchName.c_str(),labels["default"]);
				fflush(fp);
				for(k=line->lineNumber+1;k<lines.size();k++)
				{
					Line *line2=lines[k];
					if(lines[k]->level<level)
						break;
					if(lines[k]->level>level)
					{
						k+=lines[k]->printC99(fp,replacementLevel-line->level+lines[k]->level);
						lastLineNumber=(lines[k]->lineNumber>lastLineNumber)?lines[k]->lineNumber:lineNumber;
					}
					else if(lines[k]->level==level)
					{
						if(lines[k]->type==LABEL || lines[k]->type==LABEL_WITH_CODE)
						{
							fixLevels(fp,replacementLevel,line);
							indentLine(fp,replacementLevel);
							fprintf(fp,"else if( %s.labelId==%i )\n",branchName.c_str(),labels[lines[k]->processed]);
							lastLineLevel=replacementLevel;
						}
						else if(lines[k-1]->type==LABEL_WITH_CODE)
						{

							k+=lines[k]->printC99(fp,replacementLevel+1);
							lastLineNumber=(lines[k]->lineNumber>lastLineNumber)?lines[k]->lineNumber:lineNumber;
						}
						else
						{
							break;
						}
					}
					fflush(fp);
				}
				fixLevels(fp,replacementLevel,line);
				indentLine(fp,replacementLevel);
				fprintf(fp,"if( %s.repeat!=0 ) goto l%s;\n",branchName.c_str(),branchName.c_str());
				lastLineLevel=replacementLevel;
				return lastLineNumber-line->lineNumber;//skipping return call
			}
			else if(call->function->isInline)//todo handle arguments and returns
			{
				currentlyInline=1;
				inlineReturnLabel=scope->getTempName("Label");
				indentLine(fp,replacementLevel);
				fprintf(fp,"{//inline call to %s\n",call->function->processedFunctionName.c_str());
				lastLineLevel=replacementLevel+1;
				if(call->function->ret!=NULL)
				{
					if(call->function->ret->name.empty())
						inlineReturnVariableName=scope->getTempName(call->function->ret->type->name);
					else
						inlineReturnVariableName=call->function->ret->name;
					indentLine(fp,lastLineLevel);
					fprintf(fp,"%s %s;\n",call->function->ret->type->getC99Type().c_str(),inlineReturnVariableName.c_str());
				}
				for(int k=0;k<call->function->arguments.size();k++)
				{
					indentLine(fp,lastLineLevel);
					fprintf(fp,"%s%s%s = %s%s%s;\n",call->function->arguments[k]->type->getC99Type().c_str(),(call->function->arguments[k]->mode&Ob(100))?" *":" ",call->function->arguments[k]->nameC99().c_str()
						,(call->function->arguments[k]->mode&Ob(100))?"&":""
						,(call->arguments[k]->mode&Ob(100))?"*":""
						,call->arguments[k]->nameC99().c_str());
				}

				for(int k=call->function->firstLine->lineNumber;k<=call->function->lastLine->lineNumber;k++)
					lines[k]->printC99(fp,lines[k]->level+replacementLevel);

				fixLevels(fp,replacementLevel+1,line);

				indentLine(fp,replacementLevel+1);
				fprintf(fp,"%s:;\n",inlineReturnLabel.c_str());
				if(call->ret!=NULL)
				{
					indentLine(fp,replacementLevel+1);
					fprintf(fp,"%s = %s;\n",call->ret->nameC99().c_str(),inlineReturnVariableName.c_str());
				}
				lastLineLevel=replacementLevel;
				indentLine(fp,lastLineLevel);
				fprintf(fp,"}\n");
				currentlyInline=0;

				lastLineLevel=replacementLevel;
			}
			else
			{
				indentLine(fp,replacementLevel);
				call->printC99(fp);
			}
		}
	}
	lastLine=line;
	lastLineLevel=replacementLevel;
	lastLineNumber=(line->lineNumber>lastLineNumber)?line->lineNumber:lineNumber;
	return 0;
}//add as necessary http://medinazar.com/C/C_in_21_Days/apb.htm
char *reserved[]=
{
	"asm",
	"auto",
	"break",
	"default",
	"continue"
};
#define RESERVED_NUM 5
void outputC99(FILE *fp)
{
	for(int i=0;i<functions.size();i++)
	{
		Function *func=functions[i];
		for(int j=0;j<func->name.size();j++)
		{
			if(func->name[j]->var==NULL)
			{
				func->processedFunctionName+=func->name[j]->text;
			}
			else
			{
				func->processedFunctionName+=func->name[j]->var->type->name;
			}
		}
		if(!isalpha(func->processedFunctionName[0]))
			func->processedFunctionName.insert(0,"f");

		for(int j=0;j<func->processedFunctionName.size();j++)
		{
			char c=func->processedFunctionName[j];
			string replacement="Q";
			if(!isalnum(c) && c!='_')
			{
				switch(c)
				{
				case '+':
					replacement="plus";
					break;
				case '*':
					replacement="asterisk";
					break;
				case '=':
					replacement="equal";
					break;
				case '<':
					replacement="less";
					break;
				case '(':
					replacement="C";
					break;
				case ')':
					replacement="D";
					break;
				default:
					warn("No known replacement for %c\n",c);
					break;
				}

				replacement.insert(0,"_");
				replacement.push_back('_');
				func->processedFunctionName.erase(j,1);
				func->processedFunctionName.insert(j,replacement);
				j+=replacement.size();
			}
		}
		for(int j=0;j<RESERVED_NUM;j++)
		{
			if(func->processedFunctionName==reserved[j])
				func->processedFunctionName.push_back('_');
		}
	}
	fprintf(fp,"#include <stdio.h>\n\n");
	fprintf(fp,"typedef struct \n{\n\tint labelId;\n\tunsigned char repeat;\n} branch_t;\n\n");
	for(auto it=structs.begin();it!=structs.end();it++)
		it->second->writeDeclarationC99(fp);
	for(auto it=structs.begin();it!=structs.end();it++)
		it->second->writeC99(fp);
	for(int iFunc=0;iFunc<functions.size();iFunc++)
	{
		Function *func=functions[iFunc];
		if(func->isInline)
			continue;
		func->printC99Declaration(fp);
		fprintf(fp,";\n");
	}
	fprintf(fp,"\n\n");
	fprintf(fp,"int main(int argc,char **argv)\n");
	fprintf(fp,"{\n");
	fprintf(fp,"\treturn startint(argc);\n");
	fprintf(fp,"}\n\n");

	for(int iFunc=0;iFunc<functions.size();iFunc++)
	{
		lastReturn=lastReturnSet=-1;
		Function *func=functions[iFunc];
		if(func->isInline)
			continue;
		func->printC99Declaration(fp);
		Variable *ret=func->ret;
		lastLine=func->line;
		lastLineLevel=0;
		lastLine=NULL;
		fprintf(fp,"\n{\n");
		if(func->ret!=NULL)
		{
			if(func->ret->name.size())
			{
				fprintf(fp,"\t%s %s;\n",func->ret->type->getC99Type().c_str(),func->ret->name.c_str());
				lastLineLevel=1;
			}
		}

		if(func->firstLine!=NULL)
			for(int i=func->firstLine->lineNumber;i<=func->lastLine->lineNumber;i++)
			{
				Line *line=lines[i];
				i+=line->printC99(fp);
			}
		if(lastLine!=NULL && lastLineLevel!=1)
		{
			for(int i=lastLineLevel-1;i>=1;i--)
			{
				indentLine(fp,i);
				fprintf(fp,"}\n");
			}
		}

		if(func->ret==NULL || func->ret->name.empty() || lastReturn>lastReturnSet)
			fprintf(fp,"}\n");
		else
		{
			indentLine(fp,1);
			fprintf(fp,"return %s;\n}\n",func->ret->name.c_str());
		}

		fprintf(fp,"\n");
		//fprintf(fp,"}\n\n");
	}
}
vector<string> switchStack;
extern Function *switchEndFunction,*caseFunction,*caseEndFunction,*continueFunction,*continueCaseFunction,*continueDefaultFunction,*defaultFunction;
void returnC99(FILE *fp,FunctionCall *call)
{
	Function *func=call->function;
	if(currentlyInline)
	{
		fprintf(fp,"%s = %s;\ngoto %s;\n",inlineReturnVariableName.c_str(),call->arguments[0]->nameC99().c_str(),inlineReturnLabel.c_str());
	}
	else
	{
		fprintf(fp,"return %s%s;\n",(call->arguments[0]->mode&Ob(100))?"*":"",call->arguments[0]->nameC99().c_str());
		lastReturn=call->line->lineNumber;
	}
}
void returnDefaultC99(FILE *fp,FunctionCall *call)
{
	//checkErrors(call->callee->ret==NULL && call->arguments.size(),"Function does not return a value!");
	checkErrors(call->callee->ret!=NULL && call->callee->ret->name.empty(),"Function does not have an anonymous return variable!");
	if(currentlyInline)
	{
		if(call->callee->ret==NULL)
			fprintf(fp,"goto %s;\n",inlineReturnLabel.c_str());
		else
			fprintf(fp,"%s = %s;\ngoto %s;\n",inlineReturnVariableName.c_str(),call->callee->ret->name.c_str(),inlineReturnLabel.c_str());
	}
	else
	{
		if(call->callee->ret==NULL)
			fprintf(fp,"return;\n");
		else
			fprintf(fp,"return %s%s;\n",(call->callee->ret->mode&Ob(100))?"*":"",call->callee->ret==NULL?"":call->callee->ret->name.c_str());
		lastReturn=call->line->lineNumber;
	}
}
void returnLabelC99(FILE *fp,FunctionCall *call)
{
	checkErrors(call->callee->ret==NULL,"Function does not return a value!");
	checkErrors(!call->callee->ret->type->is("branch"),"Function does not return a branch");
	if(currentlyInline)
	{
		fprintf(fp,"%s = (branch_t){%i /* %s */,%i};\ngoto %s;\n",inlineReturnVariableName.c_str(),labels[call->function->name[1]->text],call->function->name[1]->text.c_str(),inlineReturnLabel.c_str());
	}
	else
	{
		fprintf(fp,"return (branch_t){%i /* %s */,%i};\n",labels[call->function->name[1]->text],call->function->name[1]->text.c_str(),call->function->arguments.size());
		lastReturn=call->line->lineNumber;
	}
}
void gotoC99(FILE *fp,FunctionCall *call)
{
	checkErrors(call->arguments.size()!=1,"goto needs a label");
	fprintf(fp,"goto %s;\n",call->arguments[0]->nameC99().c_str());
}


void switchC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"switch( %s )\n",call->arguments[0]->nameC99().c_str());
	string prefix;
	//find (switchStack,prefix);
	while(find(switchStack.begin(),switchStack.end(),(prefix=string("t_sw")+i2s(rand()%100)+tokenize(call->arguments[0]->nameC99())))!=switchStack.end());
	switchStack.push_back(prefix);
	indentLine(fp,call->line->level);
	fprintf(fp,"{\n");
	FunctionCall *c=new FunctionCall();
	c->function=switchEndFunction;
	c->callee=call->callee;
	c->ret=NULL;
	bool first=1;
	for(int i=call->line->lineNumber+1;i<=call->callee->lastLine->lineNumber+1;i++)
	{
		if(lines[i]->level<call->line->level)
		{
			c->line=lines[i];
			lines[i-1]->commands.insert(lines[i-1]->commands.end(),c);
			break;
		}
		if(lines[i]->level==call->line->level)
		{
			if((lines[i]->commands.size() && (lines[i]->commands[0]->function==caseFunction || lines[i]->commands[0]->function==defaultFunction))/* || (lines[i]->type==Line::LABEL && lines[i]->processed=="default")*/)
			{
				if(first)
					first=0;
				else
				{
					FunctionCall *e=new FunctionCall();
					e->function=caseEndFunction;
					e->callee=call->callee;
					e->ret=NULL;
					e->line=lines[i-1];
					lines[i-1]->commands.push_back(e);
				}
			}
			else
			{
				c->line=lines[i];
				lines[i-1]->commands.insert(lines[i-1]->commands.end(),c);
				break;
			}
		}
	}
}
void switchEndC99(FILE *fp,FunctionCall *call)
{
	lastLineLevel=call->line->level;
	fprintf(fp,"}\n");
	switchStack.pop_back();
}
void caseC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"case %s: ",call->arguments[0]->constant->getC99Constant().c_str());
	fprintf(fp,"case%s%s:\n",call->arguments[0]->constant->getC99Constant().c_str(),switchStack.back().c_str());
}
void caseEndC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"break;\n");
}
void continueC99(FILE *fp,FunctionCall *call)
{
	for(int i=call->line->lineNumber+1;i<=call->callee->lastLine->lineNumber+1;i++)
	{
		if(lines[i]->level<call->line->level)
		{
			if((lines[i]->commands.size() && (lines[i]->commands[0]->function==caseFunction))/* || (lines[i]->type==Line::LABEL && lines[i]->processed=="default")*/)
			{
				fprintf(fp,"goto case%s%s;\n",lines[i]->commands[0]->arguments[0]->constant->getC99Constant().c_str(),switchStack.back().c_str());
				break;
			}
			if((lines[i]->commands.size() && (lines[i]->commands[0]->function==defaultFunction))/* || (lines[i]->type==Line::LABEL && lines[i]->processed=="default")*/)
			{
				fprintf(fp,"goto default%s;\n",switchStack.back().c_str());
				break;
			}
		}
	}
}
void continueDefaultC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"goto default%s;\n",switchStack.back().c_str());
}
void continueCaseC99(FILE *fp,FunctionCall *call)
{
	checkErrors(call->arguments[0]->constant==NULL,"case labels must have a constant input");
	fprintf(fp,"goto case%s%s;\n",call->arguments[0]->constant->getC99Constant().c_str(),switchStack.back().c_str());
}
void defaultC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"default: default%s:\n",switchStack.back().c_str());
}
void setToDefaultC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"%s = %s;\n",call->arguments[0]->nameC99().c_str(),call->arguments[0]->type->getC99Default().c_str());
	NONE;
}
void memberC99(FILE *fp,FunctionCall *call)
{
	NONE;
}