#include "file.h"
#include "vec3.h"
#include "mat4f.h"

void skipToString(FILE *fp,char *str)
{
	while(!feof(fp))
	{
		char c=fgetc(fp);
		if(c==str[0])
		{
			int i=0;
			while(str[i]!='\n')
				if(fgetc(fp)!=str[i])
				{
					i=-1;
					break;
				}
				else
					i++;
			if(i!=-1)
				return;
		}
	}
}
void skipTo(FILE *fp,char g)
{
	while(!feof(fp))
	{
		char c=fgetc(fp);
		if(c==g)
			return;
	}
}
void skipBackTo(FILE *fp,char g)
{
	while(!feof(fp))
	{
		fseek(fp,-2,SEEK_CUR);
		char c=fgetc(fp);
		if(c==g)
			return;
	}
}
char skipBackWhile(FILE *fp,char g)
{
	while(!feof(fp))
	{
		fseek(fp,-2,SEEK_CUR);
		char c=fgetc(fp);
		if(c==g)
			continue;
		return c;
	}
	return 0;
}
char skipWhile(FILE *fp,char g)
{
	while(!feof(fp))
	{
		char c=fgetc(fp);
		if(c==g)
			continue;
		return c;
	}
	return 0;
}
string readTo(FILE *fp,char g)
{
	string ret;
	while(!feof(fp))
	{
		char c=fgetc(fp);
		if(feof(fp))
			break;
		if(c==g)
		{
			break;
		}
		else
			ret+=c;
	}
	return ret;
}
#ifndef WASCII
void wuchar( uchar n,FILE *fp )
{
	fwrite(&n,sizeof(uchar),1,fp);
}

void wfloat( float n,FILE *fp )
{
	fwrite(&n,sizeof(float),1,fp);
}

void wstr( string str,FILE *fp )
{
	wuint(str.size(),fp);
	for(int iLetter=0;iLetter<str.size();iLetter++)
		wuchar(str[iLetter],fp);
}

void wuint( uint n,FILE *fp )
{
	fwrite(&n,sizeof(uint),1,fp);
}

void wvec3f( vec3f v,FILE *fp )
{
	wfloat(v.x,fp);
	wfloat(v.y,fp);
	wfloat(v.z,fp);
}

void wvec4f( vec4f v,FILE *fp )
{
	wfloat(v.x,fp);
	wfloat(v.y,fp);
	wfloat(v.z,fp);
	wfloat(v.w,fp);
}

void wvec4u( vec4u v,FILE *fp )
{
	wuint(v.x,fp);
	wuint(v.y,fp);
	wuint(v.z,fp);
	wuint(v.w,fp);
}

void wmat4f( mat4f m,FILE *fp )
{
	for(int i=0;i<16;i++)
		wfloat(m[i],fp);
}

uchar ruchar( FILE *fp )
{
	uchar n;
	fread(&n,sizeof(uchar),1,fp);
	return n;
}

uint ruint( FILE *fp )
{
	uint n;
	fread(&n,sizeof(uint),1,fp);
	return n;
}
float rfloat( FILE *fp )
{
	float n;
	fread(&n,sizeof(float),1,fp);
	return n;
}

std::string rstr( FILE *fp )
{
	uint l=ruint(fp);
	string r;
	for(int i=0;i<l;i++)
	{
		r.push_back(fgetc(fp));
	}
	return r;
}

vec3f rvec3f( FILE *fp )
{
	vec3f v;
	v.x=rfloat(fp);
	v.y=rfloat(fp);
	v.z=rfloat(fp);
	return v;
}

vec4f rvec4f( FILE *fp )
{
	vec4f v;
	v.x=rfloat(fp);
	v.y=rfloat(fp);
	v.z=rfloat(fp);
	v.w=rfloat(fp);
	return v;
}

vec4u rvec4u( FILE *fp )
{
	vec4u v;
	v.x=ruint(fp);
	v.y=ruint(fp);
	v.z=ruint(fp);
	v.w=ruint(fp);
	return v;
}

mat4f rmat4f(FILE *fp)
{
	mat4f m;
	for(int i=0;i<16;i++)
		m[i]=rfloat(fp);
	return m;
}

uchar rid( FILE *fp )
{
	return ruchar(fp);
}

#else
void wuchar( uchar n,FILE *fp )
{
	fprintf(fp,"%i\n",n);
}

void wfloat( float n,FILE *fp )
{
	fprintf(fp,"%f\n",n);
}

void wstr( string str,FILE *fp )
{
	wuint(str.size(),fp);
	fprintf(fp,"%s\n",str.c_str());
}

void wuint( uint n,FILE *fp )
{
	fprintf(fp,"%i\n",n);
}

void wvec3f( vec3f v,FILE *fp )
{
	fprintf(fp,"%f,%f,%f\n",v.x,v.y,v.z);
}

void wvec4f( vec4f v,FILE *fp )
{
	fprintf(fp,"%f,%f,%f,%f\n",v.x,v.y,v.z,v.w);
}

void wvec4u( vec4u v,FILE *fp )
{
	fprintf(fp,"%i,%i,%i,%i\n",v.x,v.y,v.z,v.w);
}

void wmat4f( mat4f m,FILE *fp )
{
	for(int i=0;i<16;i++)
		wfloat(m[i],fp);
}
uchar ruchar( FILE *fp )
{
	uint n;
	fscanf(fp,"%i\n",&n);
	return n;
}

uint ruint( FILE *fp )
{
	uint n;
	fscanf(fp,"%i\n",&n);
	return n;
}

float rfloat( FILE *fp )
{
	float n;
	fscanf(fp,"%f\n",&n);
	return n;
}

std::string rstr( FILE *fp )
{
	uint l=ruint(fp);
	string r;
	for(int i=0;i<l;i++)
	{
		r.push_back(fgetc(fp));
	}
	fgetc(fp);
	return r;
}

vec3f rvec3f( FILE *fp )
{
	vec3f v;
	fscanf(fp,"%f,%f,%f\n",&v.x,&v.y,&v.z);
	return v;
}
vec4f rvec4f( FILE *fp )
{
	vec4f v;
	fscanf(fp,"%f,%f,%f,%f\n",&v.x,&v.y,&v.z,&v.w);
	return v;
}

vec4u rvec4u( FILE *fp )
{
	vec4u v;
	fscanf(fp,"%u,%u,%u,%u\n",&v.x,&v.y,&v.z,&v.w);
	return v;
}
uchar rid( FILE *fp )
{
	skipTo(fp,'(');
	uint id;
	fscanf(fp,"%i)\n",&id);
	return id;
}

mat4f rmat4f(FILE *fp)
{
	mat4f m;
	for(int i=0;i<16;i++)
		m[i]=rfloat(fp);
	return m;
}

#endif
bool ridc( FILE *fp,uchar correctID )
{
	uchar id=rid(fp);
	if(id!=correctID)
		error("Expected id %i, read %i\n",correctID,id);
	return id==correctID;
}