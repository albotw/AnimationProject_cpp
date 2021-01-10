#pragma once
#include <math.h>
#ifndef _H_VEC3_
#define _H_VEC3_

#define VEC3_EPSILON 0.0000001f

struct vec3
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float v[3];
	};
	inline vec3() : x(0.0f), y(0.0f), z(0.0f) { }
	inline vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
	inline vec3(float* fv) : x(fv[0]), y(fv[1]), z(fv[2]) { }
};

vec3 operator+ (const vec3& l, const vec3& r)
{
	return vec3(l.x + r.x, l.y + r.y, l.z + r.z);
}

vec3 operator- (const vec3& l, const vec3& r)
{
	return vec3(l.x - r.x, l.y - r.y, l.z - r.z);
}

vec3 operator* (const vec3& v, float f)
{
	return vec3(v.x * f, v.y * f, v.z * f);
}

vec3 operator* (const vec3& l, const vec3& r)
{
	return vec3(l.x * r.x, l.y * r.y, l.z * r.z);
}

/*produit scalaire*/
float dot(const vec3& l, const vec3& r)
{
	return l.x * r.x + l.y * r.y + l.z * r.z;
}

float lenSq(const vec3& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

/*taille tridimensionnelle*/
//we can calculate the distance between two vectors by taking the length of the difference between them
//float distane = length(vec1 - vec2)
float length(const vec3& v)
{
	float lsq = lenSq(v);
	if (lsq < VEC3_EPSILON)
	{
		return 0.0f;
	}
	return sqrtf(lsq);
}

void normalize(vec3& v)
{
	float lsq = lenSq(v);
	if (lsq < VEC3_EPSILON)
	{
		return;
	}
	float invLength = 1.0f / sqrtf(lsq);
	v.x *= invLength;
	v.y *= invLength;
	v.z *= invLength;
}

vec3 normalized(const vec3& v);

float angle(const vec3& l, const vec3& r);

vec3 project(const vec3& a, const vec3& b);

vec3 reject(const vec3& a, const vec3& b);

vec3 reflect(const vec3& a, const vec3& b);

vec3 cross(const vec3& l, const vec3& r);

/*interpolation linéaire*/
vec3 lerp(const vec3& s, const vec3& e, float t);

/*interpolation linéraire sphérique*/
vec3 slerp(const vec3& s, const vec3& e, float t);

/*approximate version of slerp, not constant in velocity*/
vec3 nlerp(const vec3& s, const vec3& e, float t);

bool operator==(const vec3& l, const vec3& r);

bool operator!=(const vec3& l, const vec3& r);

#endif