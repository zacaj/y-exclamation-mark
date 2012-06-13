#pragma once

#include "common.h"
class mat4f;

template <class T>
class vec4
{
public:
	T x,y,z,w;
	vec4(){}
	vec4(T t)
	{
		x=y=z=w=t;
	}
	vec4(T _x,T _y,T _z,T _w)
	{
		x=_x;
		y=_y;
		z=_z;
		w=_w;
	}
	inline float magnitude()
	{
		return sqrt(x*x+y*y+z*z+w*w);
	}
	vec4<T> operator /= (const float f)
	{
		x/=f;
		y/=f;
		z/=f;
		w/=f;
		return *this;
	}
	vec4<T> operator * (const mat4f &m) const//note probably not correct for axis oriantation used
	{
		vec4<T> r;
		r.x=x * m.m[0] +
			y * m.m[1] +
			z * m.m[2] +
			w*m.m[3];

		r.y=x * m.m[4] +
			y * m.m[5] +
			//	z * m.m[6] +//assimp uses left handed y up
			//m.m[7];
			z*m.m[6] + 
			w*m.m[7];

		r.z=x * m.m[8] +
			y * m.m[9] +
			//	z * m.m[10] +
			//m.m[11];
			z * m.m[10] +
			w*m.m[11];
		r.w=x*m.m[12] +
			y*m.m[13]+
			z*m.m[14]+
			w*m.m[15];
		return r;
	}
	vec4<T> operator *= (const mat4f &m)
	{
		(*this)=(*this)*m;
		return *this;
	}
};

typedef vec4<float> vec4f;
typedef vec4<double> vec4d;
typedef vec4<int> vec4i;
typedef vec4<uint> vec4u;
typedef vec4<uchar> vec4b;
typedef vec4<char> vec4c;