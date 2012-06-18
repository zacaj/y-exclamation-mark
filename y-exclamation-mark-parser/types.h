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
};

class InternalType:public Type
{
public:
	virtual string getLlvmType()=0;
};

class Int:public InternalType
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
};

class String:public InternalType
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
};

class Bool:public InternalType
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
};

extern map<string,Type*> types;

Type* getType(string name);