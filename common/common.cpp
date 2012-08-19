#include "common.h"
#include <stdarg.h>

 string invisibleCharacers=" ";
 string lowerLetters,upperLetters,numerals;
 spos npos=string::npos;

int fileExists(const char *path)
{
	FILE *fp=fopen(path,"r");
	if(fp==NULL)
		return 0;
	fclose(fp);
	return 1;
}

string pathToFile(string name)
{
	return string("h:/source/data/")+name;
}

string getFile(string path)
{
	int i;
	for(i=path.size()-1;i>=0;i--)
	{
		if(path[i]=='/' || path[i]=='\\')
			break;
	}
	if(i!=0)
	{
		i++;
		return(path.substr(i,path.length()-i));
	}
	else
		return path;
}

string getExt(string path)
{
	size_t pos=path.rfind('.');
	if(pos!=path.npos)
		return(path.substr(pos+1,path.length()-pos-1));
	else
		return "";
}

inline void printOut(const char *str)
{
	//FILE *fp=fopen("out.txt","a+");
	printf(str);
	//fprintf(fp,str);
	//	fclose(fp);
}

void _print(const char *format, ...)
{
#ifdef DEBUG
	char debug_str[256];
	va_list ap;
	va_start(ap,format);
	vsprintf(debug_str,format,ap);
	va_end(ap);
	printf(debug_str);
#else
#endif
}
void _error(string file,const char *format, ...)
{
	char debug_str[256];
	va_list ap;
	va_start(ap,format);
	vsprintf(debug_str,format,ap);
	va_end(ap);
	printf("[%s: %s",file.c_str(),debug_str);
	BREAK;
}

void _debug(const char *format, ...)
{
#ifdef DEBUG
	char debug_str[256];
	va_list ap;
	va_start(ap,format);
	vsprintf(debug_str,format,ap);
	va_end(ap);
	printOut(debug_str);
#else
#endif
}

size_t removeLeadingTrailingSpaces( string &str )
{
	if(str.empty())
		return 0;
	size_t notSpace=str.find_first_not_of(' ');
	if(notSpace!=string::npos)
		str.erase(str.begin(),str.begin()+notSpace);
	while(str.back()==' ') str.erase(str.size()-1);
	if(notSpace==npos)
		return 0;
	return notSpace;
}

size_t find( string str,string characters,size_t start/*=0*/ )
{
	size_t first=str.size();
	for(int i=0;i<characters.size();i++)
	{
		size_t pos=str.find(characters[i],start);
		if(pos<first)
			first=pos;
	}
	return first;
}

size_t find_not( string str,string characters,size_t start/*=0*/ )
{
	size_t first=str.size();
	for(int i=start;i<str.size();i++)
	{
		int j=0;
		for(;j<characters.size();j++)
		{
			if(str[i]==characters[j])
				break;
		}
		if(j==characters.size())
			return i;
	}
	return first;
}

void initCommon()
{
	for(int i=0;i<32;i++)
		invisibleCharacers.push_back(i);
	for(char c='a';c<='z';c++)
		lowerLetters.push_back(c);
	for(char c='A';c<='Z';c++)
		upperLetters.push_back(c);
	for(char c='0';c<='9';c++)
		numerals.push_back(c);
}

std::string i2s( int i )
{
	char str[100];
	sprintf(str,"%i",i);
	return str;
}

bool isnumber( string str )
{
	for(int i=0;i<str.size();i++)
		if(!isdigit(str[i]))
			return 0;
	return 1;
}

std::string tokenize( string str )
{
	for(int i=0;i<str.size();i++)
		if(!isalnum(str[i]))
		{
			str[i]='_';
			if(i!=0)
			{
				if(str[i-1]=='_')
				{
					str.erase(i--);
				}
			}
		}
	return str;
}

char* cstr( string &str )
{
	char *c=new char[str.size()];
	strcpy(c,str.c_str());
	return c;
}
