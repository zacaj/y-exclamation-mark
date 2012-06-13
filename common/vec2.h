#pragma once

#include "common.h"
#include "vec3.h"

template <class T>
class vec2
{
public:
	T x,y;
	vec2()
	{
		x=y=0;
	}
	vec2(T t)
	{
		x=y=t;
	}
	vec2(T _x,T _y)
	{
		x=_x;
		y=_y;
	}
	vec2(vec3<T> v)
	{
		x=v.x;
		y=v.y;
	}
	vec2<T> operator + (const vec2<T> &v) const
	{
		return vec2<T>(x+v.x,y+v.y);
	}
	vec2<T> operator * (const float &f) const
	{
		return vec2<T>(x*f,y*f);
	}
	vec2<T> operator / (const float &f) const
	{
		return vec2<T>(x/f,y/f);
	}
	vec2<T>& operator /= (const float &s)
	{
		x/=s;
		y/=s;
		return *this;
	}
	vec2<T>& operator *= (const float &s)
	{
		x*=s;
		y*=s;
		return *this;
	}
	vec2<T>& operator -= (const float &s)
	{
		x-=s;
		y-=s;
		return *this;
	}
	bool operator == (const vec2<T> &v)
	{
		return v.x==x && v.y==y;
	}
	bool operator != (const vec2<T> &v)
	{
		return v.x!=x || v.y!=y;
	}
};

typedef vec2<float> vec2f;
typedef vec2<double> vec2d;
typedef vec2<int> vec2i;
typedef vec2<uint> vec2u;
typedef vec2<uchar> vec2b;
typedef vec2<char> vec2c;