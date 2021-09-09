#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "../GL/glad.h"
using namespace std;


class Shader
{
private:
	unsigned int handle;

	map<string, unsigned int> attributes;
	map<string, unsigned int> uniforms;

	Shader(const Shader&);
	Shader& operator= (const Shader&);

	string ReadFile(const string& path);
	unsigned int CompileVertexShader(const string& vertex);
	unsigned int CompileFragmentShader(const string& fragment);
	bool LinkShaders(unsigned int vertex, unsigned int fragment);

	void PopulateAttributes();
	void PopulateUniforms();

public:
	Shader();
	Shader(const string& vertex, const string& fragment);
	~Shader();

	void Load(const string& vertex, const string& fragment);

	void Bind();
	void Unbind();

	unsigned int GetAttribute(const string& name);
	unsigned int GetUniform(const string& name);
	unsigned int GetHandle();
};