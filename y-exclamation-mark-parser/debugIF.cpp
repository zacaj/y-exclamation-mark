#include "main.h"

void debugIntermediateForm(FILE *fp)
{
	for(int iFunc=0;iFunc<functions.size();iFunc++)
	{
		Function *func=functions[iFunc];
		if(func->ret!=NULL)
		{
			fprintf(fp,"r %s ",func->ret->type->name.c_str());
			if(func->ret->name.empty())
				fprintf(fp,"NONE ");
			else
				fprintf(fp,"%s ",func->ret->name.c_str());
		}
		else
			fprintf(fp,"r void ret");


	}
}