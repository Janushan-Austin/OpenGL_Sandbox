#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const std::string& path, const std::string &directory, bool gamma = false);

class Model
{
public:
	Model(char *path)
	{
		loadModel(path);
	}
	void Draw(Shader shader, const std::string& uniformName = "");
private:
	// model data
	std::vector<Texture> TexturesLoaded;
	std::vector<Mesh> Meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string typeName);
};

