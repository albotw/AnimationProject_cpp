#pragma once
#include <vector>
#include "../GL/glad.h"
using namespace std;

class IndexBuffer {
public: 
	unsigned int handle;
	unsigned int count;

private:
	IndexBuffer(const IndexBuffer& other);
	IndexBuffer& operator= (const IndexBuffer& other);

public:
	IndexBuffer();
	~IndexBuffer();

	void Set(unsigned int* rr, unsigned int length);
	void Set(vector<unsigned int>& input);

	unsigned int Count();
	unsigned int GetHandle();
};