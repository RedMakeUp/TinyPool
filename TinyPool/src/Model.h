#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <map>
#include <vector>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
	Model(const std::string& path);

	void Render(Shader* shader);

	inline void loadToGPU() { for (auto& mesh : m_meshes) mesh->loadToGPU(); }
	inline void SetModelToWorld(const glm::mat4& modelToWorld) { m_modelToWorld = modelToWorld; }

private:
	void LoadModelFromFile(const std::string& path);

	// Processes a node in a recursive fashion.
	void ProcessNode(aiNode* node, const aiScene* scene);

	std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);

	// Checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

private:
	std::vector<Texture> m_textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<std::unique_ptr<Mesh>> m_meshes;
	std::string m_directory;

	glm::mat4 m_modelToWorld = glm::mat4(1.0f);
};
