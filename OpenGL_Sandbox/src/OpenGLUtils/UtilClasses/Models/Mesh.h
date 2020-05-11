#pragma once
#include <string>
#include <vector>
#include "OpenGLUtils/Includes/OpenGLIncludeHeaders.h"
#include "OpenGLUtils/UtilClasses/Shader/Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	//Texture Coordinate
	glm::vec2 TexCoord;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<Texture> Textures;

	void Draw(Shader shader, const std::string& uniformName = "");

private:

	unsigned int VAO, VBO, EBO;

	void SetupMesh();

};