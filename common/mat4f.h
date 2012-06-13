#pragma once

#include "common.h"
#include "vec3.h"
class Quaternion;



/**
	4x4 float matrix

	0  1  2  3
	4  5  6  7
	8  9  10 11
	12 13 14 15

|   0,0	0,1	0,2	0,3	|
|	1,0	1,1	1,2	1,3	|
|	2,0	2,1	2,2	2,3	|
|	3,0	3,1	3,2	3,3	|
	*/
class mat4f
{
public:
	float m[16];
	mat4f(void);///< Initializes the mat4f to an identity matrix
	~mat4f(void);
	mat4f(bool t);
	mat4f(float s);///< Initializes the mat4f to all \a s
	mat4f(const float *data);///< Initializes the mat4f with 16 floats from \a data
	/**
		Creates an axis angle orientation matrix

		\param axis The axis to rotate around
		\param angle The angle to rotate around \a axis
		*/
	void axisAngle(vec3f axis,float angle);
	/**
		Creates a perspective projection matrix

		\param fov Field of View of the projection (45-90 recommended)
		\param zNear The distance to the near plane of the viewing frustum
		\param zFar The distance to the far plane of the viewing frustum
		\param aspect The aspect ratio for the projection (w/h)
	*/
	void perspective(float fov,float znear,float zfar,float aspect);
	void setAxes(vec3f right,vec3f up,vec3f backward);
	/**
		Creates an orthograpic projection matrix

		If you really cant figure this out, google glOrtho
		*/
	void orthographic( float left,float right,float bottom,float top,float zNear,float zFar );
	void zero() ///< Zeros the matrix
	{
		//for(int i=0;i<16;i++)
		//	m[i]=0;
		memset(m,0,sizeof(float)*16);
	}
	/**
		Creates a matrix that would scale a 2x2x2 cube centered on origin to the extents given

		*/
	void scaleUnitToExtents(vec3f min,vec3f max);
	void identity()///< Creates an identity matrix
	{
		zero();
		m[0]=m[5]=m[10]=m[15]=1;
	}
	/**
		\returns A transposed version of the matrix

		*/
	mat4f transposed() const;
	void transpose()///< Transposes the matrix
	{
		*this=transposed();
	}
	mat4f inversed() const;
	void invert()///< Transposes the matrix
	{
		*this=inversed();
	}
	void lookAt(float centerx, float centery, float centerz,float upx, float upy, float upz);

	void upload(); ///< Uploads the matrix to the current Shader's transform matrix
	void multAndUpload(); ///< Multiplies the current Shader's transorfm matrix
	/**
		Sets the first 3 diagonals to \a s
		*/
	void scaleTo(vec3f s);
	/**
		Makes a new mat4f that only applies the orientation from this mat4f

		\returns That matrix
		*/
	mat4f mat3f();
	/// Extracts position from matrix
	vec3f getPosition()
	{
		return vec3f(m[3],m[7],m[11]);
	}
	mat4f& operator = (const mat4f &mat)
	{
		for(int i=0;i<16;i++)
			m[i]=mat.m[i];
		return *this;
	}
	operator float*()
	{
		return m;
	}
	char* c_str()
	{
		char *temp=new char[256];
		sprintf(temp,"\n%2.3f %2.3f %2.3f %2.3f\n%2.3f %2.3f %2.3f %2.3f\n%2.3f %2.3f %2.3f %2.3f\n%2.3f %2.3f %2.3f %2.3f\n"
			,m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
		return temp;
	}
	operator string()
	{
		char temp[256];
		sprintf(temp,"\n%2.3f %2.3f %2.3f %2.3f\n%2.3f %2.3f %2.3f %2.3f\n%2.3f %2.3f %2.3f %2.3f\n%2.3f %2.3f %2.3f %2.3f\n"
			,m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
		string ret=temp;
		return ret;
	}
	void printf();
	mat4f & operator = (const Quaternion &q);
	mat4f operator + (const mat4f &mat) const
	{
		mat4f r;
		for(int i=0;i<16;i++)
			r.m[i]=m[i]+mat.m[i];
		return r;
	}
	mat4f& operator += (const mat4f &mat)
	{
		for(int i=0;i<16;i++)
			m[i]+=mat.m[i];
		return *this;
	}
	mat4f operator - (const mat4f &mat) const
	{
		mat4f r;
		for(int i=0;i<16;i++)
			r.m[i]=m[i]-mat.m[i];
		return r;
	}
	mat4f& operator -= (const mat4f &mat)
	{
		for(int i=0;i<16;i++)
			m[i]-=mat.m[i];
		return *this;
	}
	mat4f& operator - ()
	{
		for(int i=0;i<16;i++)
			m[i]=-m[i];
		return *this;
	}
	vec3f operator * (const vec3f &v)
	{
		vec3f r;
		r.x=v.x * m[0] +
			v.y * m[1] +
			v.z * m[2] +
			m[3];

		r.y=v.x * m[4] +
			v.y * m[5] +
			v.z * m[6] +
			m[7];

		r.z=v.x * m[8] +
			v.y * m[9] +
			v.z * m[10] +
			m[11];
		/*r.w=v.x*m[12]+
			v.y*m[13]+
			v.z*m[14]+
			m[15]*/
		return r;
	}
	vec4f operator * (const vec4f &v)
	{
		vec4f r;
		r.x=v.x * m[0] +
			v.y * m[1] +
			v.z * m[2] +
			v.w*m[3];

		r.y=v.x * m[4] +
			v.y * m[5] +
			v.z * m[6] +
			v.w*m[7];

		r.z=v.x * m[8] +
			v.y * m[9] +
			v.z * m[10] +
			v.w*m[11];
		r.w=v.x*m[12]+
			v.y*m[13]+
			v.z*m[14]+
			v.w*m[15];
		return r;
	}
	mat4f operator * (const mat4f &mat) const
	{
		//mat4f r;
		float r[16];
		r[0]=m[0]*mat.m[0]+m[1]*mat.m[4]+m[2]*mat.m[8]+m[3]*mat.m[12];
		r[1]=m[0]*mat.m[1]+m[1]*mat.m[5]+m[2]*mat.m[9]+m[3]*mat.m[13];
		r[2]=m[0]*mat.m[2]+m[1]*mat.m[6]+m[2]*mat.m[10]+m[3]*mat.m[14];
		r[3]=m[0]*mat.m[3]+m[1]*mat.m[7]+m[2]*mat.m[11]+m[3]*mat.m[15];

		r[4]=m[4]*mat.m[0]+m[5]*mat.m[4]+m[6]*mat.m[8]+m[7]*mat.m[12];
		r[5]=m[4]*mat.m[1]+m[5]*mat.m[5]+m[6]*mat.m[9]+m[7]*mat.m[13];
		r[6]=m[4]*mat.m[2]+m[5]*mat.m[6]+m[6]*mat.m[10]+m[7]*mat.m[14];
		r[7]=m[4]*mat.m[3]+m[5]*mat.m[7]+m[6]*mat.m[11]+m[7]*mat.m[15];

		r[8]=m[8]*mat.m[0]+m[9]*mat.m[4]+m[10]*mat.m[8]+m[11]*mat.m[12];
		r[9]=m[8]*mat.m[1]+m[9]*mat.m[5]+m[10]*mat.m[9]+m[11]*mat.m[13];
		r[10]=m[8]*mat.m[2]+m[9]*mat.m[6]+m[10]*mat.m[10]+m[11]*mat.m[14];
		r[11]=m[8]*mat.m[3]+m[9]*mat.m[7]+m[10]*mat.m[11]+m[11]*mat.m[15];

		r[12]=m[12]*mat.m[0]+m[13]*mat.m[4]+m[14]*mat.m[8]+m[15]*mat.m[12];
		r[13]=m[12]*mat.m[1]+m[13]*mat.m[5]+m[14]*mat.m[9]+m[15]*mat.m[13];
		r[14]=m[12]*mat.m[2]+m[13]*mat.m[6]+m[14]*mat.m[10]+m[15]*mat.m[14];
		r[15]=m[12]*mat.m[3]+m[13]*mat.m[7]+m[14]*mat.m[11]+m[15]*mat.m[15];
		return mat4f(r);
	}
	mat4f operator *= (const mat4f &mat)
	{
		(*this)=(*this) * mat;
		return *this;
	}
	mat4f operator * (const float &s) const
	{
		mat4f r;
		for(int i=0;i<16;i++)
			r.m[i]=m[i]*s;
		return r;
	}
	mat4f& operator *= (const float &s)
	{
		for(int i=0;i<16;i++)
			m[i]*=s;
		return *this;
	}
	mat4f operator / (const float &s) const
	{
		mat4f r;
		float inverse=1.0f/s;
		for(int i=0;i<16;i++)
			r.m[i]=m[i]*inverse;
		return r;
	}
	mat4f& operator /= (const float &s)
	{
		float inverse=1.0f/s;
		for(int i=0;i<16;i++)
			m[i]*=inverse;
		return *this;
	}
	/*mat4f operator * (float f,const mat4f &m)
	{
		return m*f;
	}*///\todo
};
