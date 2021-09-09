#include "Shader.h"


Shader::Shader()
{
	handle = glCreateProgram();
}

Shader::Shader(const string& vertex, const string& fragment)
{
	handle = glCreateProgram();
	Load(vertex, fragment);
}

Shader::~Shader()
{
	glDeleteProgram(handle);
}

string Shader::ReadFile(const string& path)
{
	ifstream file;
	file.open(path);
	stringstream contents;
	contents << file.rdbuf();
	file.close();
	return contents.str();
}

unsigned int Shader::CompileVertexShader(const string& vertex)
{
	unsigned int v = glCreateShader(GL_VERTEX_SHADER);
	const char* v_source = vertex.c_str();
	glShaderSource(v, 1, &v_source, NULL);
	glCompileShader(v);

	int success = 0;
	glGetShaderiv(v, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(v, 512, NULL, infoLog);
		cout << "Erreur de compilation d'un vertex shader: " << endl;
		cout << "\t" << infoLog << endl;
		glDeleteShader(v);
		return 0;
	}

	return v;
}

unsigned int Shader::CompileFragmentShader(const string& fragment)
{
	unsigned int f = glCreateShader(GL_FRAGMENT_SHADER);
	const char* f_source = fragment.c_str();
	glShaderSource(f, 1, &f_source, NULL);
	glCompileShader(f);

	int success = 0;
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(f, 512, NULL, infoLog);
		cout << "Erreur de compilation d'un fragment shader: " << endl;
		cout << "\t" << infoLog << endl;
		glDeleteShader(f);
		return 0;
	}

	return f;
}

bool Shader::LinkShaders(unsigned int vertex, unsigned int fragment)
{
	glAttachShader(handle, vertex);
	glAttachShader(handle, fragment);
	glLinkProgram(handle);

	int success = 0;
	glGetProgramiv(handle, GL_LINK_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(handle, 512, NULL, infoLog);
		cout << "Erreur pendant la liaison des shaders:" << endl;
		cout << "\t" << infoLog << endl;
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return false;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return true;
}

void Shader::PopulateAttributes()
{
	int count = -1;
	int length;
	char name[128];
	int size;
	GLenum type;

	glUseProgram(handle);
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &count);

	for (int i = 0; i < count; ++i)
	{
		memset(name, 0, sizeof(char) * 128);
		glGetActiveAttrib(handle, (GLuint)i, 128, &length, &size, &type, name);
		int attrib = glGetAttribLocation(handle, name);

		if (attrib >= 0)
		{
			attributes[name] = attrib;
		}
	}

	glUseProgram(0);
}

void  Shader::PopulateUniforms()
{
	int count = -1;
	int length;
	char name[128];
	char testName[256];
	int size;
	GLenum type;

	glUseProgram(handle);
	glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &count);

	for (int i = 0; i < count; ++i)
	{
		memset(name, 0, sizeof(char) * 128);
		glGetActiveUniform(handle, (GLuint)i, 128, &length, &size, &type, name);
		int uniform = glGetUniformLocation(handle, name);
		if (uniform >= 0)
		{
			string uniformName = name;
			size_t found = uniformName.find('[');

			/*
			On doit déterminer si l'uniform est un array ou pas
			*/
			if (found != string::npos)
			{
				uniformName.erase(uniformName.begin() + found, uniformName.end());
				unsigned int uniformIndex = 0;
				while (true)
				{
					memset(testName, 0, sizeof(char) * 256);
					sprintf(testName, "%s[%d]", uniformName.c_str(), uniformIndex++);
					int uniformLocation = glGetUniformLocation(handle, testName);
					if (uniformLocation < 0)
					{
						break;
					}

					uniforms[testName] = uniformLocation;
				}
			}
		}
	}

	glUseProgram(0);
}

void Shader::Load(const string& vertex, const string& fragment)
{
	ifstream f(vertex.c_str());
	bool vertFile = f.good();
	f.close();

	f = ifstream(fragment.c_str());
	bool fragFile = f.good();
	f.close();

	string v_source = vertex;
	if (vertFile)
	{
		v_source = ReadFile(vertex);
	}

	string f_source = fragment;
	if (fragFile)
	{
		f_source = ReadFile(fragment);
	}

	unsigned int vert = CompileVertexShader(v_source);
	unsigned int frag = CompileFragmentShader(f_source);

	if (LinkShaders(vert, frag))
	{
		PopulateAttributes();
		PopulateUniforms();
	}
}

void Shader::Bind()
{
	glUseProgram(handle);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

unsigned int Shader::GetHandle()
{
	return handle;
}

unsigned int Shader::GetAttribute(const string& name)
{
	map<string, unsigned int>::iterator it = attributes.find(name);

	if (it == attributes.end())
	{
		cout << "Attribut invalide: " << name << endl;
		return 0;
	}

	return it->second;
}

unsigned int Shader::GetUniform(const string& name)
{
	map<string, unsigned int>::iterator it = uniforms.find(name);

	if (it == uniforms.end())
	{
		cout << "Uniforme invalide: " << name << endl;
		return 0;
	}

	return it->second;
}