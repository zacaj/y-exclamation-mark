#pragma once
#include "common.h"

extern int realLineNumber;
void checkErrors(bool isError,string description);

#define WHERESTRE  "ERROR %i: "
#define WHEREARGE  realLineNumber
#define DEBUGPRINT2E(...)       _print(__VA_ARGS__)

/**
    Prints the included text, with line number

    Use error just like you would printf.  It will automatically add the position
        from where it was called and the word ERROR in capital letters.
        Depending on the current debug setting, error()
        will print to the console, log file, or not at all.

    \see errors debug print
    */
#define checkError(is,_fmt, ...)  \
	{{ \
		if(is) \
		{ \
			DEBUGPRINT2E(WHERESTRE _fmt, WHEREARGE, __VA_ARGS__); \
			BREAK \
		} \
	} \
}
class Type;
class Line;
class Function;
class FunctionCall;
class Variable
{
public:
	string name;
	Type *type;
	uchar mode;
	Type *constant;
	Variable(string _name,Type *_type)
		:name(_name),
		type(_type),
		mode(0),
		constant(NULL){}
	Variable(string str,size_t &pos);
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
	string llvmName()
	{
		string ret=name;
		//return ret;
		for(int i=0;i<ret.size();i++)
			if(!isalnum(ret[i]))
				ret.erase(i--,1);
		return ret;
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
	Identifier(string str,spos &pos);
};


class Function
{
public:
	string original;
	Variable *ret;
	vector<Variable*> arguments;
	vector<Identifier*> name;
	uint minIdentifiers;
	float precedence;
	int firstLine,lastLine;
	vector<Line*> lines;
	bool isInline;
	Line *line;

	string processedFunctionName;
	void (*internalPrintC99)(FILE*,FunctionCall*);
	~Function();

	Function()
		:ret(NULL),precedence(0.0),internalPrintC99(NULL){}
	Function(string str);
	void printC99Declaration(FILE *fp);
};
extern Function *startFunction;
class FunctionCall
{
public:
	Function *function;
	vector<Variable*> arguments;
	Variable *ret;
	Function *callee;

	FunctionCall()
	{
		ret=NULL;
		function=NULL;
	}
	string llvmCall();
	void printC99(FILE *fp);
};

class Scope
{
	map<string,Variable*> variables;
public:
	uchar level;
	Scope *parent;

	Scope(Function* function,Scope *_parent=NULL);
	string getTempName(string typeName,string suffix="");
	Variable *getVariable(string name);
	void addVariable(Variable *var);
	void removeVariable(string name);
	void writeC99(FILE *fp);
};
#include <set>
struct CallToken
{
	uchar possibilities;
	bool newVariable;
	string str;
	set<Function*> possibleFunctions;
	Variable* possibleVariable;
	Type *type;
	Variable *newVariablePtr;
	CallToken()
	{
		possibilities=0;
		newVariable=0;
		possibleVariable=NULL;
		newVariablePtr=NULL;
	}
};
struct IndependantFunction 
{
	Function *func;
	int start,end;
};
struct LinePossibility
{
	vector<CallToken> p;
	vector<FunctionCall*> call;
	int id;
};
class Line
{
public:
	string original;
	uchar level;
	vector<FunctionCall*> commands;
	uint lineNumber,originalLineNumber;;
	string processed;
	Scope *scope;
	string comment;
	Function *parent;
	enum LineType {UNKNOWN,INTERPRETER_COMMAND,FUNCTION_DECLARATION,CODE,CODE_WITH_OPTIONS,LABEL,EMPTY} type;
	string cString;

	Line(string str,uint _lineNumber);
		
	void splitCommands(string str);
	void parseNextIsNewVariable(vector<CallToken> &call,uint p,vector<LinePossibility> &functions,vector<CallToken> attempt);
	void parseNextIsVariable(vector<CallToken> &call,uint p,vector<LinePossibility> &functions,vector<CallToken> attempt);
	void parseNextIsFunction(vector<CallToken> &call,uint p,vector<LinePossibility> &functions,vector<CallToken> attempt,Function *function);
	void parseCode(vector<CallToken> &call,uint p,vector<LinePossibility> &functions,vector<CallToken> attempt);

	vector<Line*> getLabels();

	int printC99(FILE *fp,int replacementLevel=-1);
};

extern map<string,int> labels;

void addLabel(string label);

extern vector<Line*> lines;
extern vector<Function*> functions;
