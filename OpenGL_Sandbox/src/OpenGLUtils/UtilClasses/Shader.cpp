#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>



Shader::Shader(const std::string& shaderFilePath)
{
	ShaderProgramSource shaderSource = ParseShader(shaderFilePath);
	shaderID = CreateShader(shaderSource.vertexShader, shaderSource.fragmentShader);
}

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	std::string vertexSource = ParseShader(vertexFilePath, shaderType::VERTEX).vertexShader;
	std::string fragmentSource = ParseShader(fragmentFilePath, shaderType::FRAGMENT).fragmentShader;
	shaderID = CreateShader(vertexSource, fragmentSource);
}


Shader::~Shader()
{
	glDeleteProgram(shaderID);
}

void Shader::Bind() { glUseProgram(shaderID); }
void Shader::UnBind() { glUseProgram(0); }

void Shader::SetUniform1i(const std::string & name, int v0)
{
	glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform2i(const std::string & name, int v0, int v1)
{
	glUniform2i(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3i(const std::string & name, int v0, int v1, int v2)
{
	glUniform3i(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4i(const std::string & name, int v0, int v1, int v2, int v3)
{
	glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1f(const std::string & name, float v0)
{
	glUniform1f(GetUniformLocation(name), v0);
}

void Shader::SetUniform2f(const std::string & name, float v0, float v1)
{
	glUniform2f(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3f(const std::string & name, float v0, float v1, float v2)
{
	glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformVec3(const std::string& name, glm::vec3 vector) {
	glUniform3fv(GetUniformLocation(name), 1, &vector[0]);
}

void Shader::SetUniformMat4(const std::string& name, glm::mat4 matrix) {
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string & name)
{
	return glGetUniformLocation(shaderID, name.c_str());
}

ShaderProgramSource Shader::ParseShader(const std::string& shaderFilePath, shaderType initialType)
{
	std::ifstream shaderFile(shaderFilePath);
	std::stringstream ss[2];
	std::string line = "";

	if (!shaderFile.is_open()) {
		std::cout << "SHADER FILE: " << shaderFilePath << " FAILED TO OPEN\n";
	}

	shaderType type = initialType;

	while (std::getline(shaderFile, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = shaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = shaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}


	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	int programLinkSuccess;
	glGetShaderiv(program, GL_LINK_STATUS, &programLinkSuccess);
	if (!programLinkSuccess) {
		char infoLog[512];
		glGetShaderInfoLog(program, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR:: SHADDER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::CompileShader(int type, const std::string& shaderSource)
{
	unsigned int shader = glCreateShader(type);
	const char * cStr = shaderSource.c_str();
	glShaderSource(shader, 1, &cStr, NULL);
	glCompileShader(shader);

	//check for shader successful compilation
	int shaderCompilationSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompilationSuccess);
	if (!shaderCompilationSuccess) {
		char infoLog[512];
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR:: SHADDER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}
