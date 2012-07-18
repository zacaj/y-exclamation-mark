#include "types.h"
#include "main.h"

map<string,Type*> types;

Type* getType( string name )
{
	map<string,Type*>::iterator it=types.find(name);
	checkError(it==types.end(),"Type %s not defined",name.c_str());
	return it->second;
}

Type* parseConstant( string str )
{
	spos pos=0;
	if(str[0]=='\"')//todo set variables for literals
	{
		spos startOfString=0;
		while(pos<str.size()-1)
		{
			pos=find(str,"\"",pos+1);
			if(str[pos-1]!='\\')
				break;
		}
		checkErrors(pos==str.size(),"No closing \" found ");
		string stringContent=str.substr(startOfString,pos-startOfString+1);
		String *cString=new String;
		cString->value=stringContent;
		return cString;
	}
	else if(isdigit(str[0]) || str[0]=='-')//todo variables that start with numbers?
	{
		string num;
		while(pos<str.size() && (isdigit(str[pos]) || str[0]=='-'))
			num.push_back(str[pos++]);
		Int *cInt=new Int();
		cInt->value=atoi(num.c_str());
		return cInt;
	}
}
