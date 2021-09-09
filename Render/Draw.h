#pragma once
#include "IndexBuffer.h"
#include "../GL/glad.h"
#include <iostream>

using namespace std;
enum class DrawMode {
	Points,
	LineStrip,
	LineLoop,
	Lines,
	Triangles,
	TrianglesStrip,
	TriangleFan
};

void Draw(IndexBuffer& inIndexedBuffer, DrawMode mode);
void Draw(unsigned int vertexCount, DrawMode mode);

void DrawInstanced(IndexBuffer& inIndexedBuffer, DrawMode mode);
void DrawInstanced(unsigned int vertexCount, DrawMode mode, unsigned int nInstances);