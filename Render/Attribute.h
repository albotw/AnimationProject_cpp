#pragma once
#include <vector>
#include "../Math/vec2.h"
#include "../Math/vec3.h"
#include "../Math/vec4.h"
#include "../GL/glad.h"

using namespace std;

template<typename T>

class Attribute {

protected: 
	unsigned int handle;
	unsigned int count;

private:
	Attribute(const Attribute& other);
	Attribute& operator= (const Attribute& other);

	void SetAttribPointer(unsigned int slot);

public:
	Attribute();
	~Attribute();

	void Set(T* inputArray, unsigned int arrayLength);
	void Set(vector<T>& input);

	void BindTo(unsigned int slot);
	void UnbindFrom(unsigned int slot);

	unsigned int Count();
	unsigned int GetHandle();
};