#include "Draw.h"

static GLenum DrawModeToGLEnum(DrawMode input)
{
	switch (input)
	{
	case DrawMode::Points: return GL_POINTS;
	case DrawMode::LineStrip: return GL_LINE_STRIP;
	case DrawMode::LineLoop: return GL_LINE_LOOP;
	case DrawMode::Lines: return GL_LINES;
	case DrawMode::Triangles: return GL_TRIANGLES;
	case DrawMode::TrianglesStrip: return GL_TRIANGLE_STRIP;
	case DrawMode::TriangleFan: return GL_TRIANGLE_FAN;
	}

	cout << "DrawModeToGLEnum, input invalide" << endl;
	return 0;
}

void Draw(unsigned int vertexCount, DrawMode mode)
{
	glDrawArrays(DrawModeToGLEnum(mode), 0, vertexCount);
}

void DrawInstanced(unsigned int vertexCount, DrawMode mode, unsigned int nInstances)
{
	glDrawArraysInstanced(DrawModeToGLEnum(mode), 0, vertexCount, nInstances);
}

void Draw(IndexBuffer& inIndexedBuffer, DrawMode mode)
{
	unsigned int handle = inIndexedBuffer.GetHandle();
	unsigned int nIndices = inIndexedBuffer.Count();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	glDrawElements(DrawModeToGLEnum(mode), nIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DrawInstanced(IndexBuffer& inIndexedBuffer, DrawMode mode, unsigned int nInstances)
{
	unsigned int handle = inIndexedBuffer.GetHandle();
	unsigned int count = inIndexedBuffer.Count();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	glDrawElementsInstanced(DrawModeToGLEnum(mode), count, GL_UNSIGNED_INT, 0, nInstances);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}