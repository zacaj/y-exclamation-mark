#pragma once
#include "common.h"
#include "main.h"



class Int:public Type
{
public:
	int value;
	Int()
	{
		value=0;
		name="int";
	}
	string getLlvmType()
	{
		return "i32";
	}
	string getC99Type()
	{
		return "int";
	}
	string getC99Constant()
	{
		return i2s(value);
	}
	string getC99Default()
	{
		return "0";
	}
};

class String:public Type
{
public:
	string value;
	String()
	{
		name="string";
	}
	string getLlvmType()
	{
		return "i8*";
	}
	string getC99Type()
	{
		return "char*";
	}
	string getC99Constant()
	{
		return value;
	}
	string getC99Default()
	{
		return "";
	}
};

class Bool:public Type
{
public:
	bool value;
	Bool()
	{
		value=0;
		name="bool";
	}

	string getLlvmType()
	{
		return "i1";
	}
	string getC99Type()
	{
		return "unsigned char";
	}
	string getC99Constant()
	{
		return i2s(value);
	}
	string getC99Default()
	{
		return "0";
	}
};

class Branch:public Type
{
public:
	string destination;
	bool repeat;
	Branch()
	{
		name="branch";
	}
	string getC99Type()
	{
		return "branch_t";
	}
	string getC99Constant()
	{
		return i2s(labels[destination]);
	}
};

class Label:public Type
{
public:
	string label;
	Label()
	{
		name="Label";
	}
	string getC99Type()
	{
		return "int";
	}
};

class Var:public Type
{
public:
	string label;
	Var()
	{
		name="var";
	}
	string getC99Type()
	{
		return "void";
	}
};
extern map<string,Type*> types;

Type* getType(string name);

Type* parseConstant(string str);