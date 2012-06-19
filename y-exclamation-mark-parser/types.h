#pragma once
#include "common.h"

class Type
{
public:
	string name;
	virtual bool is(string typeName)
	{
		if(typeName=="internal")
			return 1;
		return typeName==name;
	}
	virtual string getLlvmType()=0;
	virtual string getC99Type()=0;
	virtual string getC99Constant()=0;
};


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
};

extern map<string,Type*> types;

Type* getType(string name);