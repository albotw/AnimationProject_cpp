#include "Attribute.h"
#include "Math/vec2.h"
#include "Math/vec3.h"
#include "Math/vec4.h"

template Attribute<int>;
template Attribute<float>;
template Attribute<vec2>;
template Attribute<vec3>;
template Attribute<vec4>;
template Attribute<ivec4>;

template<typename T>
Attribute<T>::Attribute()
{
	glGenBuffers(1, &handle);
	count = 0;
}

