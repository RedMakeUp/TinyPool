#pragma once

#include <memory>
#include "Mesh.h"
#include "Shader.h"

class Terrain {
public:
	Terrain(int gridX, int gridZ);

	void Render(Shader* shader);

private:
	std::unique_ptr<Mesh> GenerateMesh();

private:
	std::unique_ptr<Mesh> m_mesh;
	glm::mat4 m_modelToWorld;
};
