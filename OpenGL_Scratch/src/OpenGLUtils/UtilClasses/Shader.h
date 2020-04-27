#pragma once
#include <string>
#include "OpenGLUtils/Includes/OpenGLIncludeHeaders.h"

struct ShaderProgramSource {
	std::string vertexShader;
	std::string fragmentShader;
};

enum class shaderType {
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};

class Shader
{
public:
	Shader(const std::string& shaderFilePath);
	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	~Shader();

	void Bind();
	void UnBind();

	void SetUniform1i(const std::string& name, int v0);
	void SetUniform2i(const std::string& name, int v0, int v1);
	void SetUniform3i(const std::string& name, int v0, int v1, int v2);
	void SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3);

	void SetUniform1f(const std::string& name, float v0);
	void SetUniform2f(const std::string& name, float v0, float v1);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniformMat4(const std::string& name, glm::mat4 matrix);

	int GetUniformLocation(const std::string& name);

private:
	unsigned int shaderID;

	ShaderProgramSource ParseShader(const std::string& shaderFilePath, shaderType initialType = shaderType::NONE);

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(int type, const std::string& shader);
};

