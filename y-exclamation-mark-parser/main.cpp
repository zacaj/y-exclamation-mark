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
		pos=str.find('(',pos);
		checkErrors(pos==string::npos,"Expected ( in variable declaration");
		for(int i=0;i<pos;i++)
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

	Function()
		:ret(NULL){}
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
		vector<string> call;
		spos pos=0;
		set<Function*> possibleFunctions;
		set<string> possibleVariables;
		while(pos<str.size()-1)
		{
			while(pos<str.size() && str[pos]==' ') pos++;
			spos endOfId=str.find(' ',pos);
			if(endOfId==npos)
				endOfId=str.size();
			string id=str.substr(pos,endOfId-pos);
			removeLeadingTrailingSpaces(id);
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
				scope->variables[id]=new Variable(id,getType("string"));
				possibleVariables.insert(id);
			}
			else if(isdigit(id[0]))//todo variables that start with numbers?
			{
				while(pos<str.size() && isdigit(str[pos++]));
				id=scope->getTempName("int");
				scope->variables[id]=new Variable(id,getType("int"));
				possibleVariables.insert(id);
			}
			else
			{
				pos=endOfId+1;
				map<string,vector<Function*>>::iterator fit=identifiers.find(id);
				checkError(fit==identifiers.end() && !Variable::isValidName(id),"%s not found",id.c_str());
				if(fit!=identifiers.end())
				{
					vector<Function*> &functions=fit->second;
					for(int i=0;i<functions.size();i++)
					{
						possibleFunctions.insert(functions[i]);

					}
				}
				if(Variable::isValidName(id))
				{
					possibleVariables.insert(id);
				}
			}
			call.push_back(id);
		}
		NONE;
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
	functions.push_back(new Function("r(int)sum (int)a + (int) b"));
	functions.push_back(new Function("o(int)a = (int) b"));
	functions.push_back(new Function("r(bool)isLess (int)a < (int)b"));
	functions.push_back(new Function("print (string)str"));
	functions.push_back(new Function("if (bool)is"));
	functions.push_back(new Function("go to line (int)lineNumber"));
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