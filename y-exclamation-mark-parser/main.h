#pragma once
#include "common.h"

extern int realLineNumber;
void checkErrors(bool isError,string description);
#define WASANEWVARIABLE Ob(100000000)
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
class Struct;
class Variable
{
public:
	string name;
	Type *type;
	uint mode;
	Type *constant;
	Variable *parent;
	Variable(string _name,Type *_type)
		:name(_name),
		type(_type),
		mode(0),
		parent(NULL),
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
	string nameC99()
	{
		if(parent==NULL)
			return name;
		return parent->nameC99()+"."+name;
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
	Line *firstLine,*lastLine;
	//vector<Line*> lines;
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
	Line *line;

	FunctionCall()
	{
		ret=NULL;
		function=NULL;
		line=NULL;
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
	void writeC99(FILE *fp,int level=-1);
};
class Type
{
public:
	string name;
	virtual int is(string typeName)
	{
		if(typeName=="internal")
			return 1;
		if(typeName==name)
			return 1;
		if(typeName=="var")//fix
			return 2;
		return 0;
	}
	virtual string getLlvmType(){return "";}
	virtual string getC99Type(){return "";}
	virtual string getC99Constant(){return "";}
	virtual string getC99Default(){return "NO DEFAULT FOR THIS TYPE";};
	virtual bool isStruct(){return 0;}
};

class Struct:public Type
{
public:
	map<string,Variable*> members;
	void addMember(string str);

	virtual string getC99Default();
	virtual string getC99Type();
	void writeC99(FILE *fp);
	void writeDeclarationC99(FILE *fp);
	bool isStruct(){return 1;}
};
extern map<string,Struct*> structs;
#include <set>
struct CallToken
{
	uchar possibilities;
	bool newVariable;
	char *str;
	uint nPossibleFunctions,aPossibleFunctions;
	//set<Function*> possibleFunctions;
	Function **possibleFunctions;
	Variable* possibleVariable;
	Type *type;
	Variable *newVariablePtr;
	char *label;
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
	vector<FunctionCall*> forLoopIncr;
	vector<FunctionCall*> forLoopInit;
};

extern int lineIndent;
extern vector<int> lineIndentLevel;

class Line
{
public:
	string original;
	int level;
	vector<FunctionCall*> commands;
	uint lineNumber,originalLineNumber;;
	string processed;
	Scope *scope;
	string comment;
	Function *parentFunction;
	Struct *parentStruct;
	enum LineType {UNKNOWN,INTERPRETER_COMMAND,FUNCTION_DECLARATION,CODE,CODE_WITH_OPTIONS,LABEL,LABEL_WITH_CODE,STRUCT,STRUCT_MEMBER,EMPTY} type;
	string cString;
	bool split;

	Line( vector<FunctionCall*> &call,Scope *_scope,Function *_parent,int _level);
	Line(string str,uint _lineNumber);
		
	vector<LinePossibility*> findCommands(vector<CallToken> &call);
	void splitCommands(string str);


	void parseNextIsNewVariable(vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt);
	void parseNextIsVariable(vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt);
	void parseNextIsLabel(vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt);
	void parseNextIsFunction(vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt,Function *function);
	void parseCode(vector<CallToken> &call,uint p,vector<LinePossibility*> &functions,vector<CallToken> attempt);

	vector<Line*> getLabels();

	int printC99(FILE *fp,int replacementLevel=-1);
};

void fixLineNumbers() ;
extern map<string,int> labels;
extern map<string,set<Function*>> labelLocations;

void addLabel(string label,Function *location);

extern vector<Line*> lines;
extern vector<Function*> functions;


void returnDefaultC99(FILE *fp,FunctionCall *call);
void returnLabelC99(FILE *fp,FunctionCall *call);
void gotoC99(FILE *fp,FunctionCall *call);
void switchC99(FILE *fp,FunctionCall *call);
void switchEndC99(FILE *fp,FunctionCall *call);
void caseC99(FILE *fp,FunctionCall *call);
void returnC99(FILE *fp,FunctionCall *call);
void caseEndC99(FILE *f,FunctionCall *call);
void continueC99(FILE *fp,FunctionCall *call);
void continueDefaultC99(FILE *fp,FunctionCall *call);
void continueCaseC99(FILE *fp,FunctionCall *call);
void defaultC99(FILE *fp,FunctionCall *call);
void structMemberC99(FILE *fp,FunctionCall *call);
void memberC99(FILE *fp,FunctionCall *call);
void setToDefaultC99(FILE *fp,FunctionCall *call);