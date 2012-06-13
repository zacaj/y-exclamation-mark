#include "types.h"
#include "main.h"

map<string,Type*> types;

Type* getType( string name )
{
	map<string,Type*>::iterator it=types.find(name);
	checkError(it==types.end(),"Type %s not defined",name.c_str());
	return it->second;
}
