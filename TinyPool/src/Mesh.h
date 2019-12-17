#pragma once

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Shader.h"


struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	/*glm::vec3 Tangent;
	glm::vec3 Bitangent;*/
};

struct Texture {
	unsigned int Id;
	std::string Type;
	std::string Path;
};

class Mesh {
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	Mesh() = default;
	~Mesh();

	void Render(Shader* shader,const glm::mat4& modelToWorld);

	void loadToGPU();

private:
	friend class Model;
	friend class Terrain;

	GLuint m_vao = 0, m_vbo = 0, m_ebo = 0;

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;

	glm::mat4 m_localToModel = glm::mat4(1.0f);
};
