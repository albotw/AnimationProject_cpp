#include "vec3.h"

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
//positif: pointent dans la même dir
//négatif: pointent en direction opposée
//0 : vecteurs perpendiculaires.
float dot(const vec3& l, const vec3& r)
{
	return l.x * r.x + l.y * r.y + l.z * r.z;
}

float lenSq(const vec3& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

/*taille tridimensionnelle (basé sur length²(A) = dot(A, A))*/
//on peut calculer la distance entre deux vecteurs comme ça: float distance = length(vec1 - vec2)
//vérif de taille plus opti: dot(A, A) < 5 * 5
float length(const vec3& v)
{
	float lsq = lenSq(v);
	if (lsq < VEC3_EPSILON)
	{
		return 0.0f;
	}
	return sqrtf(lsq);
}


/*Normalisation sur place*/
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

vec3 normalized(const vec3& v)
{
	float lsq = lenSq(v);
	if (lsq < VEC3_EPSILON) { return v; }
	float invLength = 1.0f / sqrtf(lsq);
	return vec3 (
		v.x * invLength,
		v.y * invLength,
		v.z * invLength
	);
}

float angle(const vec3& l, const vec3& r)
{
	float sqMagL = lenSq(l);
	float sqMagR = lenSq(r);

	if (sqMagL < VEC3_EPSILON || sqMagR < VEC3_EPSILON)
	{
		return 0.0f;
	}

	float dot = l.x * r.x + l.y * r.y + l.z * r.z;
	float len = sqrtf(sqMagL) * sqrtf(sqMagR);
	return acosf(dot / len);
}

vec3 project(const vec3& a, const vec3& b)
{
	float magBSq = length(b);
	if (magBSq < VEC3_EPSILON)
	{
		return vec3();
	}

	float scale = dot(a, b) / magBSq;
	return b * scale;
}

vec3 reject(const vec3& a, const vec3& b)
{
	vec3 projection = project(a, b);
	return a - projection;
}

vec3 reflect(const vec3& a, const vec3& b)
{
	float magBSq = length(b);
	if (magBSq < VEC3_EPSILON)
	{
		return vec3();
	}

	float scale = dot(a, b) / magBSq;
	vec3 proj2 = b * (scale * 2);
	return a - proj2;
}

vec3 cross(const vec3& l, const vec3& r)
{
	return vec3(
		l.y * r.z - l.z * r.y,
		l.z * r.x - l.x * r.z,
		l.x * r.y - l.y * r.x
	);
}

vec3 lerp(const vec3& s, const vec3& e, float t)
{
	return vec3(
		s.x + (e.x - s.x) * t,
		s.y + (e.y - s.y) * t,
		s.z + (e.z - s.z) * t
	);
}

vec3 slerp(const vec3& s, const vec3& e, float t)
{
	if (t < 0.01f)
	{
		return lerp(s, e, t);
	}

	vec3 from = normalized(s);
	vec3 to = normalized(e);

	float theta = angle(from, to);
	float sin_theta = sinf(theta);

	float a = sinf((1.0f - t) * theta) / sin_theta;
	float b = sinf(t * theta) / sin_theta;

	return from * a + to * b;
}

vec3 nlerp(const vec3& s, const vec3& e, float t)
{
	vec3 linear(
		s.x + (e.x - s.x) * t,
		s.y + (e.y - s.y) * t,
		s.z + (e.z - s.z) * t
	);
	return normalized(linear);
}

bool operator==(const vec3& l, const vec3& r)
{
	vec3 diff(l - r);
	return lenSq(diff) < VEC3_EPSILON;
}

bool operator!=(const vec3& l, const vec3& r)
{
	return !(l == r);
}