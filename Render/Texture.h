#pragma once
#include "../GL/glad.h"
#include "../lib/stb_image.h"

class Texture
{
protected:
	unsigned int width;
	unsigned int height;
	unsigned int channels;
	unsigned int handle;

private: 
	Texture(const Texture& other);
	Texture& operator= (const Texture& other);

public:
	Texture();
	Texture(const char* path);
	~Texture();

	void Load(const char* path);
	void Set(unsigned int uniform, unsigned int texIndex);
	void Unset(unsigned int texIndex);
	unsigned int GetHandle();
};

