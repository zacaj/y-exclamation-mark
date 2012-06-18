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
	int value;
	Int()
	{
		value=0;
		name="int";
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
};

extern map<string,Type*> types;

Type* getType(string name);