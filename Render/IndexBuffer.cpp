#include "IndexBuffer.h"


IndexBuffer::IndexBuffer() {
	glGenBuffers(1, &handle);
	count = 0;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &handle);
}

unsigned int IndexBuffer::Count()
{
	return count;
}

unsigned int IndexBuffer::GetHandle()
{
	return handle;
}

void IndexBuffer::Set(unsigned int* input, unsigned int length)
{
	count = length;
	unsigned int size = sizeof(unsigned int);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * count, input, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Set(vector<unsigned int>& input)
{
	Set(&input[0], (unsigned int)input.size());
}