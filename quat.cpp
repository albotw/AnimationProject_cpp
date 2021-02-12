#include "quat.h"
#include <cmath>

quat angleAxis(float angle, const vec3& axis)
{
	vec3 norm = normalized(axis);
	float s = sinf(angle * 0.5f);

	return quat(norm.x * s,
				norm.y * s,
				norm.z * s,
				cosf(angle * 0.5f)
	);
}

quat fromTo(const vec3& from, const vec3& to) 
{
	vec3 f = normalized(from);
	vec3 t = normalized(to);

	if (f == t) 
	{
		return quat();
	}
	else if (f == t * -1.0f)
	{
		vec3 ortho = vec3(1, 0, 0);
		if (fabsf(f.y) < fabsf(f.x))
		{
			ortho = vec3(0, 1, 0);
		}
		if (fabsf(f.z) < fabsf(f.y) && fabs(f.z) < fabsf(f.x))
		{
			ortho = vec3(0, 0, 1);
		}

		vec3 axis = normalized(cross(f, ortho));
		return quat(axis.x, axis.y, axis.z, 0);
	}

	vec3 half = normalized(f + t);
	vec3 axis = cross(f, half);
	return quat(axis.x, axis.y, axis.z, dot(f, half));
}

vec3 getAxis(const quat& quat)
{
	return normalized(vec3(quat.x, quat.y, quat.z));
}

float getAngle(const quat& quat)
{
	return 2.0f * acosf(quat.w);
}

quat operator+ (const quat& a, const quat& b)
{
	return quat(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

quat operator- (const quat& a, const quat& b)
{
	return quat(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}