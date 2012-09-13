#include <stdio.h>
#include <string>
#include <time.h>
using namespace std;
#include "file.h"
#include "common.h"
#include "types.h"
#include <stdarg.h>
#include "main.h"

string tempPath;
int realLineNumber=0;
int lineIndent=0;
vector<int> lineIndentLevel;
map<string,Struct*> structs;
void checkErrors(bool isError,string description="")
{
	if(isError)
	{
		error("ERROR %i: %s\n",realLineNumber,description.c_str());
	}
}

bool handlePotentialInterpreterOption(string option)
{
	if(option=="uses")
	{

		return 1;
	}
	return 0;
}


class Function;
map<string,vector<Function*>> identifiers;

class Line;

vector<Function*> functions;
Function *currentFunction=NULL;
void initCallToken(CallToken &token)
{
	token.aPossibleFunctions=0;
	token.nPossibleFunctions=0;
	token.possibleFunctions=NULL;
	token.possibilities=0;
	token.possibleVariable=NULL;
	token.newVariable=0;
	token.newVariablePtr=NULL;
	token.label=NULL;
	token.str=NULL;
}
void insertFunction(CallToken &token,Function *func)
{
	if(token.aPossibleFunctions==0)
	{
		token.aPossibleFunctions=4;
		token.nPossibleFunctions=1;
		token.possibleFunctions=(Function**)malloc(sizeof(Function*)*token.aPossibleFunctions);
		token.possibleFunctions[0]=func;
		return;
	}
	for(int i=0;i<token.nPossibleFunctions;i++)
	{
		if(token.possibleFunctions[i]==func)
			return;
	}
	if(token.nPossibleFunctions+1>=token.aPossibleFunctions)
	{
		token.aPossibleFunctions*=2;
		token.possibleFunctions=(Function**)realloc(token.possibleFunctions,sizeof(Function*)*token.aPossibleFunctions);
	}
	token.possibleFunctions[token.nPossibleFunctions++]=func;
}


class Line;
Function *startFunction=NULL;
vector<Line*> lines;


void debugIntermediateForm(FILE *fp);
void printLlvmIrCode(FILE *fp);
void outputC99(FILE *fp);
extern int lastReturn;
extern bool currentlyInline;
extern string inlineReturnVariableName,inlineReturnLabel;

void parseSourceLine(string str)
{
	if(!str.empty())
	{
		removeLeadingTrailingSpaces(str);
		Line *line=new Line(str,realLineNumber);
		if(line->type==Line::EMPTY)
			delete line;
		else
		{
		//	lines.push_back(line);
		}
	}
	realLineNumber++;
}
Function *switchEndFunction,*caseFunction,*caseEndFunction,*continueFunction,*continueCaseFunction,*continueDefaultFunction,*defaultFunction,*forFunction,*whileFunction;
int main(_In_ int _Argc, char **argv)
{
	initCommon();
	types["int"]=new Int;
	types["string"]=new String;
	types["bool"]=new Bool;
	types["branch"]=new Branch;
	types["Label"]=new Label;
	//types["var"]=new Var;
	int start=time(NULL);
	FILE *fp=fopen("../y! code/main.y","r");
	addLabel("default",NULL);
	addLabel("else",NULL);
	addLabel("none",NULL);
	realLineNumber=1;
	while(!feof(fp))
	{
		string str=readTo(fp,'\n');
		parseSourceLine(str);
	}
	fclose(fp);

	{
		functions.push_back(new Function("inline return"));
		functions.back()->internalPrintC99=returnDefaultC99;

		for(auto it=labels.begin();it!=labels.end();it++)
		{
			functions.push_back(new Function("inline return "+it->first+""));
			functions.back()->internalPrintC99=returnLabelC99;

			functions.push_back(new Function("inline return "+it->first+" (int)r"));
			functions.back()->internalPrintC99=returnLabelC99;//todo change for optional?
		}

		
		for(auto it=types.begin();it!=types.end();it++)
		{
			functions.push_back(new Function("inline return ("+it->first+")r"));
			functions.back()->internalPrintC99=returnC99;

			parseSourceLine("r("+it->first+") ( ("+it->first+")a )");
			parseSourceLine("\treturn a");


			functions.push_back(new Function("inline o("+it->first+")v = default"));
			functions.back()->internalPrintC99=setToDefaultC99;


			parseSourceLine("r(")
		}
		//functions.push_back(new Function("inline return (var)r"));
		//functions.back()->internalPrintC99=returnC99;

		//parseSourceLine("r(var) ( (var)a )");
		//parseSourceLine("\treturn a");

		functions.push_back(new Function("inline goto (Label)label"));
		functions.back()->internalPrintC99=gotoC99;

		{
			functions.push_back(new Function("switch (int)var"));
			functions.back()->internalPrintC99=switchC99;

			functions.push_back(new Function("case (int)var"));
			functions.back()->internalPrintC99=caseC99;
			caseFunction=functions.back();
			functions.push_back(new Function("switchEnd"));
			functions.back()->internalPrintC99=switchEndC99;
			switchEndFunction=functions.back();
			functions.push_back(new Function("caseEnd"));
			functions.back()->internalPrintC99=caseEndC99;
			caseEndFunction=functions.back();
			functions.push_back(new Function("continue"));
			functions.back()->internalPrintC99=continueC99;
			continueFunction=functions.back();
			functions.push_back(new Function("continue default"));
			functions.back()->internalPrintC99=continueDefaultC99;
			continueDefaultFunction=functions.back();
			functions.push_back(new Function("continue case (int)i"));
			functions.back()->internalPrintC99=continueCaseC99;
			continueCaseFunction=functions.back();
			functions.push_back(new Function("default"));
			functions.back()->internalPrintC99=defaultC99;
			defaultFunction=functions.back();
		}
		functions.push_back(new Function("inline r(branch) for (var)a ; (var)b ; (var)c"));
		forFunction=functions.back();

		parseSourceLine("r(branch) while (bool)is");
		parseSourceLine("c	if(is)");
		parseSourceLine("\t\treturn default 1");
		parseSourceLine("\treturn none");
		whileFunction=functions.back();

		for(auto it=structs.begin();it!=structs.end();it++)
		{
			Struct *s=it->second;
			for(auto it2=s->members.begin();it2!=s->members.end();it2++)
			{
				parseSourceLine("r("+it2->second->type->name+") ("+s->name+")this . "+it2->first+" p = 9999999");
				functions.back()->internalPrintC99=memberC99;
			}
		}
	}

	for(int i=0;i<lines.size();i++)
	{
		if((lines[i]->type==Line::CODE || lines[i]->type==Line::CODE_WITH_OPTIONS) && !lines[i]->split)
			lines[i]->splitCommands(lines[i]->processed);
	}
	vector<Function*> &mainCandidates=identifiers.find("start")->second;
	for(int i=0;i<mainCandidates.size();i++)
	{
		if(mainCandidates[i]->name.size()==2 && mainCandidates[i]->arguments.size()==1 && mainCandidates[i]->arguments[0]->type==getType("int")
			&& mainCandidates[i]->arguments[0]->name=="nArgument")//good enough
			startFunction=mainCandidates[i];
	}
	checkErrors(startFunction==NULL,"r(int) start (int)nArgument not found\n");
	//return 0;
	fp=fopen("../y! code/main.c","w");
	//fp=fopen("../y! code/main.ll","w");
	//fp=fopen("../y! code/main.yif","w");
	//debugIntermediateForm(fp);
	//printLlvmIrCode(fp);
	outputC99(fp);
	fclose(fp);
}
map<string,int> labels;
map<string,set<Function*>> labelLocations;
void addLabel( string label ,Function *location)
{
	auto it=labels.find(label);
	if(it==labels.end())
		labels[label]=labels.size();
	auto it2=labelLocations.find(label);
	if(it2==labelLocations.end())
	{
		set<Function*> locations;
		locations.insert(location);
		labelLocations[label]=locations;
	}
	else
		it2->second.insert(location);
}
Struct *currentStruct=NULL;
Line::Line( string str,uint _lineNumber ):originalLineNumber(_lineNumber)
{
	split=0;
	lineNumber=lines.size();
	removeLeadingTrailingSpaces(str);
	scope=NULL;
	original=str;
	parentFunction=NULL;
	parentStruct=NULL;

	spos singleLineCommentPos=str.find("//");
	if(singleLineCommentPos!=npos)
	{
		comment=str.substr(singleLineCommentPos,str.size()-singleLineCommentPos+1);
		str.erase(singleLineCommentPos,str.size()-singleLineCommentPos+1);
	}

	if(find_not(str,invisibleCharacers)!=str.size())
	{
		size_t tab=str.find(9);
		processed=str;
		bool dontAdd=0;
		string newString;
		if(tab==string::npos)//function declaration or option or struct
		{
			level=0;
			spos firstSpace=str.find(' ');
			string first;
			if(firstSpace!=npos)
			{
				first=str.substr(0,firstSpace);
			}
			if(handlePotentialInterpreterOption(first))
			{
				type=INTERPRETER_COMMAND;
				lines.push_back(this);
				return;
			}
			
			spos endOfFirstId=find_not(str,lowerLetters+upperLetters+numerals+"_");
			if(endOfFirstId!=str.size() && str[endOfFirstId]==':')//todo code after label
			{
				type=LABEL;
				processed=str.substr(0,endOfFirstId);
				addLabel(processed,currentFunction);
				checkErrors(lineNumber==0,"Cannot have a label on the first line");
				level=lines[lineNumber-1]->level;
			}
			else if(first=="struct")
			{
				Struct *strct=new Struct;
				spos startOfName=find_not(str," ",firstSpace);
				checkErrors(startOfName==str.size(),"struct has no name");
				spos endOfName=find_not(str,upperLetters+lowerLetters+numerals+"_",startOfName);
				strct->name=str.substr(startOfName,endOfName-startOfName+1);
				removeLeadingTrailingSpaces(strct->name);
				types[strct->name]=strct;
				type=STRUCT;
				currentStruct=strct;
				currentFunction=NULL;
				structs[strct->name]=strct;
				return;
			}
			else
			{
				functions.push_back(new Function(str));
				functions.back()->line=this;
				scope=new Scope(functions.back());
				scope->level=1;
				type=FUNCTION_DECLARATION;
				currentFunction=functions.back();
				currentStruct=NULL;
				lines.push_back(this);
				return;
			}
		}
		if(currentStruct!=NULL)
		{
			parentStruct=currentStruct;
			size_t t=str.find_first_not_of(9);
			currentStruct->addMember(str.substr(t,str.size()-t+1));
			type=STRUCT_MEMBER;
		}
		if(currentFunction!=NULL)
		{
			parentFunction=currentFunction;
//			currentFunction->lines.push_back(this);
			if(currentFunction->firstLine==NULL)
				currentFunction->firstLine=this;
			currentFunction->lastLine=this;
			size_t commandStart=str.find_first_not_of(9,tab);
			if(commandStart!=npos)
			{
				level=commandStart-tab;
				if(lineIndentLevel.size() && level<lineIndentLevel.back())
				{
					lineIndentLevel.pop_back();
					lineIndent--;
				}
				//level+=lineIndent;
			}
			if(tab!=0 && tab!=npos)
			{
				//todo handle options
				type=CODE_WITH_OPTIONS;
				if(str[0]=='c')
				{
					cString=str.substr(commandStart,str.size()-commandStart+1);
				}
			}
			else if(tab!=npos)
			{
				type=CODE;
				spos endOfFirstId=find_not(str,lowerLetters+upperLetters+numerals+"_",commandStart);
				if(endOfFirstId!=str.size() && str[endOfFirstId]==':')//todo code after label
				{
					type=LABEL;
					processed=str.substr(commandStart,endOfFirstId-commandStart);
					addLabel(processed,parentFunction);
					if(find_not(str,invisibleCharacers,endOfFirstId+1)!=str.size())//code after label
					{
						for(int i=0;i<level;i++)
							newString.push_back('\t');
						newString+=str.substr(endOfFirstId+1,str.size()-endOfFirstId);
						//lineIndent++;
						//lineIndentLevel.push_back(level);
						dontAdd=1;
						type=LABEL_WITH_CODE;
					}
				}
			}
			if(type!=LABEL && commandStart!=npos && type!=LABEL_WITH_CODE)
			{
				processed.erase(processed.begin(),processed.begin()+commandStart);
				checkErrors(lineNumber==0,"Code outside of a function");
			}

			{
				if(lines[lineNumber-1]->type==LABEL_WITH_CODE && lines[lineNumber-1]->level<=level)
				{
					scope=new Scope(*lines[lineNumber-1]->scope);
					scope->parent=lines[lineNumber-1]->scope;
					scope->level=level;

				}
				else
				for(int i=lineNumber-1;i>=0;i--)
				{
					if(lines[i]->type!=CODE && lines[i]->type!=CODE_WITH_OPTIONS && lines[i]->type!=FUNCTION_DECLARATION && lines[i]->type!=LABEL && lines[i]->type!=LABEL_WITH_CODE)
						continue;
					if(lines[i]->level==level && lines[i]->type!=LABEL_WITH_CODE && lines[i-1]->type!=LABEL_WITH_CODE)
					{
					/*	if(lines[i]->type==LABEL_WITH_CODE)
						{
							scope=new Scope(*lines[i]->scope);
							scope->parent=lines[i]->scope;
							scope->level=level;
							break;
						}
						else*/
						{
							scope=lines[i]->scope;
							break;
						}
					}
					else if(lines[i]->level<level)
					{
						scope=new Scope(*lines[i]->scope);
						scope->parent=lines[i]->scope;
						scope->level=level;
						break;
					}
				}
				checkErrors(scope==NULL,"Code outside of a function");
			}
		}
		lines.push_back(this);
		if(dontAdd)
			new Line(newString,originalLineNumber);
	}
	else
		type=EMPTY;
}

 Line::Line( vector<FunctionCall*> &call,Scope *_scope,Function *_parent,int _level)
{
	commands=call;
	scope=_scope;
	parentFunction=_parent;
	level=_level;
	type=CODE;
	split=1;
}

void Line::splitCommands( string str )
{
	if(cString.size())
		return;
	vector<CallToken> call;
	spos pos=0;
	while(pos<str.size())
	{
		char lastC=0;
		while(pos<str.size() && str[pos]==' ') pos++;//skip duplicate whitespace
		spos endOfId=pos;
		//if(endOfId==npos)
		while(endOfId<str.size())
		{
			if(str[endOfId]==' ')
				break;
			int a=isalnum(str[endOfId]);
			int b=isalnum(lastC);
			if(lastC!=0 && (a==0 || b==0))
				break;
			lastC=str[endOfId];
			endOfId++;
		}
		string id=str.substr(pos,endOfId-pos);
		removeLeadingTrailingSpaces(id);
		if(find_not(id,invisibleCharacers)==id.size())
		{
			pos++;
			continue;
		}
		CallToken token;
		initCallToken(token);

		if(id[0]=='\"')//todo set variables for literals
		{
			spos startOfString=pos;
			while(pos<str.size()-1)
			{
				pos=find(str,"\"",pos+1);
				if(str[pos-1]!='\\')
					break;
			}
			checkErrors(pos==str.size(),"No closing \" found ");
			string stringContent=str.substr(startOfString,pos-startOfString+1);
			pos++;
			id=scope->getTempName("string");
			token.possibleVariable=new Variable(id,getType("string"));
			String *cString=new String;
			cString->value=stringContent;
			token.possibleVariable->constant=cString;
			token.possibleVariable->mode|=Ob(10000);
			token.str=cstr(id);
			token.possibilities++;
			scope->addVariable(token.possibleVariable);
		}
		else if(isdigit(id[0]) || id[0]=='-')//todo variables that start with numbers?
		{
			string num;
			while(pos<str.size() && (isdigit(str[pos]) || id[0]=='-'))
				num.push_back(str[pos++]);
			id=scope->getTempName("int","_"+num);
			token.possibleVariable=new Variable(id,getType("int"));
			Int *cInt=new Int();
			cInt->value=atoi(num.c_str());
			token.possibleVariable->constant=cInt;
			token.possibleVariable->mode|=Ob(10000);
			token.possibilities++;
			token.str=cstr(id);
			scope->addVariable(token.possibleVariable);
		}
		else
		{
			pos=endOfId;
			map<string,vector<Function*>>::iterator fit=identifiers.find(id);
			//checkError(fit==identifiers.end() && !Variable::isValidName(id),"%s not found",id.c_str());
			if(fit!=identifiers.end())
			{
				vector<Function*> &functions=fit->second;
				for(int i=0;i<functions.size();i++)
				{
//					token.possibleFunctions.insert(functions[i]);
					insertFunction(token,functions[i]);
					//possibleFunctions.insert(functions[i]);
				}
				if(token.nPossibleFunctions)
				{
					token.str=cstr(id);
					token.possibilities++;
				}
			}
			Variable *var=scope->getVariable(id);
			if(var!=NULL)
			{
				token.str=cstr(id);
				token.possibleVariable=var;
				token.possibilities++;
			}
			else if(Variable::isValidName(id))
			{
				token.newVariable=1;
				token.str=cstr(id);
				token.possibilities++;
			}

			if(labels.find(id)!=labels.end())
			{
				if(labelLocations[id].find(parentFunction)!=labelLocations[id].end())
				{
					token.label=cstr(id);
					token.str=cstr(id);
					token.possibilities++;
				}
			}
		}
		checkError(token.possibilities==0,"%s not found\n",id.c_str());
		call.push_back(token);
	}
	debug("Processed line %i\n",originalLineNumber);
	vector<LinePossibility*> &possibilities=findCommands(call);
	checkErrors(possibilities.size()==0,"no function specified");
	checkErrors(possibilities.size()>=2,"ambiguous call");
	for(int i=0;i<possibilities[0]->call.size();i++)
	{
		for(int j=0;j<possibilities[0]->call[i]->arguments.size();j++)
		{
			if(possibilities[0]->call[i]->arguments[j]->mode&WASANEWVARIABLE)
			{
				scope->addVariable(possibilities[0]->call[i]->arguments[j]);
				possibilities[0]->call[i]->arguments[j]->mode^=WASANEWVARIABLE;
			}
		}
	}
	commands.insert(commands.begin(),possibilities[0]->call.begin(),possibilities[0]->call.end());
	if(possibilities[0]->forLoopIncr.size())
	{
		int i;
		Line *lastLine=NULL;
		for(i=lineNumber+1;i<=parentFunction->lastLine->lineNumber;i++)
			if(lines[i]->level<=level)
				break;
			else
				lastLine=lines[i];
		if(lastLine==NULL)
		{
			Line *line;
			line=new Line(possibilities[0]->forLoopIncr,scope,parentFunction,level+1);
			lines.insert(lines.begin()+lineNumber+1,line);
			fixLineNumbers();
		}
		else
		{
			Scope *sc;
			if(lastLine->level==level+1)
			{
				sc=lastLine->scope;
			}
			else
			{
				sc=lastLine->scope;
				while(sc->level!=level+1)
				{
					sc=sc->parent;
				}
			}
			Line *line=new Line(possibilities[0]->forLoopIncr,sc,parentFunction,level+1);
			lines.insert(lines.begin()+lastLine->lineNumber+1,line);
			
			fixLineNumbers();

		}

		{
			Line *line=new Line(possibilities[0]->forLoopInit,scope,parentFunction,level);
			lines.insert(lines.begin()+lineNumber,line);
			fixLineNumbers();
		}
	}
	NONE;
	split=1;
	for(int i=0;i<call.size();i++)
	{
		free(call[i].possibleFunctions);
	}
}

void fixLineNumbers()
{
	for(int j=0;j<lines.size();j++)
		lines[j]->lineNumber=j;
}
vector<LinePossibility*> Line::findCommands( vector<CallToken> &call )
{
	
	vector<CallToken> attempt;
	vector<LinePossibility*> possibilities;
	parseCode(call,0,possibilities,attempt);
	string failReason;
	for(int i=possibilities.size()-1;i>=0;i--)
	{
#define FAIL(reason) { failReason=reason; goto fail; }
		LinePossibility &linePossibility=*possibilities[i];
		
		vector<IndependantFunction> independantFunctionPossibilities;
		vector<CallToken> &possibility=linePossibility.p;
		string correct="vffvfffvvffvf";
		if(correct.size()==call.size())
		{
			int j=0;
			for(;j<correct.size();j++)
			{
				switch(correct[j])
				{
					case 'v':
						if(possibility[j].possibleVariable==NULL)
							j=99;
						break;
					case 'f':
						if(possibility[j].nPossibleFunctions==0)
							j=100;
						break;
				}
			}
			if(j<99)
				NONE;
		}	
		int id=linePossibility.id;
		{
			if(possibility[0].nPossibleFunctions)
			{
				if(strcmp(possibility[0].str,"for")==0 && possibility[0].possibleFunctions[0]==forFunction)
				{
					vector<int> semicolons;
					for(int j=1;j<possibility.size();j++)
					{
						if(possibility[j].nPossibleFunctions && possibility[j].possibleFunctions[0]==forFunction)
						{
							if(strcmp(possibility[j].str,";")==0)
								semicolons.push_back(j);
							else
								FAIL("cannot have a for loop in a for loop declaration");
						}
					}
					if(semicolons.size()!=2)
						FAIL("a for loop requires two semicolons");

					{//init				
						vector<CallToken> iCall;

						for(int j=1;j<semicolons[0];j++)
						{
							iCall.push_back(possibility[j]);
						}
						vector<LinePossibility*> &possibilities=findCommands(iCall);
						if(possibilities.size()!=1)
							FAIL("bad possibilities");
						vector<FunctionCall*> &iCmd=possibilities[0]->call;
						for(int j=0;j<iCmd.size();j++)
						{
							FunctionCall *call=iCmd[j];
							for(int k=0;k<call->arguments.size();k++)
							{
								if(call->arguments[k]->mode&WASANEWVARIABLE)
								{
									for(int l=semicolons[0]+1;l<possibility.size();l++)
									{
										if(possibility[l].newVariable && strcmp(possibility[l].str,call->arguments[k]->name.c_str())==0)
										{
											possibility[l].newVariable=0;
											possibility[l].possibleVariable=call->arguments[k];
										}
									}
									NONE;//	iCmd[j].newVariablePtr=new Variable(iCmd[j].str,func->name[k]->var->type);
								}
							}
						}
						//linePossibility.call.insert(linePossibility.call.begin(),iCmd.begin(),iCmd.end());
						linePossibility.forLoopInit=iCmd;
					}
					{//increment		
						vector<CallToken> iCall;
						for(int j=semicolons[1]+1;j<possibility.size();j++)
						{
							iCall.push_back(possibility[j]);
						}
						vector<LinePossibility*> &possibilities=findCommands(iCall);
						if(possibilities.size()!=1)
							FAIL("bad possibilities 2");
						vector<FunctionCall*> &iCmd=possibilities[0]->call;
						linePossibility.forLoopIncr.insert(linePossibility.forLoopIncr.begin(),iCmd.begin(),iCmd.end());
					}

					possibility.erase(possibility.begin()+semicolons[1],possibility.end());
					possibility.erase(possibility.begin(),possibility.begin()+semicolons[0]+1);
					CallToken whileToken;
					initCallToken(whileToken);

					whileToken.possibilities=1;
					whileToken.str="while";
					insertFunction(whileToken,whileFunction);
					//whileToken.possibleFunctions.insert(whileFunction);
					whileToken.newVariablePtr=NULL;
					possibility.insert(possibility.begin(),whileToken);
					

					NONE;
				}
			}
		}
		independantFunctionPossibilities.clear();
		int j;
		for(j=0;j<possibility.size();j++)//go thru all ids
		{
			if(possibility[j].nPossibleFunctions)//if its a funcion id
			{
				Function *func=possibility[j].possibleFunctions[0];
				//find the same id in the function
				int functionTokenIndexInFunction=0;
				for(;functionTokenIndexInFunction<func->name.size();functionTokenIndexInFunction++)
				{
					if(func->name[functionTokenIndexInFunction]->text==possibility[j].str)
						break;
				}
				checkErrors(functionTokenIndexInFunction==func->name.size(),"internal error 1");

				int k;
				for(k=0;k<func->name.size();k++)
				{
					if(j-functionTokenIndexInFunction+k>=possibility.size())
						break;
					if(func->name[k]->var!=NULL)
					{
						if(possibility[j-functionTokenIndexInFunction+k].newVariable)//output
						{
							if(!(func->name[k]->var->mode&Ob(100)))
								break;
							else
							{
								possibility[j-functionTokenIndexInFunction+k].newVariablePtr=new Variable(possibility[j-functionTokenIndexInFunction+k].str,func->name[k]->var->type);
								possibility[j-functionTokenIndexInFunction+k].newVariablePtr->mode|=WASANEWVARIABLE;
							}	
						}
						else if(possibility[j-functionTokenIndexInFunction+k].label!=NULL)
						{
							if(func->name[k]->var==NULL)
								break;
							if(!func->name[k]->var->type->is("Label"))
								break;

						}
						else
						{
							if(possibility[j-functionTokenIndexInFunction+k].possibleVariable==NULL)
								break;
							if(!possibility[j-functionTokenIndexInFunction+k].possibleVariable->type->is(func->name[k]->var->type->name))
								break;
						}
					}
					else
					{
						if(!possibility[j-functionTokenIndexInFunction+k].nPossibleFunctions || possibility[j-functionTokenIndexInFunction+k].possibleFunctions[0]!=func ||func->name[k]->text!=possibility[j-functionTokenIndexInFunction+k].str)
							break;
					}
				}
				if(k==func->name.size())//match
				{
					IndependantFunction indf;
					indf.func=func;
					indf.start=j-functionTokenIndexInFunction;
					indf.end=j-functionTokenIndexInFunction+func->name.size();
					independantFunctionPossibilities.push_back(indf);//todo search for duplicates
				}
			}
		}
		if(independantFunctionPossibilities.empty())
			FAIL("no independent functions");

		float highestPrecedence=-9999999999999;
		int highestPrecedenceIndex=-1;
		for(int j=0;j<independantFunctionPossibilities.size();j++)
		{
			if(independantFunctionPossibilities[j].func->precedence>highestPrecedence)//change to >= to go rl in case of == p
			{
				highestPrecedence=independantFunctionPossibilities[j].func->precedence;
				highestPrecedenceIndex=j;
			}
		}
		checkErrors(highestPrecedenceIndex==-1,"internal error 3");
		IndependantFunction &indf=independantFunctionPossibilities[highestPrecedenceIndex];
		if(indf.func->internalPrintC99==memberC99)
		{
			checkErrors(possibility[indf.start].possibleVariable==NULL,"internal error 43");
			checkErrors(possibility[indf.end-1].nPossibleFunctions==0,"internal error 443");
			checkErrors(indf.end-indf.start!=3,"internal error 3454");
			checkErrors(!possibility[indf.start].possibleVariable->type->isStruct(),"internal error 345");
			Struct *stct=(Struct*)possibility[indf.start].possibleVariable->type;
			Variable *svar=possibility[indf.start].possibleVariable;
			checkError(stct->members.find(possibility[indf.end-1].str)==stct->members.end(),"Struct %s (%s) does not have a member named %s",possibility[indf.start].str,stct->name.c_str(),possibility[indf.end-1].str);
			Type *varType=stct->members.find(possibility[indf.end-1].str)->second->type;
			Variable *var=new Variable(possibility[indf.end-1].str,varType);
			var->parent=svar;
			var->mode=Ob(10000000);
			possibility.erase(possibility.begin()+indf.start,possibility.begin()+indf.end);
			CallToken token;
			initCallToken(token);
			
			token.str=cstr(svar->name);
			token.possibleVariable=var;
			token.newVariablePtr=NULL;
			token.newVariable=NULL;
			
			possibility.insert(possibility.begin()+indf.start,token);
			i++;
		}
		else if(indf.start==0 && indf.end==possibility.size())//only this call
		{
			{
				FunctionCall *fcall=new FunctionCall();
				fcall->function=indf.func;
				fcall->ret=NULL;
				fcall->callee=parentFunction;
				fcall->line=this;
				for(int j=indf.start;j<indf.end;j++)
				{
					if(possibility[j].possibleVariable!=NULL)
						fcall->arguments.push_back(possibility[j].possibleVariable);
					else if(possibility[j].newVariablePtr!=NULL)
						fcall->arguments.push_back(possibility[j].newVariablePtr);
					else if(possibility[j].label!=NULL)
						fcall->arguments.push_back(new Variable(possibility[j].label,getType("Label")));
				}
				checkErrors(fcall->arguments.size()!=fcall->function->arguments.size(),"internal error 4");
				linePossibility.call.push_back(fcall);
			}
		}
		else//simplify the call
		{
			//checkError(indf.func->ret==NULL,"%s does not return a value")
			if(indf.func->ret==NULL)
				FAIL((indf.func->original+" does not return a value"));
			Variable *var=new Variable(scope->getTempName(indf.func->ret->type->name,tokenize(indf.func->original)),indf.func->ret->type);
			var->mode|=Ob(10000000);
			scope->addVariable(var);
			{
				FunctionCall *fcall=new FunctionCall();
				fcall->function=indf.func;
				fcall->ret=var;
				fcall->line=this;
				fcall->callee=parentFunction;
				for(int j=indf.start;j<indf.end;j++)
				{
					if(possibility[j].possibleVariable!=NULL)
						fcall->arguments.push_back(possibility[j].possibleVariable);
					else if(possibility[j].newVariablePtr!=NULL)
						fcall->arguments.push_back(possibility[j].newVariablePtr);
					else if(possibility[j].label!=NULL)
						fcall->arguments.push_back(new Variable(possibility[j].label,getType("Label")));
				}
				checkErrors(fcall->arguments.size()!=fcall->function->arguments.size(),"internal error 4");
				linePossibility.call.push_back(fcall);
			}
			possibility.erase(possibility.begin()+indf.start,possibility.begin()+indf.end);
			CallToken token;
			initCallToken(token);

			token.str=cstr(var->name);
			token.possibleVariable=var;
			token.newVariablePtr=NULL;
			token.newVariable=0;
			possibility.insert(possibility.begin()+indf.start,token);
			i++;
		}


		continue;//skip fail if got to here

fail:
		for(int j=0;j<linePossibility.call.size();j++)//remove unused temp vars
		{
			//for(int k=0;k<linePossibility.call[j]->arguments.size();k++)
			{
				if(linePossibility.call[j]->ret!=NULL && linePossibility.call[j]->ret->mode&Ob(10000000))
					scope->removeVariable(linePossibility.call[j]->ret->name);
			}
		}
		for(int j=0;j<linePossibility.p.size();j++)//remove unused temp vars
		{
			if(linePossibility.p[j].possibleFunctions!=NULL)
				free(linePossibility.p[j].possibleFunctions);
		}
		possibilities.erase(possibilities.begin()+i);
	}
	
	return possibilities;
}
void Line::parseNextIsNewVariable( vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt )
{
	CallToken token;
			initCallToken(token);

	token.newVariable=1;
	token.str=call[p].str;
	attempt.push_back(token);
	parseCode(call,p+1,functions,attempt);
}

void Line::parseNextIsVariable( vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt )
{
	CallToken token;
			initCallToken(token);

	token.possibleVariable=call[p].possibleVariable;//scope->getVariable(call[p].str);
	token.str=call[p].str;
	attempt.push_back(token);
	parseCode(call,p+1,functions,attempt);
}

void Line::parseNextIsLabel( vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt )
{
	CallToken token;
			initCallToken(token);

	token.label=call[p].label;
	token.str=call[p].str;
	token.newVariable=0;
	token.newVariablePtr=NULL;
	attempt.push_back(token);
	parseCode(call,p+1,functions,attempt);
}
void Line::parseNextIsFunction( vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt,Function *function )
{
	CallToken token;
			initCallToken(token);

	//token.possibleFunctions.insert(function);
	insertFunction(token,function);
	token.str=call[p].str;
	attempt.push_back(token);
	parseCode(call,p+1,functions,attempt);
}

void Line::parseCode( vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt )
{
	if(p==call.size())
	{
		LinePossibility *lp=new LinePossibility;
		lp->p=attempt;
		static int id=0;
		lp->id=id++;
		functions.push_back(lp);
		return;
	}
	else
	{
		if(call[p].newVariable)
			parseNextIsNewVariable(call,p,functions,attempt);
		if(call[p].possibleVariable!=NULL)
			parseNextIsVariable(call,p,functions,attempt);
		if(call[p].label!=NULL)
			parseNextIsLabel(call,p,functions,attempt);

		//for(set<Function*>::iterator it=call[p].possibleFunctions[0];it!=call[p].possibleFunctions.end();it++)
		//	parseNextIsFunction(call,p,functions,attempt,*it);
		for(int i=0;i<call[p].nPossibleFunctions;i++)
			parseNextIsFunction(call,p,functions,attempt,call[p].possibleFunctions[i]);
	}
}

Scope::Scope( Function* function,Scope *_parent/*=NULL*/ )
{
	parent=_parent;
	level=0;
	if(function->ret!=NULL)
	{
		variables[function->ret->name]=function->ret;
	}
	for(int i=0;i<function->arguments.size();i++)
		variables[function->arguments[i]->name]=function->arguments[i];
}
void Scope::addVariable( Variable *var )
{
	variables[var->name]=var;
}

Variable * Scope::getVariable( string name )
{
	map<string,Variable*>::iterator it=variables.find(name);
	if(it==variables.end())
	{
		if(parent!=NULL)
			return parent->getVariable(name);
		else
			return NULL;
	}
	else
		return it->second;
}

std::string Scope::getTempName( string typeName,string suffix/*=""*/ )
{
	string ret;
	if(typeName=="Label")
	{
		while(labels.find((ret=string("t_")+typeName+i2s(rand()%100)+tokenize(suffix)))!=labels.end());
	}
	else
	{
		//	while(variables.find((ret=string("__ZXQ_temp_")+typeName+i2s(rand())+suffix))!=variables.end());
		while(variables.find((ret=string("t_")+typeName+i2s(rand()%100)+tokenize(suffix)))!=variables.end());
	}
	return ret;
}

void Scope::removeVariable( string name )
{
	variables.erase(name);
}

Function::Function( string str )
	:original(str)
{
	Function();
	firstLine=lastLine=NULL;
	precedence=0;
	line=NULL;
	spos pos=0;
	internalPrintC99=NULL;
	isInline=0;
	ret=NULL;
	option:
	if(original[pos]=='r' && (original[pos+1]=='(' || (original[pos+1]==' ' && original[find_not(original," ",pos+1)]=='(')))//has a return value
	{
		ret=new Variable(original,pos);
		ret->mode|=Ob(100000);
		goto option;
	}
	else if(original.substr(pos,6)=="inline")
	{
		isInline=1;
		pos+=7;
		goto option;
	}

	while(pos<str.size())
	{
		while(str[pos]==' ') pos++;
		if(str[pos]=='p')
		{
			spos pos2=find_not(str," ",pos+1);
			if(str[pos2]=='=')
			{
				pos2=find_not(str," ",pos2+1);
				pos=find_not(str,"1234567890-.",pos2+1);
				string num=str.substr(pos2,pos-pos2+1);
				sscanf(num.c_str(),"%f",&precedence);
				continue;
			}
		}
		name.push_back(new Identifier(str,pos));
		if(name.back()->var==NULL)
			identifiers[name.back()->text].push_back(this);
		minIdentifiers+=!name.back()->optional;
		if(name.back()->var!=NULL)
			arguments.push_back(name.back()->var);
	}
}

Function::~Function()
{
	for(int i=0;i<name.size();i++)
	{
		if(name[i]->var==NULL)
		{
			auto it=identifiers.find(name[i]->text);
			checkErrors(it==identifiers.end(),"internal error 56");
			for(int j=0;j<it->second.size();j++)
				if(it->second[j]==this)
				{
					it->second.erase(it->second.begin()+j--);
				}
		}
	}
}

vector<Line*> Line::getLabels()
{
	vector<Line*> l;
	l.push_back(this);
	//if(type==Line::LABEL)
	{
		for(int i=lineNumber+1;i<lines.size();i++)
		{
			if(lines[i]->level==level)
			{
				if(lines[i]->type==Line::LABEL || lines[i]->type==Line::LABEL_WITH_CODE)
					l.push_back(lines[i]);
				else if(lines[i-1]->type!=Line::LABEL_WITH_CODE)
				{	
					l.push_back(lines[i]);
					
						break;
				}
			}
			else if(lines[i]->level<level)
			{	
				l.push_back(lines[i]);
				break;
			}
		}
	}

	return l;
}

Identifier::Identifier( string str,spos &pos )
{
	var=NULL;
	optional=0;
	original=str;
	if(str[pos]=='[')
	{
		optional=1;
		checkErrors(str.find(']',pos)==string::npos,"No closing [ found");
		original=str.substr(pos,str.find(']',pos)-pos+1);
	}
	text=str.substr(pos,str.find(' ',pos+1)-pos);
	removeLeadingTrailingSpaces(text);
	if((text.find('('))!=npos)//variable?
	{
		spos thisOpen=str.find('(',pos);
		spos old=pos;
		spos nextClose=str.find(')',thisOpen);
		spos nextOpen=str.find('(',thisOpen+1);
		spos nextAny=find_not(str,invisibleCharacers,pos+1);
		if(nextClose==npos || (nextOpen!=npos && nextOpen<nextClose) || nextAny==npos)
			goto id;
		string betweenParen=str.substr(thisOpen+1,nextClose-thisOpen-1);
		removeLeadingTrailingSpaces(betweenParen);
		if(find_not(betweenParen,invisibleCharacers)==betweenParen.size())
			goto id;
		if(types.find(betweenParen)==types.end())
			goto id;
		if(find_not(str,invisibleCharacers,nextClose+1)==str.size())
			goto id;
		if(str[find_not(str,invisibleCharacers,nextClose+1)]=='(')
			goto id;

		var=new Variable(str,pos);
		var->mode|=Ob(100000);
		text=str.substr(old,pos-old);
		return;
	}
	id:
	{
		spos end=find(str,invisibleCharacers+']',pos+1);
		if(end!=str.size())
		{
			str=str.substr(pos,end-pos);
			pos=end+1;
		}
		else
			pos=str.size();
	}
}

Variable::Variable( string str,size_t &pos )
{
	constant=NULL;
	parent=NULL;
	mode=0;
	spos startPos=pos;
	pos=str.find('(',pos);
	checkErrors(pos==string::npos,"Expected ( in variable declaration");
	for(int i=startPos;i<pos;i++)
	{
		switch(str[i])
		{
		case 'r':
			mode|=Ob(1);
			break;
		case 'i':
			mode|=Ob(10);
			break;
		case 'o':
			mode|=Ob(100);
			break;
		case 'd':
			mode|=Ob(1000);
			break;
		}
	}
	size_t endOfType=str.find(')',pos);
	checkErrors(endOfType==string::npos,"Expected ) after type");
	string typeName=str.substr(pos+1,endOfType-pos-1);
	removeLeadingTrailingSpaces(typeName);
	type=getType(typeName);
	pos=endOfType+1;

	pos=str.find_first_not_of(' ',pos);
	if(pos!=endOfType+1 && mode&Ob(1))
		return;
	spos endOfName=find(str,invisibleCharacers,pos);
	checkErrors((endOfName==pos || endOfName==npos) && !(mode&1),"No variable name specified");
	name=str.substr(pos,endOfName-pos);
	pos=endOfName;
}

std::string Struct::getC99Default()
{
	string ret="("+getC99Type()+") {";
	bool first=1;
	for(auto it=members.begin();it!=members.end();it++)
	{
		if(!first)
			ret+=", ";
		else
			first=0;
		if(it->second->type->isStruct() || it->second->constant==NULL)
			ret+=it->second->type->getC99Default();
		else
			ret+=it->second->constant->getC99Constant();
	}
	ret+="}";
	return ret;
}

std::string Struct::getC99Type()
{
	return "struct "+name;
}

void Struct::addMember( string str )
{
	removeLeadingTrailingSpaces(str);
	checkErrors(str[0]!='(',"Member definition does not begin with a type");
	spos endOfType=str.find(')');
	checkErrors(endOfType==str.size(),"Member definition does not begin with a type");
	string typeName=str.substr(1,endOfType-1);
	removeLeadingTrailingSpaces(typeName);
	spos startOfName=find(str,upperLetters+lowerLetters,endOfType);
	checkErrors(startOfName==str.size(),"No variable name specified");
	spos endOfName=find_not(str,upperLetters+lowerLetters+numerals+"_",startOfName);
	string memberName=str.substr(startOfName,endOfName-startOfName);
	Type *type=getType(typeName);
	checkError(type==NULL,"%s is not a valid type",typeName.c_str());
	Variable *var=new Variable(memberName,type);
	members[memberName]=var;
	spos equal=find(str,"=",endOfName);
	if(equal!=str.size())
	{
		spos startOfValue=find_not(str," ",equal+1);
		checkErrors(startOfValue==str.size(),"No default value given");
		var->constant=parseConstant(str.substr(startOfValue,str.size()-startOfValue+1));
	}
	//parseSourceLine("\t")
	NONE;
}
