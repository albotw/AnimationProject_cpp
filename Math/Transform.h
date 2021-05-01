#pragma once
#include "vec3.h"
#include "quat.h"

struct Transform
{
	vec3 position;
	quat rotation;
	vec3 scale;

	Transform(const vec3& p, const quat& r, const vec3& s) : position(p), rotation(r), scale(s) { }
	Transform() : position(vec3(0, 0, 0)), rotation(quat(0, 0, 0, 1)), scale(vec3(1, 1, 1)) { }
};

