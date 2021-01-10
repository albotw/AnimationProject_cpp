#include "mat4.h"
#include <math.h>
bool operator==(const mat4& a, const mat4& b)
{
	for (int i = 0; i < 16; i++)
	{
		if (fabsf(a.v[i] - b.v[i]) > MAT4_EPSILON)
		{
			return false;
		}
	}
	return true;
}

bool operator!= (const mat4& a, const mat4& b)
{
	return !(a == b);
}

mat4 operator+(const mat4& a, const mat4& b)
{
	return mat4(
		a.xx + b.xx, a.xy + b.xy, a.xz + b.xz, a.xw + b.xw,
		a.yx + b.yx, a.yy + b.yy, a.yz + b.yz, a.yw + b.yw,
		a.zx + b.zx, a.xy + b.zy, a.zz + b.zz, a.zw + b.zw,
		a.wx + b.wx, a.wy + b.wy, a.wz + b.wz, a.ww + b.ww);
}

mat4 operator*(const mat4& m, float f)
{
	return mat4(
		m.xx * f, m.xy * f, m.xz * f, m.xw * f,
		m.yx * f, m.yy * f, m.yz * f, m.yw * f,
		m.zx * f, m.zy * f, m.zz * f, m.zw * f,
		m.wx * f, m.wy * f, m.wz * f, m.ww * f
	);
}

#define M4D(aRow, bCol) \
	a.v[ 0 * 4 + aRow] * b.v[bCol * 4 + 0] + \
	a.v[ 1 * 4 + aRow] * b.v[bCol * 4 + 1] + \
	a.v[ 2 * 4 + aRow] * b.v[bCol * 4 + 2] + \
	a.v[ 3 * 4 + aRow] * b.v[bCol * 4 + 3]

mat4 operator* (const mat4& a, const mat4& b)
{
	return mat4(
		M4D(0, 0), M4D(1, 0), M4D(2, 0), M4D(3, 0),
		M4D(0, 1), M4D(1, 1), M4D(2, 1), M4D(3, 1),
		M4D(0, 2), M4D(1, 2), M4D(2, 2), M4D(3, 2),
		M4D(0, 3), M4D(1, 3), M4D(2, 3), M4D(3, 3)
	);
}

#define M4V4D(mRow, x, y, z, w) \
	x * m.v[0 * 4 + mRow] + \
	y * m.v[1 * 4 + mRow] + \
	z * m.v[2 * 4 + mRow] + \
	w * m.v[3 * 4 + mRow]

vec4 operator* (const mat4& m, const vec4& v)
{
	return vec4(
		M4V4D(0, v.x, v.y, v.z, v.w),
		M4V4D(1, v.x, v.y, v.z, v.w),
		M4V4D(2, v.x, v.y, v.z, v.w),
		M4V4D(3, v.x, v.y, v.z, v.w)
	);
}

vec3 transformVector(const mat4& m, const vec3& v)
{
	return vec3(
		M4V4D(0, v.x, v.y, v.z, 0.0f),
		M4V4D(1, v.x, v.y, v.z, 0.0f),
		M4V4D(2, v.x, v.y, v.z, 0.0f)
	);
}

vec3 transformPoint(const mat4& m, const vec3& v)
{
	return vec3(
		M4V4D(0, v.x, v.y, v.z, 1.0f),
		M4V4D(1, v.x, v.y, v.z, 1.0f),
		M4V4D(2, v.x, v.y, v.z, 1.0f)
	);
}

vec3 transformPoint(const mat4& m, const vec3& v, float& w)
{
	float _w = w;
	w = M4V4D(3, v.x, v.y, v.z, _w);
	return vec3(
		M4V4D(0, v.x, v.y, v.z, _w),
		M4V4D(1, v.x, v.y, v.z, _w),
		M4V4D(2, v.x, v.y, v.z, _w)
	);
}