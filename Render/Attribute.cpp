#include "Attribute.h"


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

template<typename T>
Attribute<T>::~Attribute()
{
	glDeleteBuffer(1, &handle);
}

template<typename T>
unsigned int Attribute<T>::Count()
{
	return count;
}

template<typename T>
unsigned int Attribute<T>::GetHandle()
{
	return handle;
}

template<typename T>
void Attribute<T>::Set(T* input, unsigned int length)
{
	count = length;
	unsigned int size = sizeof(T);

	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, size * count, input, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void Attribute<T>::Set(vector<T>& input)
{
	Set(&input[0], (unsigned int)input.size());
}

//Typage obligatoires pour la fonction, impossible d'utiliser une template.
template<>
void Attribute<int>::SetAttribPointer(unsigned int s)
{
	glVertexAttribIPointer(s, 1, GL_INT, 0, (void*)0);
}

template<>
void Attribute<ivec4>::SetAttribPointer(unsigned int s)
{
	glVertexAttribIPointer(s, 4, GL_INT, 0, (void*)0);
}

template<>
void Attribute<float>::SetAttribPointer(unsigned int s)
{
	glVertexAttribPointer(s, 1, GL_FLOAT, GL_FALSE, 0, 0);
}

template<>
void Attribute<vec2>::SetAttribPointer(unsigned int s)
{
	glVertexAttribPointer(s, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

template<>
void Attribute<vec3>::SetAttribPointer(unsigned int s)
{
	glVertexAttribPointer(s, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

template<>
void Attribute<vec4>::SetAttribPointer(unsigned int s)
{
	glVertexAttribPointer(s, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

template<typename T>
void Attribute<T>::BindTo(unsigned int slot)
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glEnableVertexAttribArray(slot);
	SetAttribPointer(slot);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void Attribute<T>::UnbindFrom(unsigned int slot)
{
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glDisableVertexAttribArray(slot);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}