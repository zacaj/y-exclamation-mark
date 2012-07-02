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
Function *switchEndFunction,*caseFunction,*caseEndFunction,*continueFunction,*continueCaseFunction,*continueDefaultFunction,*defaultFunction;
int main(_In_ int _Argc, char **argv)
{
	initCommon();
	types["int"]=new Int;
	types["string"]=new String;
	types["bool"]=new Bool;
	types["branch"]=new Branch;
	types["Label"]=new Label;
	int start=time(NULL);
	FILE *fp=fopen("../y! code/main.y","r");
	addLabel("default",NULL);
	addLabel("else",NULL);
	/*functions.push_back(new Function("return (int)r"));
	functions.push_back(new Function("return (string)r"));
	functions.push_back(new Function("r(int)sum (int)a + (int) b p = -20"));
	functions.push_back(new Function("o(int)a = (int) b p = -100"));
	functions.push_back(new Function("r(bool)isLess (int)a < (int)b"));
	functions.push_back(new Function("print (string)str"));
	//functions.push_back(new Function("if (bool)is"));
	//functions.push_back(new Function("goToLine (int)lineNumber"));*/
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
		}

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

	}

	for(int i=0;i<lines.size();i++)
	{
		if(lines[i]->type==Line::CODE || lines[i]->type==Line::CODE_WITH_OPTIONS)
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

Line::Line( string str,uint _lineNumber ):originalLineNumber(_lineNumber)
{
	lineNumber=lines.size();
	removeLeadingTrailingSpaces(str);
	scope=NULL;
	original=str;

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
		if(tab==string::npos)//function declaration or option
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
			else
			{
				functions.push_back(new Function(str));
				functions.back()->line=this;
				scope=new Scope(functions.back());
				scope->level=1;
				type=FUNCTION_DECLARATION;
				currentFunction=functions.back();
				lines.push_back(this);
				return;
			}
		}
		//else
		{
			parent=currentFunction;
			currentFunction->lines.push_back(this);
			if(currentFunction->firstLine==-1)
				currentFunction->firstLine=lineNumber;
			currentFunction->lastLine=lineNumber;
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
					addLabel(processed,parent);
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

void Line::splitCommands( string str )
{
	if(cString.size())
		return;
	vector<CallToken> call;
	spos pos=0;
	while(pos<str.size())
	{
		while(pos<str.size() && str[pos]==' ') pos++;
		spos endOfId=str.find(' ',pos);
		if(endOfId==npos)
			endOfId=str.size();
		string id=str.substr(pos,endOfId-pos);
		removeLeadingTrailingSpaces(id);
		CallToken token;
		token.possibilities=0;
		token.newVariable=0;
		token.possibleVariable=NULL;
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
			token.str=id;
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
			token.str=id;
			scope->addVariable(token.possibleVariable);
		}
		else
		{
			pos=endOfId+1;
			map<string,vector<Function*>>::iterator fit=identifiers.find(id);
			//checkError(fit==identifiers.end() && !Variable::isValidName(id),"%s not found",id.c_str());
			if(fit!=identifiers.end())
			{
				vector<Function*> &functions=fit->second;
				for(int i=0;i<functions.size();i++)
				{
					token.possibleFunctions.insert(functions[i]);
					//possibleFunctions.insert(functions[i]);
				}
				if(token.possibleFunctions.size())
				{
					token.str=id;
					token.possibilities++;
				}
			}
			Variable *var=scope->getVariable(id);
			if(var!=NULL)
			{
				token.str=id;
				token.possibleVariable=var;
				token.possibilities++;
			}
			else if(Variable::isValidName(id))
			{
				token.newVariable=1;
				token.str=id;
				token.possibilities++;
			}

			if(labels.find(id)!=labels.end())
			{
				if(labelLocations[id].find(parent)!=labelLocations[id].end())
				{
					token.label=id;
					token.str=id;
					token.possibilities++;
				}
			}
		}
		checkError(token.possibilities==0,"%s not found\n",id.c_str());

		call.push_back(token);
	}
	//checkErrors(possibleFunctions.size()==0,"no function specified");
	vector<CallToken> attempt;
	vector<LinePossibility> possibilities;
	parseCode(call,0,possibilities,attempt);
	string failReason;
	for(int i=0;i<possibilities.size();i++)
	{
#define FAIL(reason) { failReason=reason; goto fail; }
		vector<CallToken> &possibility=possibilities[i].p;
		int id=possibilities[i].id;
		vector<IndependantFunction> independantFunctionPossibilities;
		int j;
		for(j=0;j<possibility.size();j++)//go thru all ids
		{
			if(possibility[j].possibleFunctions.size())//if its a funcion id
			{
				Function *func=*possibility[j].possibleFunctions.begin();
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
								//possibility[j-functionTokenIndexInFunction+k].newVariablePtr->mode|=Ob(100);
							}	
						}
						else if(possibility[j-functionTokenIndexInFunction+k].label.size())
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
							if(possibility[j-functionTokenIndexInFunction+k].possibleVariable->type!=func->name[k]->var->type)
								break;
						}
					}
					else
					{
						if(!possibility[j-functionTokenIndexInFunction+k].possibleFunctions.size() || *possibility[j-functionTokenIndexInFunction+k].possibleFunctions.begin()!=func ||func->name[k]->text!=possibility[j-functionTokenIndexInFunction+k].str)
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
		if(indf.start==0 && indf.end==possibility.size())//only this call
		{
			{
				FunctionCall *fcall=new FunctionCall();
				fcall->function=indf.func;
				fcall->ret=NULL;
				fcall->callee=parent;
				fcall->line=this;
				for(int j=indf.start;j<indf.end;j++)
				{
					if(possibility[j].possibleVariable!=NULL)
						fcall->arguments.push_back(possibility[j].possibleVariable);
					else if(possibility[j].newVariablePtr!=NULL)
						fcall->arguments.push_back(possibility[j].newVariablePtr);
					else if(possibility[j].label.size())
						fcall->arguments.push_back(new Variable(possibility[j].label,getType("Label")));
				}
				checkErrors(fcall->arguments.size()!=fcall->function->arguments.size(),"internal error 4");
				possibilities[i].call.push_back(fcall);
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
				fcall->callee=parent;
				for(int j=indf.start;j<indf.end;j++)
				{
					if(possibility[j].possibleVariable!=NULL)
						fcall->arguments.push_back(possibility[j].possibleVariable);
					else if(possibility[j].newVariablePtr!=NULL)
						fcall->arguments.push_back(possibility[j].newVariablePtr);
					else if(possibility[j].label.size())
						fcall->arguments.push_back(new Variable(possibility[j].label,getType("Label")));
				}
				checkErrors(fcall->arguments.size()!=fcall->function->arguments.size(),"internal error 4");
				possibilities[i].call.push_back(fcall);
			}
			possibility.erase(possibility.begin()+indf.start,possibility.begin()+indf.end);
			CallToken token;
			token.str=var->name;
			token.possibleVariable=var;
			possibility.insert(possibility.begin()+indf.start,token);
			i--;
		}


		continue;//skip fail if got to here

fail:
		for(int j=0;j<possibilities[i].call.size();j++)//remove unused temp vars
		{
			//for(int k=0;k<possibilities[i].call[j]->arguments.size();k++)
			{
				if(possibilities[i].call[j]->ret!=NULL && possibilities[i].call[j]->ret->mode&Ob(10000000))
					scope->removeVariable(possibilities[i].call[j]->ret->name);
			}
		}
		possibilities.erase(possibilities.begin()+i--);
	}
	checkErrors(possibilities.size()==0,"no function specified");
	checkErrors(possibilities.size()>=2,"ambiguous call");
	for(int i=0;i<possibilities[0].p.size();i++)
	{
		if(possibilities[0].p[i].newVariable)
		{
			//checkError(possibilities[0][i].possibleVariable==NULL,"internal error 4: %s not created\n",possibilities[0][i].str.c_str());
			if(possibilities[0].p[i].newVariablePtr!=NULL)
			{
				scope->addVariable(possibilities[0].p[i].newVariablePtr);
			}
			else
			{
				if(possibilities[0].p[i].possibleVariable==NULL)
					scope->addVariable(new Variable(possibilities[0].p[i].str,possibilities[0].p[i].type));
				else
					scope->addVariable(possibilities[0].p[i].possibleVariable);
			}
		}

	}
	commands=possibilities[0].call;
	debug("Processed line %i\n",originalLineNumber);
	NONE;
}

void Line::parseNextIsNewVariable( vector<CallToken> &call,uint p,vector<LinePossibility> &functions,vector<CallToken> attempt )
{
	CallToken token;
	token.newVariable=1;
	token.str=call[p].str;
	attempt.push_back(token);
	parseCode(call,p+1,functions,attempt);
}

void Line::parseNextIsVariable( vector<CallToken> &call,uint p,vector<LinePossibility> &functions,vector<CallToken> attempt )
{
	CallToken token;
	token.possibleVariable=scope->getVariable(call[p].str);
	token.str=call[p].str;
	attempt.push_back(token);
	parseCode(call,p+1,functions,attempt);
}

void Line::parseNextIsLabel( vector<CallToken> &call,uint p,vector<LinePossibility> &functions,vector<CallToken> attempt )
{
	CallToken token;
	token.label=call[p].label;
	token.str=call[p].str;
	attempt.push_back(token);
	parseCode(call,p+1,functions,attempt);
}
void Line::parseNextIsFunction( vector<CallToken> &call,uint p,vector<LinePossibility> &functions,vector<CallToken> attempt,Function *function )
{
	CallToken token;
	token.possibleFunctions.insert(function);
	token.str=call[p].str;
	attempt.push_back(token);
	parseCode(call,p+1,functions,attempt);
}

void Line::parseCode( vector<CallToken> &call,uint p,vector<LinePossibility> &functions,vector<CallToken> attempt )
{
	if(p==call.size())
	{
		LinePossibility lp;
		lp.p=attempt;
		static int id=0;
		lp.id=id++;
		functions.push_back(lp);
		return;
	}
	else
	{
		if(call[p].newVariable)
			parseNextIsNewVariable(call,p,functions,attempt);
		if(call[p].possibleVariable!=NULL)
			parseNextIsVariable(call,p,functions,attempt);
		if(call[p].label.size())
			parseNextIsLabel(call,p,functions,attempt);

		for(set<Function*>::iterator it=call[p].possibleFunctions.begin();it!=call[p].possibleFunctions.end();it++)
			parseNextIsFunction(call,p,functions,attempt,*it);
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
	firstLine=lastLine=-1;
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

	while(pos<str.size()-1)
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
		if(find_not(str,invisibleCharacers,nextClose)==str.size())
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