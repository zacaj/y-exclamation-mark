#pragma once

#include "common.h"
#include "vec3.h"

class mat4f;
/// Quaternion.  Look it up.
class Quaternion
{
public:
	float x,y,z,w;
	Quaternion(void);
	/**
		Makes a quaternion from a YXZ Euler rotation

		*/
	Quaternion(vec3f rot)
	{
		YXZ(rot);
	}
	Quaternion(vec3f axis,float angle)
	{
		axisAngle(axis,angle);
	}
	Quaternion(float X,float Y,float Z,float W)
	{
	    x=X;
	    y=Y;
	    z=Z;
	    w=W;
	}
	Quaternion(vec4f v)
	{
		x=v.x;
		y=v.y;
		z=v.z;
		w=v.w;
	}
	Quaternion normalized();
	void normalize();
	Quaternion conjugate();
	void axisAngle(vec3f v,float a);
	void YXZ(vec3f a);
	void ZYX( vec3f a );
	Quaternion& operator = (const Quaternion &q)
	{
		x=q.x;
		y=q.y;
		z=q.z;
		w=q.w;
		return *this;
	}
	operator vec4f()
	{
		return vec4f(x,y,z,w);
	}
	operator string()
	{
		char temp[256];
		sprintf(temp,"(%2.3f %2.3f %2.3f %2.3f\n",x,y,z,w);
		string ret=temp;
		return ret;
	}
	operator mat4f();
	Quaternion operator * (const Quaternion &q)
	{
		Quaternion C;

		C.x = w*q.x + x*q.w + y*q.z - z*q.y;
		C.y = w*q.y - x*q.z + y*q.w + z*q.x;
		C.z = w*q.z + x*q.y - y*q.x + z*q.w;
		C.w = w*q.w - x*q.x - y*q.y - z*q.z;
		return C;
	}
	Quaternion operator *= (const Quaternion &q)
	{
		(*this)=(*this) * q;
		return *this;
	}
};
