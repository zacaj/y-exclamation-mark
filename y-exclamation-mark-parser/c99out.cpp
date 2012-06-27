#include "main.h"
#include "types.h"

void indentLine(FILE *fp,int level);


Line *lastLine=NULL;
int lastReturn=-1;
int lastReturnSet=-1;
uchar lastLineLevel=-1;

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
		fprintf(fp,"%s =  %s( ",ret->name.c_str(),function->processedFunctionName.c_str());
	}
	else
		fprintf(fp,"%s( ",function->processedFunctionName.c_str());

	for(int k=0;k<arguments.size();k++)
	{
		if(ret!=NULL && function->arguments[k]->mode&Ob(100) && arguments[k]->name==ret->name)
			lastReturnSet=line->lineNumber;

		fprintf(fp,"%s%s%s",(function->arguments[k]->mode&Ob(100))?"&":"",(arguments[k]->mode&Ob(100))?"*":"",arguments[k]->name.c_str());
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
				indentLine(fp,replacementLevel);
				string branchName=line->scope->getTempName("branch");
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
						k+=lines[k]->printC99(fp,replacementLevel+1);
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
							break;
					}
					fflush(fp);
				}
				return lastLineNumber-line->lineNumber;
				/*vector<Line*> l=line->getLabels();
				map<int,vector<Line*>> ls;
				auto ln=l.begin();
				for(int i=line->lineNumber+1;i<lines.size() && (ln)!=l.end() && i<l.back()->lineNumber;i++)
				{
					if(lines[i]->type==Line::LABEL)
						ln++;
					else
					{
						int labelId=0;//default
						if((*ln)->type==Line::LABEL)
						{
							labelId=labels[(*ln)->processed];
						}
						auto it=ls.find(labelId);
						if(it==ls.end())
						{
							vector<Line*> nlns;
							nlns.push_back(lines[i]);
							ls[labelId]=nlns;
						}
						else
							ls[labelId].push_back(lines[i]);
					}
				}

				string branchName=line->scope->getTempName("branch");
				fprintf(fp,"branch_t %s = ",branchName.c_str());
				call->printC99(fp);

				for(auto it=ls.begin();it!=ls.end();it++)
				{
					fixLevels(fp,replacementLevel,line);
					indentLine(fp,replacementLevel);
					if(it==ls.begin())
						fprintf(fp,"if( %s.labelId==%i )\n",branchName.c_str(),it->first);
					else
					{
						fprintf(fp,"else if( %s.labelId==%i )\n",branchName.c_str(),it->first);
						lastLineLevel=replacementLevel;
					}

					for(int k=0;k<it->second.size();k++)
					{
						Line *line=it->second[k];
						line->printC99(fp);
						lastLineNumber=(line->lineNumber>lastLineNumber)?line->lineNumber:lineNumber;
					}
				}

				return lastLineNumber-line->lineNumber;*/
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
					fprintf(fp,"%s%s%s = %s%s%s;\n",call->function->arguments[k]->type->getC99Type().c_str(),(call->function->arguments[k]->mode&Ob(100))?" *":" ",call->function->arguments[k]->name.c_str()
						,(call->function->arguments[k]->mode&Ob(100))?"&":""
						,(call->arguments[k]->mode&Ob(100))?"*":""
						,call->arguments[k]->name.c_str());
				}

				for(int k=0;k<call->function->lines.size();k++)
					call->function->lines[k]->printC99(fp,call->function->lines[k]->level+replacementLevel);

				fixLevels(fp,replacementLevel+1,line);

			/*	if(call->function->ret==NULL || call->function->ret->name.empty() || lastReturn>lastReturnSet)
				{

				}
				else
				{
					indentLine(fp,replacementLevel+1);
					fprintf(fp,"%s = %s;\n",inlineReturnVariableName.c_str(),call->function->ret->name.c_str());
				}*/

				indentLine(fp,replacementLevel+1);
				fprintf(fp,"%s:;\n",inlineReturnLabel.c_str());
				if(call->ret!=NULL)
				{
					indentLine(fp,replacementLevel+1);
					fprintf(fp,"%s = %s;\n",call->ret->name.c_str(),inlineReturnVariableName.c_str());
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


		for(int i=0;i<func->lines.size();i++)
		{
			Line *line=func->lines[i];
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

void returnC99(FILE *fp,FunctionCall *call)
{
	Function *func=call->function;
	if(currentlyInline)
	{
		fprintf(fp,"%s = %s;\ngoto %s;\n",inlineReturnVariableName.c_str(),call->arguments[0]->name.c_str(),inlineReturnLabel.c_str());
	}
	else
	{
		fprintf(fp,"return %s;\n",call->arguments[0]->name.c_str());
		lastReturn=call->line->lineNumber;
	}
}
void returnDefaultC99(FILE *fp,FunctionCall *call)
{
	checkErrors(call->callee->ret==NULL && call->arguments.size(),"Function does not return a value!");
	checkErrors(call->callee->ret!=NULL && call->callee->ret->name.empty(),"Function does not have an anonymous return variable!");
	if(currentlyInline)
	{
		fprintf(fp,"%s = %s;\ngoto %s;\n",inlineReturnVariableName.c_str(),call->callee->ret->name.c_str(),inlineReturnLabel.c_str());
	}
	else
	{
		fprintf(fp,"return %s;\n",call->callee->ret==NULL?"":call->callee->ret->name.c_str());
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
	fprintf(fp,"goto %s;\n",call->arguments[0]->name.c_str());
}
void switchC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"switch( %s )\n",call->arguments[0]->name.c_str());
	indentLine(fp,call->line->level);
	fprintf(fp,"{\n");
	FunctionCall *c=new FunctionCall();
	c->function=switchEndFunction;
	c->callee=call->callee;
	c->ret=NULL;
	bool first=1;
	for(int i=call->line->lineNumber;i<call->callee->lastLine+1;i++)
	{
		if(lines[i]->level<call->line->level)
		{
			c->line=lines[i];
			lines[i]->commands.insert(lines[i]->commands.begin(),c);
			break;
		}
		if(lines[i]->level==call->line->level)
		{
			if(lines[i]->commands[0]->function==caseFunction || (lines[i]->type==Line::LABEL && lines[i]->processed=="default"))
			{
				if(first)
					first=0;
				else
				{
					FunctionCall *e=new FunctionCall();
					e->function=caseEndFunction;
					e->callee=call->callee;
					e->ret=NULL;
					e->line=lines[i];
					lines[i]->commands.push_back(e);
				}
			}
			else
			{
				c->line=lines[i];
				lines[i]->commands.insert(lines[i]->commands.begin(),c);
				break;
			}
		}
	}
}
extern Function *switchEndFunction,*caseFunction,*caseEndFunction;
void switchEndC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"}\n",call->arguments[0]->name.c_str());
	
}
void caseC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"case %s:\n",call->arguments[0]->constant->getC99Constant().c_str());
}
void caseEndC99(FILE *fp,FunctionCall *call)
{
	fprintf(fp,"break;\n");
}