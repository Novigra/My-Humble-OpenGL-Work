#pragma once

#include "Mesh.h"
#include <vector>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:

	Model(const char* path, bool gamma = false);

	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> LoadedTexture;
	bool gammaCorrection;

	void Draw(Shader& shader);

private:
	
	void LoadModel(std::string path);

	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
};