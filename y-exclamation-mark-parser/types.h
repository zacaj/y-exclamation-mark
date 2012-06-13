#pragma once
#include "common.h"

class Type
{
public:
	string name;
	virtual bool is(string typeName)
	{
		return typeName==name;
	}
};

class Int:public Type
{
public:
	Int()
	{
		name="int";
	}

};

class String:public Type
{
public:
	String()
	{
		name="string";
	}
};

class Bool:public Type
{
public:
	Bool()
	{
		name="bool";
	}
};

extern map<string,Type*> types;

Type* getType(string name);