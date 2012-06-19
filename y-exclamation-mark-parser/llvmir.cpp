#include "main.h"
#include "types.h"



string getLlvmVariableType(Variable *var)
{
	checkError(!var->type->is("internal"),"type %s does not exist",var->type->name.c_str());
	{
		return var->type->getLlvmType();
	}
}

void indentLine(FILE *fp,int level)
{
	for(int k=0;k<level;k++)
		fprintf(fp,"\t");
}

void printLlvmIrCode(FILE *fp)
{
	fprintf(fp,"define void @main()\n");
	fprintf(fp,"{\n");
	fprintf(fp,"\tcall i32 @startint();\n");
	fprintf(fp,"\tret void;\n");
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
			if(!isalnum(c) && c!='.' && c!='_')
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

				replacement.insert(0,".");
				replacement.push_back('.');
				func->processedFunctionName.erase(j,1);
				func->processedFunctionName.insert(j,replacement);
				j+=replacement.size();
			}
		}
	}


	for(int i=0;i<functions.size();i++)
	{
		Function *func=functions[i];
		fprintf(fp,"define fastcc ");

		if(func->ret==NULL)
			fprintf(fp,"void ");
		else
			fprintf(fp,"%s ",getLlvmVariableType(func->ret).c_str());

		fprintf(fp,"@%s ( ",func->processedFunctionName.c_str());
		for(int j=0;j<func->arguments.size();j++)
		{
			fprintf(fp,"%s %%%s",getLlvmVariableType(func->arguments[j]).c_str(),func->arguments[j]->llvmName().c_str());
			if(j!=func->arguments.size()-1)
				fprintf(fp,", ");
		}
		fprintf(fp,")\n{\n");

		Line *lastLine=NULL;
		for(int iLine=0;iLine<func->lines.size();iLine++)
		{
			Line *line=func->lines[iLine];
			if(lastLine!=NULL && lastLine->level!=line->level)
			{
				if(lastLine->level<line->level)
				{
					for(int i=lastLine->level;i<line->level;i++)
					{
						indentLine(fp,i);
						fprintf(fp,"{\n");
					}
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
			for(int iCall=0;iCall<line->commands.size();iCall++)
			{
				FunctionCall *call=line->commands[iCall];
				indentLine(fp,line->level);
				fprintf(fp,"%s\n",call->llvmCall().c_str());
			}
			lastLine=line;
		}
		if(lastLine!=NULL && lastLine->level!=1)
			for(int i=lastLine->level-1;i>=1;i--)
			{
				indentLine(fp,i);
				fprintf(fp,"}\n");
			}
		if(func->ret==NULL)
			fprintf(fp,"\tret void\n}\n\n");
		else
			fprintf(fp,"\tret %s %%%s\n}\n\n",getLlvmVariableType(func->ret).c_str(),func->ret->llvmName().c_str());
	}
}

string FunctionCall::llvmCall()
{
	string call;
	if(ret!=NULL)
	{
		call+="%"+ret->llvmName()+" = ";
		call+="call "+getLlvmVariableType(ret)+" ";
	}
	else
		call+="call void ";
	call+="@"+function->processedFunctionName+"(";
	for(int i=0;i<arguments.size();i++)
	{
		call+=getLlvmVariableType(arguments[i])+" %"+arguments[i]->llvmName();
	}
	call+=")";
	return call;
}