#include <stdio.h>
#include <string>
#include <time.h>
using namespace std;
#include "file.h"
#include "common.h"
#include "types.h"
#include <stdarg.h>
#include <set>
#include "main.h"

string tempPath;
int lineNumber=0;

void checkErrors(bool isError,string description="")
{
	if(isError)
	{
		error("ERROR %i: %s\n",lineNumber,description.c_str());
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

class Variable
{
public:
	string name;
	Type *type;
	uchar mode;
	Variable(string _name,Type *_type)
		:name(_name),
		type(_type),
		mode(0){}
	Variable(string str,size_t &pos)
	{
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
		spos endOfName=find(str,invisibleCharacers,pos);
		checkErrors((endOfName==pos || endOfName==npos) && !(mode&1),"No variable name specified");
		name=str.substr(pos,endOfName-pos);
		pos=endOfName;
	}
	static bool isValidName(string name)
	{
		if(!isalpha(name[0]))
			return 0;
		for(int i=0;i<name.size();i++)
		{
			if(name[i]<=32)
				return 0;
		}
		return 1;
	}
};

class Identifier
{
public:
	string text;
	Variable *var;
	bool optional;
	string original;
	Identifier()
		:var(NULL),
		optional(0){}
	Identifier(string str,spos &pos)
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
		if(text.find('(')!=npos)//variable
		{
			spos old=pos;
			var=new Variable(str,pos);
			text=str.substr(old,pos-old);
		}
		else
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
};
class Function;
map<string,vector<Function*>> identifiers;

class Function
{
public:
	string original;
	Variable *ret;
	vector<Variable*> arguments;
	vector<Identifier*> name;
	uint minIdentifiers;
	float precedence;

	Function()
		:ret(NULL),precedence(0){}
	Function(string str)
		:original(str)
	{
		Function();
		spos pos=0;
		if(original[0]=='r' && (original[1]=='(' || (original[1]==' ' && original[find_not(original," ",1)]=='(')))//has a return value
		{
			ret=new Variable(original,pos);
		}
		else
			ret=NULL;
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
			identifiers[name.back()->text].push_back(this);
			minIdentifiers+=!name.back()->optional;
			if(name.back()->var!=NULL)
				arguments.push_back(name.back()->var);
		}
	}
};
vector<Function*> functions;

class FunctionCall
{
public:
	Function *function;
	vector<Variable*> arguments;
	Variable *ret;

	FunctionCall()
	{
		ret=NULL;
		function=NULL;
	}
};

class Scope
{
public:
	map<string,Variable*> variables;
	uchar level;

	Scope(Function* function)
	{
		level=0;
		if(function->ret!=NULL)
		{
			variables[function->ret->name]=function->ret;
		}
		for(int i=0;i<function->arguments.size();i++)
			variables[function->arguments[i]->name]=function->arguments[i];
	}
	string getTempName(string typeName)
	{
		string ret;
		while(variables.find((ret=string("__ZXQ_temp_")+typeName+i2s(rand())))!=variables.end());
		return ret;
	}
};
class Line;

struct CallToken
{
	uchar possibilities;
	bool newVariable;
	string str;
	set<Function*> possibleFunctions;
	Variable* possibleVariable;
	Type *type;
	CallToken()
	{
		possibilities=0;
		newVariable=0;
		possibleVariable=NULL;
	}
};
struct IndependantFunction 
{
	Function *func;
	int start,end;
};
vector<Line*> lines;
class Line
{
public:
	string original;
	uchar level;
	vector<FunctionCall*> commands;
	uint lineNumber,originalLineNumber;;
	string processed;
	Scope *scope;
	enum LineType {UNKNOWN,INTERPRETER_COMMAND,FUNCTION_DECLARATION,CODE,CODE_WITH_OPTIONS,EMPTY} type;

	Line(string str,uint _lineNumber)
		:originalLineNumber(_lineNumber)
	{
		lineNumber=lines.size();
		removeLeadingTrailingSpaces(str);
		scope=NULL;
		if(find_not(str,invisibleCharacers)!=str.size())
		{
			original=str;
			size_t tab=original.find(9);
			processed=original;
			if(tab==string::npos)//function declaration or option
			{
				level=0;
				spos firstSpace=str.find(' ');
				string first;
				if(firstSpace!=npos)
				{
					first=original.substr(0,firstSpace);
				}
				if(handlePotentialInterpreterOption(first))
				{
					type=INTERPRETER_COMMAND;
				}
				else
				{
					functions.push_back(new Function(original));
					scope=new Scope(functions.back());
					type=FUNCTION_DECLARATION;
				}
			}
			else
			{
				if(tab==0)
					type=CODE;
				else
					type=CODE_WITH_OPTIONS;
				//todo handle options
				size_t commandStart=original.find_first_not_of(9,tab);
				level=commandStart-tab;
				processed.erase(processed.begin(),processed.begin()+commandStart);
				checkErrors(lineNumber==0,"Code outside of a function");

				if(level==lines[lineNumber-1]->level)
					scope=lines[lineNumber-1]->scope;
				else if(level>lines[lineNumber-1]->level)
				{
					scope=new Scope(*lines[lineNumber-1]->scope);
				}
				else
				{
					for(int i=lineNumber-1;i>=0;i--)
					{
						if(lines[i]->level==level)
						{
							scope=lines[i]->scope;
							break;
						}
						else if(lines[i]->level<level)
						{
							scope=new Scope(*lines[i]->scope);
							break;
						}
					}
					checkErrors(scope==NULL,"Code outside of a function");
				}
			}
		}
		else
			type=EMPTY;
	}
	void splitCommands(string str)
	{
		vector<CallToken> call;
		spos pos=0;
		//set<Function*> possibleFunctions;
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
			if(id[0]=='\"')
			{
				spos startOfString=pos;
				while(pos<str.size()-1)
				{
					pos=find(str,"\"",pos+1);
					if(str[pos-1]!='\\')
						break;
				}
				checkErrors(pos==str.size(),"No closing \" found ");
				pos++;
				id=scope->getTempName("string");
				//scope->variables[id]=new Variable(id,getType("string"));
				token.possibleVariable=new Variable(id,getType("string"));
				token.possibleVariable->mode|=Ob(10000);
				token.str=id;
				token.possibilities++;
				scope->variables[token.str]=token.possibleVariable;
			}
			else if(isdigit(id[0]))//todo variables that start with numbers?
			{
				while(pos<str.size() && isdigit(str[pos++]));
				id=scope->getTempName("int");
				//scope->variables[id]=new Variable(id,getType("int"));
				token.possibleVariable=new Variable(id,getType("int"));
				token.possibleVariable->mode|=Ob(10000);
				token.possibilities++;
				token.str=id;
				scope->variables[token.str]=token.possibleVariable;
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
				map<string,Variable*>::iterator vit=scope->variables.find(id);
				if(vit!=scope->variables.end())
				{
					token.str=id;
					token.possibleVariable=(vit->second);
					token.possibilities++;
				}
				else if(Variable::isValidName(id))
				{
					token.newVariable=1;
					token.str=id;
					token.possibilities++;
				}
			}
			checkError(token.possibilities==0,"%s not found\n",id.c_str());

			call.push_back(token);
		}
		//checkErrors(possibleFunctions.size()==0,"no function specified");
		vector<CallToken> attempt;
		vector<vector<CallToken>> possibilities;
		parseCode(call,0,possibilities,attempt);
		vector<vector<FunctionCall*>> possibleCalls;
		for(int i=0;i<possibilities.size();i++)
		{
#define FAIL(reason) { failReason=reason; goto fail; }
			string failReason;
			/*int j=0;
			int lastFunctionStart=0;//global
			int lastFunctionToken=-1;//so start on 0      global
			Function *lastFunc=NULL;
			string failReason;
			vector<FunctionCall*> functionCall;
			while(1)
			{
				for(j=lastFunctionToken+1;j<possibilities[i].size();j++)//find next function token
				{
					if(possibilities[i][j].possibleFunctions.size())
						break;
				}
				if(j==possibilities[i].size())//no more function tokens
					break;
				Function *func=*possibilities[i][j].possibleFunctions.begin();
				if((func!=lastFunc && lastFunc!=NULL))
				{
					int newFunctionTokenIndex=0;//local
					for(;newFunctionTokenIndex<func->name.size();newFunctionTokenIndex++)
						if(func->name[newFunctionTokenIndex]->text==possibilities[i][j].str)
							break;
					checkErrors(newFunctionTokenIndex==func->name.size(),"internal error 2");
					for(int k=0;k<newFunctionTokenIndex;k++)
					{
						if(func->name[k]->var==NULL)
							FAIL("421 not a variable");
						if(possibilities[i][k+lastFunctionToken+1].newVariable)
						{
							if(!func->name[k]->var->mode&Ob(100))//output
								FAIL("not an output this position")
							else
								possibilities[i][k+lastFunctionToken+1].possibleVariable=new Variable(possibilities[i][k+lastFunctionToken+1].str,func->name[k]->var->type);
						}
						else
						{
							if(func->name[k]->var->type!=possibilities[i][k+lastFunctionToken+1].possibleVariable->type)
								FAIL("423 wrong type");
						}
					}

					lastFunctionStart=j-newFunctionTokenIndex;
					lastFunctionToken=newFunctionTokenIndex+lastFunctionStart;
				}
				if(func->name[j-lastFunctionStart]->text!=possibilities[i][j].str)
					FAIL("431 token not match");
				for(int k=lastFunctionToken+1;k<j;k++)//check between last token (or start) and this one
				{
					if(func->name[k-lastFunctionStart]->var==NULL)
						FAIL("431 not a variable");
					if(possibilities[i][k].newVariable)
					{
						if(!func->name[k-lastFunctionStart]->var->mode&Ob(100))//output
							FAIL("not an output this position")
						else
							possibilities[i][k].possibleVariable=new Variable(possibilities[i][k].str,func->name[k-lastFunctionStart]->var->type);
					}
					else
					{
						if(func->name[k-lastFunctionStart]->var->type!=possibilities[i][k].possibleVariable->type)
							FAIL("433 wrong type");
					}
				}
				lastFunctionToken=j;
				lastFunc=func;
			}
			for(j=0;j<possibilities[i].size();j++)
				if(possibilities[i][j].possibleFunctions.size())
					break;
			if(j==possibilities[i].size())
				FAIL("no function tokens")
			checkErrors(lastFunc==NULL,"internal error 3");
			for(j=lastFunctionToken+1;j<possibilities[i].size();j++)//find first function token
			{
				if(lastFunc->name[j-lastFunctionStart]->var==NULL)
					FAIL("451 not a variable")
				if(possibilities[i][j].newVariable)
				{
					if(!lastFunc->name[j-lastFunctionStart]->var->mode&Ob(100))//output
						FAIL("not an output this position")
					else
						possibilities[i][j].possibleVariable=new Variable(possibilities[i][j].str,lastFunc->name[j-lastFunctionStart]->var->type);
				}
				else
				{
					if(lastFunc->name[j-lastFunctionStart]->var->type!=possibilities[i][j].possibleVariable->type)
						FAIL("453 wrong type")
				}
			}*/

			//while(1)

			vector<IndependantFunction> independantFunctionPossibilities;
			{
				int j;
				for(j=0;j<possibilities[i].size();j++)//go thru all ids
				{
					if(possibilities[i][j].possibleFunctions.size())//if its a funcion id
					{
						Function *func=*possibilities[i][j].possibleFunctions.begin();
						//find the same id in the function
							int functionTokenIndexInFunction=0;
							for(;functionTokenIndexInFunction<func->name.size();functionTokenIndexInFunction++)
							{
								if(func->name[functionTokenIndexInFunction]->text==possibilities[i][j].str)
									break;
							}
							checkErrors(functionTokenIndexInFunction==func->name.size(),"internal error 1");

						int k;
						for(k=0;k<func->name.size();k++)
						{
							if(func->name[k]->var!=NULL)
							{
								if(possibilities[i][j-functionTokenIndexInFunction+k].newVariable)//output
								{
									if(!func->name[k]->var->mode&Ob(100))
										break;
									else
										possibilities[i][j-functionTokenIndexInFunction+k].type=func->name[k]->var->type;
								}
								else
								{
									if(possibilities[i][j-functionTokenIndexInFunction+k].possibleVariable==NULL)
										break;
									if(possibilities[i][j-functionTokenIndexInFunction+k].possibleVariable->type!=func->name[k]->var->type)
										break;
								}
							}
							else
							{
								if(!possibilities[i][j-functionTokenIndexInFunction+k].possibleFunctions.size() || *possibilities[i][j-functionTokenIndexInFunction+k].possibleFunctions.begin()!=func ||func->name[k]->text!=possibilities[i][j-functionTokenIndexInFunction+k].str)
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


			}


			continue;//skip fail if got to here

fail:
			possibilities.erase(possibilities.begin()+i--);
		}
		//checkErrors(possibilities.size()==0,"no function specified");
		//checkErrors(possibilities.size()>=2,"ambiguous call");
		for(int i=0;i<possibilities[0].size();i++)
		{
			if(possibilities[0][i].newVariable)
			{
				//checkError(possibilities[0][i].possibleVariable==NULL,"internal error 4: %s not created\n",possibilities[0][i].str.c_str());
				if(possibilities[0][i].possibleVariable==NULL)
					scope->variables[possibilities[0][i].str]=new Variable(possibilities[0][i].str,possibilities[0][i].type);
				else
					scope->variables[possibilities[0][i].str]=possibilities[0][i].possibleVariable;
			}

		}
		debug("Processed line %i\n",originalLineNumber);
		NONE;
	}
	void parseNextIsNewVariable(vector<CallToken> &call,uint p,vector<vector<CallToken>> &functions,vector<CallToken> attempt)
	{
		CallToken token;
		token.newVariable=1;
		token.str=call[p].str;
		attempt.push_back(token);
		parseCode(call,p+1,functions,attempt);
	}
	void parseNextIsVariable(vector<CallToken> &call,uint p,vector<vector<CallToken>> &functions,vector<CallToken> attempt)
	{
		CallToken token;
		token.possibleVariable=scope->variables.find(call[p].str)->second;
		token.str=call[p].str;
		attempt.push_back(token);
		parseCode(call,p+1,functions,attempt);
	}
	void parseNextIsFunction(vector<CallToken> &call,uint p,vector<vector<CallToken>> &functions,vector<CallToken> attempt,Function *function)
	{
		CallToken token;
		token.possibleFunctions.insert(function);
		token.str=call[p].str;
		attempt.push_back(token);
		parseCode(call,p+1,functions,attempt);
	}
	void parseCode(vector<CallToken> &call,uint p,vector<vector<CallToken>> &functions,vector<CallToken> attempt)
	{
		if(p==call.size())
		{
			functions.push_back(attempt);
			return;
		}
		else
		{
			if(call[p].newVariable)
				parseNextIsNewVariable(call,p,functions,attempt);
			if(call[p].possibleVariable!=NULL)
				parseNextIsVariable(call,p,functions,attempt);

			for(set<Function*>::iterator it=call[p].possibleFunctions.begin();it!=call[p].possibleFunctions.end();it++)
				parseNextIsFunction(call,p,functions,attempt,*it);
		}
	}
};

int main(_In_ int _Argc, char **argv)
{

	initCommon();
	types["int"]=new Int;
	types["string"]=new String;
	types["bool"]=new Bool;
	int start=time(NULL);
	FILE *fp=fopen("../y! code/main.y","r");
	functions.push_back(new Function("return (int)r"));
	functions.push_back(new Function("return (string)r"));
	functions.push_back(new Function("r(int)sum (int)a + (int) b p = -20"));
	functions.push_back(new Function("o(int)a = (int) b p = -100"));
	functions.push_back(new Function("r(bool)isLess (int)a < (int)b"));
	functions.push_back(new Function("print (string)str"));
	functions.push_back(new Function("if (bool)is"));
	functions.push_back(new Function("goToLine (int)lineNumber"));
	lineNumber=1;
	while(!feof(fp))
	{
		string str=readTo(fp,'\n');
		if(!str.empty())
		{
			removeLeadingTrailingSpaces(str);
			lines.push_back(new Line(str,lineNumber));
		}
		lineNumber++;
	}
	fclose(fp);
	for(int i=0;i<lines.size();i++)
	{
		if(lines[i]->type==Line::CODE || lines[i]->type==Line::CODE_WITH_OPTIONS)
			lines[i]->splitCommands(lines[i]->processed);
	}
}