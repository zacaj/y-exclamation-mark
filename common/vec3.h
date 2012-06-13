#pragma once

#include "common.h"
#include "vec4.h"
class mat4f;

template <class T>
class vec3
{
public:
	T x,y,z;
	vec3()
	{}
	vec3(T t)
	{
		x=y=z=t;
	}
	vec3(T _x,T _y,T _z)
	{
		x=_x;
		y=_y;
		z=_z;
	}
	float dot(vec3<T> v)
	{
		return x*v.x+y*v.y+z*v.z;
	}
	inline float magnitude()
	{
		return sqrt(x*x+y*y+z*z);
	}
	inline T magnitudesq()
	{
		return x*x+y*y+z*z;
	}
	vec3<T> normalized()
	{
		float mag=magnitude();
		return vec3(x/mag,y/mag,z/mag);
	}
	void normalize()
	{
		float mag=magnitude();
		x/=mag;
		y/=mag;
		z/=mag;
	}
	float dist(vec3<T> b)
	{
		vec3<T> v=*this-b;
		return v.magnitude();
	}
	vec3<T> operator * (const float &f) const
	{
		return vec3<T>(x*f,y*f,z*f);
	}
	vec3<T> operator / (const float &f) const
	{
		return vec3<T>(x/f,y/f,z/f);
	}
	vec3<T> operator + (const vec3<T> &v) const
	{
		return vec3<T>(x+v.x,y+v.y,z+v.z);
	}
	vec3<T> operator - (const vec3<T> &v) const
	{
		return vec3<T>(x-v.x,y-v.y,z-v.z);
	}
	vec3<T> operator * (const vec3<T> &v) const
	{
		return vec3<T>(x*v.x,y*v.y,z*v.z);
	}
	vec3<T> operator += (const T &f)
	{
		x+=f;
		y+=f;
		z+=f;
		return *this;
	}
	vec3<T> operator -= (const T &f)
	{
		x-=f;
		y-=f;
		z-=f;
		return *this;
	}
	vec3<T> operator *= (const T &f)
	{
		x*=f;
		y*=f;
		z*=f;
		return *this;
	}
	vec3<T> operator /= (const T &f)
	{
		x/=f;
		y/=f;
		z/=f;
		return *this;
	}
	vec3<T> operator - () const
	{
		return vec3<T>(-x,-y,-z);
	}
	vec3<T> operator += (const vec3<T> &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		return *this;
	}
	vec3<T> operator * (const mat4f &m) const//note probably not correct for axis oriantation used
	{
		vec3<T> r;
		r.x=x * m.m[0] +
			y * m.m[1] +
			z * m.m[2] +
			m.m[3];

		r.y=x * m.m[4] +
			y * m.m[5] +
		//	z * m.m[6] +//assimp uses left handed y up
			//m.m[7];
			z*m.m[6] - 
			m.m[11];

		r.z=x * m.m[8] +
			y * m.m[9] +
		//	z * m.m[10] +
			//m.m[11];
			z * m.m[10] +
			m.m[7];
		return r;
	}
	vec3<T> operator *= (const mat4f &m)
	{
		(*this)=(*this) * m;
		return *this;
	}
	operator vec4<T>()
	{
		return vec4<T>(x,y,z,1);
	}
};

typedef vec3<float> vec3f;
typedef vec3<double> vec3d;
typedef vec3<int> vec3i;
typedef vec3<unsigned int> vec3u;
typedef vec3<uchar> vec3b;
typedef vec3<char> vec3c;

