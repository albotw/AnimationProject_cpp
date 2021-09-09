#include "Texture.h"
Texture::Texture()
{
	width = 0;
	height = 0;
	channels = 0;
	glGenTextures(1, &handle);
}

Texture::Texture(const char* path)
{
	glGenTextures(1, &handle);
	Load(path);
}

Texture::~Texture()
{
	glDeleteTextures(1, &handle);
}

void Texture::Load(const char* path)
{
	glBindTexture(GL_TEXTURE_2D, handle);
	
	int w, h, c;
	unsigned char* data = stbi_load(path, &w, &h, &c, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	width = w;
	height = h;
	channels = c;
}

void Texture::Set(unsigned int uniformIndex, unsigned int textureIndex)
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, handle);
	glUniform1i(uniformIndex, textureIndex);
}

void Texture::Unset(unsigned int textureIndex)
{
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}

unsigned int Texture::GetHandle()
{
	return handle;
}