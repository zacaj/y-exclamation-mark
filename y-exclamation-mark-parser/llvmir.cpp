#include "main.h"

void printLlvmIrCode(FILE *fp)
{
	for(int i=0;i<functions.size();i++)
	{
		Function *func=functions[i];
		for(int j=0;j<func->name.size();j++)
		{
			if(func->name[j]->var==NULL)
			{
				//func->processed
			}
		}
	}
}