#include "main.h"
#include "types.h"

void indentLine(FILE *fp,int level);

void Scope::writeC99(FILE *fp)
{
	for(map<string,Variable*>::iterator it=variables.begin();it!=variables.end();it++)
	{
		Variable *var=it->second;
		if(var->mode&Ob(100000))
			continue;
		indentLine(fp,level);
		fprintf(fp,"%s %s",var->type->getC99Type().c_str(),var->name.c_str());
		if(var->constant!=NULL)
		{
			fprintf(fp," = %s",var->constant->getC99Constant().c_str());
		}
		fprintf(fp,";\n");
	}
	fprintf(fp,"\n");
}

void Function::printC99Declaration(FILE *fp)
{
	if(ret!=NULL)
	{
		fprintf(fp,"%s ",ret->type->getC99Type().c_str());
	}
	else
		fprintf(fp,"void ");

	bool first=1;

	fprintf(fp,"%s ( ",processedFunctionName.c_str());

	first=1;
	for(int i=0;i<name.size();i++)
	{
		if(name[i]->var!=NULL)
		{
			Variable *var=name[i]->var;
			if(first)
				first=0;
			else
				fprintf(fp,", ");
			fprintf(fp,"%s %s",var->type->getC99Type().c_str(),var->name.c_str());
		}
	}
	fprintf(fp," )");
}

void outputC99(FILE *fp)
{
	fprintf(fp,"#include <stdio.h>\n");
	fprintf(fp,"int main(int argc,char **argv)\n");
	fprintf(fp,"{\n");
	fprintf(fp,"\treturn startint(argc);\n");
	fprintf(fp,"}\n\n");
	for(int i=0;i<functions.size();i++)
	{
		Function *func=functions[i];
		for(int j=0;j<func->name.size();j++)
		{
			if(func->name[j]->var==NULL)
			{
				func->processedFunctionName+=func->name[j]->text;
			}
			else
			{
				func->processedFunctionName+=func->name[j]->var->type->name;
			}
		}
		if(!isalpha(func->processedFunctionName[0]))
			func->processedFunctionName.insert(0,"f");

		for(int j=0;j<func->processedFunctionName.size();j++)
		{
			char c=func->processedFunctionName[j];
			string replacement="Q";
			if(!isalnum(c) && c!='_')
			{
				switch(c)
				{
				case '+':
					replacement="plus";
					break;
				case '*':
					replacement="asterisk";
					break;
				case '=':
					replacement="equal";
					break;
				case '<':
					replacement="less";
					break;
				default:
					warn("No known replacement for %c\n",c);
					break;
				}

				replacement.insert(0,"_");
				replacement.push_back('_');
				func->processedFunctionName.erase(j,1);
				func->processedFunctionName.insert(j,replacement);
				j+=replacement.size();
			}
		}
	}
	for(int iFunc=0;iFunc<functions.size();iFunc++)
	{
		Function *func=functions[iFunc];
		func->printC99Declaration(fp);
		fprintf(fp,";\n");
	}
	fprintf(fp,"\n\n");

	for(int iFunc=0;iFunc<functions.size();iFunc++)
	{
		Function *func=functions[iFunc];
		func->printC99Declaration(fp);
		fprintf(fp,"\n{\n");
		if(func->ret!=NULL)
			if(func->ret->name.size())
			{
				fprintf(fp,"\t%s %s;\n",func->ret->type->getC99Type().c_str(),func->ret->name.c_str());
			}


		Line *lastLine=NULL;
		for(int i=0;i<func->lines.size();i++)
		{
			Line *line=func->lines[i];
			if(lastLine!=NULL && lastLine->level!=line->level)
			{
				if(lastLine->level<line->level)
				{

					for(int i=lastLine->level;i<line->level;i++)
					{
						indentLine(fp,i);
						fprintf(fp,"{\n");
					}
					line->scope->writeC99(fp);
				}
				else if(lastLine->level>line->level)
				{
					for(int i=lastLine->level-1;i>=line->level;i--)
					{
						indentLine(fp,i);
						fprintf(fp,"}\n");
					}
				}
			}
			if(lastLine==NULL)
				line->scope->writeC99(fp);
			for(int j=0;j<line->commands.size();j++)
			{
				FunctionCall *call=line->commands[j];
				indentLine(fp,line->level);
				if(call->ret!=NULL)
					fprintf(fp,"%s =  %s( ",call->ret->name.c_str(),call->function->processedFunctionName.c_str());
				else
					fprintf(fp,"%s( ",call->function->processedFunctionName.c_str());

				for(int k=0;k<call->arguments.size();k++)
				{
					fprintf(fp,"%s",call->arguments[k]->name.c_str());
					if(k==call->arguments.size()-1)
						fprintf(fp," ");
					else
						fprintf(fp,", ");
				}

				fprintf(fp,");\n");
				lastLine=line;
			}
		}
		if(lastLine!=NULL && lastLine->level!=1)
			for(int i=lastLine->level-1;i>=1;i--)
			{
				indentLine(fp,i);
				fprintf(fp,"}\n");
			}

			if(func->ret==NULL)
				fprintf(fp,"}\n");
			else
			{
				indentLine(fp,1);
				fprintf(fp,"return %s;\n}\n",func->ret->name.c_str());
			}

		fprintf(fp,"\n");
		//fprintf(fp,"}\n\n");
	}
}