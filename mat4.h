#pragma once
#ifndef _H_MAT4_
#define _H_MAT4_
#define MAT4_EPSILON 0.0000001f
#include "vec4.h"
#include "vec3.h"
struct mat4
{
	union
	{
		float v[16];
		struct
		{
			vec4 right;
			vec4 up;
			vec4 forward;
			vec4 position;
		};
		struct
		{
			//		|row 1	  |row 2	|row 3    |row 4
			/*col 1*/float xx; float xy; float xz; float xw;
			/*col 2*/float yx; float yy; float yz; float yw;
			/*col 3*/float zx; float zy; float zz; float zw;
			/*col 4*/float wx; float wy; float wz; float ww;
		};
		struct
		{
			/*coumn - row notation*/
			float c0r0; float c0r1; float c0r2; float c0r3;
			float c1r0; float c1r1; float c1r2; float c1r3;
			float c2r0; float c2r1; float c2r2; float c2r3;
			float c3r0; float c3r1; float c3r2; float c3r3;
		};
		struct
		{
			/*row - column notation*/
			float r0c0; float r0c1; float r0c2; float r0c3;
			float r1c0; float r1c1; float r1c2; float r1c3;
			float r2c0; float r2c1; float r2c2; float r2c3;
			float r3c0; float r3c1; float r3c2; float r3c3;
		};
	};
	inline mat4() :
		xx(1), xy(0), xz(0), xw(0),
		yx(0), yy(1), yz(0), yw(0),
		zx(0), zy(0), zz(1), zw(0),
		wx(0), wy(0), wz(0), ww(1) { }

	inline mat4(float* fv) : 
		xx(fv[0]), xy(fv[1]), xz(fv[2]), xw(fv[3]),
		yx(fv[4]), yy(fv[5]), yz(fv[6]), yw(fv[7]),
		zx(fv[8]), zy(fv[9]), zz(fv[10]), zw(fv[11]),
		wx(fv[12]), wy(fv[13]), wz(fv[14]), ww(fv[15]) { }

	inline mat4(
		float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33) : 
		xx(_00), xy(_01), xz(_02), xw(_03),
		yx(_10), yy(_11), yz(_12), yw(_13),
		zx(_20), zy(_21), zz(_22), zw(_23),
		wx(_30), wy(_31), wz(_32), ww(_33) { }

};

bool operator==(const mat4& a, const mat4& b);
bool operator!=(const mat4& a, const mat4& b);
mat4 operator+ (const mat4& a, const mat4& b);

#endif