#include "Quaternion.h"
#include <math.h>
#include "mat4f.h"
Quaternion::Quaternion(void)
{
	x=y=z=0;
	w=1;
}


Quaternion Quaternion::normalized()
{

	Quaternion q(*this);
	float l=q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w;
	if(l!=1)
		l=sqrt(l);
	q.x/=l;
	q.y/=l;
	q.z/=l;
	q.w/=l;
	return q;
}

void Quaternion::normalize()
{
	*this=normalized();
}

Quaternion Quaternion::conjugate()
{
	x=-x;
	y=-y;
	z=-z;
	return *this;
}

void Quaternion::axisAngle( vec3f v,float a )
{
	float angle=(float)((a/180.0f)*M_PI);

	float result=(float)sin(angle/2.0f);

	w=(float)cos(angle/2.0f);

	x=(v.x*result);
	y=(v.y*result);
	z=(v.z*result);
}

void Quaternion::YXZ( vec3f a )
{
	float cy = (float)cos(a.y*DEG2RAD/2);
	float sy = (float)sin(a.y*DEG2RAD/2);
	float cx = (float)cos(a.x*DEG2RAD/2);
	float sx = (float)sin(a.x*DEG2RAD/2);
	float cz = (float)cos(a.z*DEG2RAD/2);
	float sz = (float)sin(a.z*DEG2RAD/2);
	float sysz=sy*sz;
	float cycz=cy*cz;
	w=cycz*cx-sysz*sx;
	x=sysz*cx+cycz*sx;
	y=sy*cz*cx+cy*sz*sx;
	z=cy*sz*cx-sy*cz*sx;
}

void Quaternion::ZYX( vec3f a )
{
	float cy = (float)cos(a.y*DEG2RAD/2);
	float sy = (float)sin(a.y*DEG2RAD/2);
	float cx = (float)cos(a.x*DEG2RAD/2);
	float sx = (float)sin(a.x*DEG2RAD/2);
	float cz = (float)cos(a.z*DEG2RAD/2);
	float sz = (float)sin(a.z*DEG2RAD/2);
	float sysz=sy*sz;
	float cycz=cy*cz;
	w=cycz*cx-sysz*sx;
	x=sysz*cx+cycz*sx;
	y=sy*cz*cx+cy*sz*sx;
	z=cy*sz*cx-sy*cz*sx;
}

Quaternion::operator mat4f()
{
	//mat4f mat;
	float mat[16];
	float sqw = w*w;
	float sqx = x*x;
	float sqy = y*y;
	float sqz = z*z;

	// invs (inverse square length) is only required if quaternion is not already normalised
	float invs = 1 ;/// (sqx + sqy + sqz + sqw);
	mat[0] = ( sqx - sqy - sqz + sqw)*invs ; // since sqw + sqx + sqy + sqz =1/invs*invs
	mat[5] = (-sqx + sqy - sqz + sqw)*invs ;
	mat[10] = (-sqx - sqy + sqz + sqw)*invs ;

	float tmp1 = x*y;
	float tmp2 = z*w;
	mat[4] = (float)2.0 * (tmp1 + tmp2)*invs ;
	mat[1] = (float)2.0 * (tmp1 - tmp2)*invs ;

	tmp1 = x*z;
	tmp2 = y*w;
	mat[8] = (float)2.0 * (tmp1 - tmp2)*invs ;
	mat[2] = (float)2.0 * (tmp1 + tmp2)*invs ;
	tmp1 = y*z;
	tmp2 = x*w;
	mat[9] = (float)2.0 * (tmp1 + tmp2)*invs ;
	mat[6] = (float)2.0 * (tmp1 - tmp2)*invs ;
	mat[3]=mat[7]=mat[11]=0.0;
	mat[15]=1;
	mat[3]=mat[7]=mat[11]=mat[12]=mat[13]=mat[14]=0;
	return mat4f(mat);
}