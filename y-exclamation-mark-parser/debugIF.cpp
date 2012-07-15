#include "main.h"
#include "types.h"

void debugIntermediateForm(FILE *fp)
{
	for(int iFunc=0;iFunc<functions.size();iFunc++)
	{
		Function *func=functions[iFunc];
		string name;
		bool first=1;
		for(int i=0;i<func->name.size();i++)
		{
			if(func->name[i]->var==NULL)
			{
				if(first)
				{
					first=0;
					name+=func->name[i]->text;
				}
				else
				{
					name.push_back(toupper(func->name[i]->text[0]));
					name+=func->name[i]->text.substr(1,func->name[i]->text.size()-1).c_str();
				}
			}
		}
		func->processedFunctionName=(name);
	}
	for(int iFunc=0;iFunc<functions.size();iFunc++)
	{
		Function *func=functions[iFunc];
		if(func->ret!=NULL)
		{
			fprintf(fp,"%s ",func->ret->type->name.c_str());
			if(func->ret->name.empty())
				fprintf(fp,"NONE ");
			else
				fprintf(fp,"%s ",func->ret->name.c_str());
		}
		else
			fprintf(fp,"NORETURN ");

		bool first=1;
		
		fprintf(fp,"%s ( ",func->processedFunctionName.c_str());

		first=1;
		for(int i=0;i<func->name.size();i++)
		{
			if(func->name[i]->var!=NULL)
			{
				Variable *var=func->name[i]->var;
				if(first)
					first=0;
				else
					fprintf(fp,", ");
				fprintf(fp,"%s %s",var->type->name.c_str(),var->name.c_str());
			}
		}
		fprintf(fp," )\n");
		//fprintf(fp," )\n{\n");

		for(int i=func->firstLine->lineNumber;i<func->lastLine->lineNumber;i++)
		{
			Line *line=lines[i];
			for(int j=0;j<line->commands.size();j++)
			{
				FunctionCall *call=line->commands[j];
				for(int k=0;k<line->level;k++)
					fprintf(fp,"\t");
				if(call->ret!=NULL)
					fprintf(fp,"RET %s :=  %s(",call->ret->name.c_str(),call->function->processedFunctionName.c_str());
				else
					fprintf(fp,"%s ( ",call->function->processedFunctionName.c_str());

				for(int k=0;k<call->arguments.size();k++)
				{
					fprintf(fp,"%s",call->arguments[k]->name.c_str());
					if(k==call->arguments.size()-1)
						fprintf(fp," ");
					else
						fprintf(fp,", ");
				}

				fprintf(fp,")\n");
			}
		}

		fprintf(fp,"\n");
		//fprintf(fp,"}\n\n");
	}
}