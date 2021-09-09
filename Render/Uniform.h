#pragma once
#include <vector>
#include "../Math/vec4.h"
#include "../Math/vec2.h"
#include "../Math/vec3.h"
#include "../Math/mat4.h"
#include "../Math/quat.h"
#include "../GL/glad.h"

using namespace std;

template<typename T>
class Uniform
{
private:
	Uniform();
	Uniform(const Uniform&);
	Uniform& operator=(const Uniform&);
	~Uniform();

public:
	static void Set(unsigned int slot, const T& value);
	static void Set(unsigned int slot, T* array, unsigned int length);
	static void Set(unsigned int slot, vector<T>& array);
};