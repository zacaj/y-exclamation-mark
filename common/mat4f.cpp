#include "mat4f.h"
#include <math.h>
#include "Quaternion.h"

mat4f::mat4f(void)
{
	identity();
}

mat4f::mat4f(float s)
{
	for(int i=0;i<16;i++)
		m[i]=s;
}

mat4f::mat4f( const float *data )
{
	//for(int i=0;i<16;i++)
	//	m[i]=data[i];
	memcpy(m,data,sizeof(float)*16);
}

mat4f::mat4f( bool t )
{

}

mat4f::~mat4f(void)
{
}

mat4f mat4f::transposed() const
{
	float r[16];
	r[0]=m[0];
	r[1]=m[4];
	r[2]=m[8];
	r[3]=m[12];
	r[4]=m[1];
	r[5]=m[5];
	r[6]=m[9];
	r[7]=m[13];
	r[8]=m[2];
	r[9]=m[6];
	r[10]=m[10];
	r[11]=m[14];
	r[12]=m[3];
	r[13]=m[7];
	r[14]=m[11];
	r[15]=m[15];
	return mat4f(r);
}

void mat4f::perspective(float fov,float znear,float zfar,float aspect)
{
    float xymax = znear * (float)tan(fov * (M_PI/360.f));
    float ymin = -xymax;
    float xmin = -xymax;

    float width = xymax - xmin;
    float height = xymax - ymin;

    float depth = zfar - znear;
    float q = -(zfar + znear) / depth;
    float qn = -2 * (zfar * znear) / depth;

    float w = 2 * znear / width;
    w = w / aspect;
    float h = 2 * znear / height;
	m[0]  = w;m[1]  = 0;m[2]  = 0;m[3] = 0;

	m[4]  = 0;m[5]  = h;m[6]  = 0;m[7] = 0;

	m[8]  = 0;m[9]  = 0;m[10] = q;m[11] =qn;

	m[12]  = 0;m[13]  = 0;m[14] = -1;m[15] = 0;/**/

}

void mat4f::axisAngle(vec3f axis,float angle)
{
	float c = (float)cos(angle*DEG2RAD);
	float s = (float)sin(angle*DEG2RAD);
	float t = 1.f - c;
	//  if axis is not already normalized then uncomment this
	// double magnitude = Math.sqrt(a1.x*a1.x + a1.y*a1.y + a1.z*a1.z);
	// if (magnitude==0) throw error;
	// a1.x /= magnitude;
	// a1.y /= magnitude;
	// a1.z /= magnitude;
	m[0] = c + axis.x*axis.x*t;
	m[5] = c + axis.y*axis.y*t;
	m[10] = c + axis.z*axis.z*t;

	float tmp1 = axis.x*axis.y*t;
	float tmp2 = axis.z*s;
	m[4] = tmp1 + tmp2;
	m[1] = tmp1 - tmp2;
	tmp1 = axis.x*axis.z*t;
	tmp2 = axis.y*s;
	m[8] = tmp1 - tmp2;
	m[2] = tmp1 + tmp2;    tmp1 = axis.y*axis.z*t;
	tmp2 = axis.x*s;
	m[9] = tmp1 + tmp2;
	m[6] = tmp1 - tmp2;
}
void mat4f::printf()
{
	print("\n%2.3f %2.3f %2.3f %2.3f\n%2.3f %2.3f %2.3f %2.3f\n%2.3f %2.3f %2.3f %2.3f\n%2.3f %2.3f %2.3f %2.3f\n"
		,m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
}
void mat4f::lookAt(float centerx, float centery, float centerz,
	float upx, float upy, float upz)
{
    float x[3], y[3], z[3];
    float mag;  
    /* Make rotation matrix */
    
    /* Z vector */
    z[0] = - centerx;
    z[1] = - centery;
    z[2] = - centerz;
    mag = sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
    if (mag) {          /* mpichler, 19950515 */
        z[0] /= mag;
        z[1] /= mag;
        z[2] /= mag;
    }
    
    /* Y vector */
    y[0] = upx;
    y[1] = upy;
    y[2] = upz;
    
    /* X vector = Y cross Z */
    x[0] = y[1] * z[2] - y[2] * z[1];
    x[1] = -y[0] * z[2] + y[2] * z[0];
    x[2] = y[0] * z[1] - y[1] * z[0];
    
    /* Recompute Y = Z cross X */
    y[0] = z[1] * x[2] - z[2] * x[1];
    y[1] = -z[0] * x[2] + z[2] * x[0];
    y[2] = z[0] * x[1] - z[1] * x[0];
    
    /* mpichler, 19950515 */
    /* cross product gives area of parallelogram, which is < 1.0 for
     * non-perpendicular unit-length vectors; so normalize x, y here
     */
    
    mag = sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
    if (mag) {
        x[0] /= mag;
        x[1] /= mag;
        x[2] /= mag;
    }
    
    mag = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
    if (mag) {
        y[0] /= mag;
        y[1] /= mag;
        y[2] /= mag;
    }
    
#define M(row,col)  m[col+row*4]
    M(0, 0) = x[0];
    M(0, 1) = x[1];
    M(0, 2) = x[2];
    M(0, 3) = 0.0;
    M(1, 0) = y[0];
    M(1, 1) = y[1];
    M(1, 2) = y[2];
    M(1, 3) = 0.0;
    M(2, 0) = z[0];
    M(2, 1) = z[1];
    M(2, 2) = z[2];
    M(2, 3) = 0.0;
    M(3, 0) = 0.0;
    M(3, 1) = 0.0;
    M(3, 2) = 0.0;
    M(3, 3) = 1.0;
#undef M    
}

void mat4f::scaleTo( vec3f s )
{
	m[0]=s.x;
	m[5]=s.y;
	m[10]=s.z;
}

mat4f mat4f::mat3f()
{
	float r[16];
	r[0]=m[0];
	r[1]=m[1];
	r[2]=m[2];
	r[3]=0;
	r[4]=m[4];
	r[5]=m[5];
	r[6]=m[6];
	r[7]=0;
	r[8]=m[8];
	r[9]=m[9];
	r[10]=m[10];
	r[11]=0;
	r[12]=0;
	r[13]=0;
	r[14]=0;
	r[15]=1;
	return mat4f(r);
}

void mat4f::orthographic( float left,float right,float bottom,float top,float zNear,float zFar )
{
	m[0]=2.f/(right-left);
	m[4]=m[8]=0;
	m[3]=-(right+left)/(right-left);
	m[1]=0;
	m[5]=2.f/(top-bottom);
	m[9]=0;
	m[7]=-(top+bottom)/(top-bottom);
	m[2]=m[6]=0;
	m[10]-2.f/(zFar-zNear);
	m[11]=-(zFar+zNear)/(zFar-zNear);
	m[12]=m[13]=m[14]=0;
	m[15]=1;
}
mat4f & mat4f::operator = (const Quaternion &q)
{
	float sqw = q.w*q.w;
	float sqx = q.x*q.x;
	float sqy = q.y*q.y;
	float sqz = q.z*q.z;

	// invs (inverse square length) is only required if quaternion is not already normalised
	float invs = 1 ;/// (sqx + sqy + sqz + sqw);
	m[0] = ( sqx - sqy - sqz + sqw)*invs ; // since sqw + sqx + sqy + sqz =1/invs*invs
	m[5] = (-sqx + sqy - sqz + sqw)*invs ;
	m[10] = (-sqx - sqy + sqz + sqw)*invs ;

	float tmp1 = q.x*q.y;
	float tmp2 = q.z*q.w;
	m[4] = (float)2.0 * (tmp1 + tmp2)*invs ;
	m[1] = (float)2.0 * (tmp1 - tmp2)*invs ;

	tmp1 = q.x*q.z;
	tmp2 = q.y*q.w;
	m[8] = (float)2.0 * (tmp1 - tmp2)*invs ;
	m[2] = (float)2.0 * (tmp1 + tmp2)*invs ;
	tmp1 = q.y*q.z;
	tmp2 = q.x*q.w;
	m[9] = (float)2.0 * (tmp1 + tmp2)*invs ;
	m[6] = (float)2.0 * (tmp1 - tmp2)*invs ;
	m[3]=m[7]=m[11]=0.0;
	m[15]=1;
	m[3]=m[7]=m[11]=m[12]=m[13]=m[14]=0;
	return *this;
}

mat4f mat4f::inversed() const

{
	float a0 = m[ 0]*m[ 5] - m[ 1]*m[ 4];
	float a1 = m[ 0]*m[ 6] - m[ 2]*m[ 4];
	float a2 = m[ 0]*m[ 7] - m[ 3]*m[ 4];
	float a3 = m[ 1]*m[ 6] - m[ 2]*m[ 5];
	float a4 = m[ 1]*m[ 7] - m[ 3]*m[ 5];
	float a5 = m[ 2]*m[ 7] - m[ 3]*m[ 6];
	float b0 = m[ 8]*m[13] - m[ 9]*m[12];
	float b1 = m[ 8]*m[14] - m[10]*m[12];
	float b2 = m[ 8]*m[15] - m[11]*m[12];
	float b3 = m[ 9]*m[14] - m[10]*m[13];
	float b4 = m[ 9]*m[15] - m[11]*m[13];
	float b5 = m[10]*m[15] - m[11]*m[14];

	mat4f inverse;

	float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
	//if (Math<float>::FAbs(det) > epsilon)
	{
		//Matrix4 inverse;
		inverse.m[ 0] = + m[ 5]*b5 - m[ 6]*b4 + m[ 7]*b3;
		inverse.m[ 4] = - m[ 4]*b5 + m[ 6]*b2 - m[ 7]*b1;
		inverse.m[ 8] = + m[ 4]*b4 - m[ 5]*b2 + m[ 7]*b0;
		inverse.m[12] = - m[ 4]*b3 + m[ 5]*b1 - m[ 6]*b0;
		inverse.m[ 1] = - m[ 1]*b5 + m[ 2]*b4 - m[ 3]*b3;
		inverse.m[ 5] = + m[ 0]*b5 - m[ 2]*b2 + m[ 3]*b1;
		inverse.m[ 9] = - m[ 0]*b4 + m[ 1]*b2 - m[ 3]*b0;
		inverse.m[13] = + m[ 0]*b3 - m[ 1]*b1 + m[ 2]*b0;
		inverse.m[ 2] = + m[13]*a5 - m[14]*a4 + m[15]*a3;
		inverse.m[ 6] = - m[12]*a5 + m[14]*a2 - m[15]*a1;
		inverse.m[10] = + m[12]*a4 - m[13]*a2 + m[15]*a0;
		inverse.m[14] = - m[12]*a3 + m[13]*a1 - m[14]*a0;
		inverse.m[ 3] = - m[ 9]*a5 + m[10]*a4 - m[11]*a3;
		inverse.m[ 7] = + m[ 8]*a5 - m[10]*a2 + m[11]*a1;
		inverse.m[11] = - m[ 8]*a4 + m[ 9]*a2 - m[11]*a0;
		inverse.m[15] = + m[ 8]*a3 - m[ 9]*a1 + m[10]*a0;

		float invDet = ((float)1)/det;
		inverse.m[ 0] *= invDet;
		inverse.m[ 1] *= invDet;
		inverse.m[ 2] *= invDet;
		inverse.m[ 3] *= invDet;
		inverse.m[ 4] *= invDet;
		inverse.m[ 5] *= invDet;
		inverse.m[ 6] *= invDet;
		inverse.m[ 7] *= invDet;
		inverse.m[ 8] *= invDet;
		inverse.m[ 9] *= invDet;
		inverse.m[10] *= invDet;
		inverse.m[11] *= invDet;
		inverse.m[12] *= invDet;
		inverse.m[13] *= invDet;
		inverse.m[14] *= invDet;
		inverse.m[15] *= invDet;

		return inverse;
	}

//	return ZERO;
}

void mat4f::setAxes( vec3f right,vec3f up,vec3f backward )
{
	m[0]=right.x;
	m[4]=right.y;
	m[8]=right.z;
	m[1]=up.x;
	m[5]=up.y;
	m[9]=up.z;
	m[2]=backward.x;
	m[6]=backward.y;
	m[10]=backward.z;
}

void mat4f::scaleUnitToExtents( vec3f min,vec3f max )
{
	m[0]=(fabs(max.x)+fabs(min.x))/2;
	m[5]=(fabs(max.y)+fabs(min.y))/2;
	m[10]=(fabs(max.z)+fabs(min.z))/2;
	m[3]=-(fabs(min.x)+fabs(max.x))/2+max.x;
	m[7]=-(fabs(min.y)+fabs(max.y))/2+max.y;
	m[11]=-(fabs(min.z)+fabs(max.z))/2+max.z;
}
