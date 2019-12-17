#include "Terrain.h"

constexpr unsigned int TERRAIN_VERTEX_COUNT = 201;
constexpr float TERRAIN_SIZE = 50.0f;
constexpr float TERRAIN_MAX_HEIGHT = 60.0f;
constexpr float TERRAIN_GRID_SQUARE_SIZE = TERRAIN_SIZE / static_cast<float>(TERRAIN_VERTEX_COUNT - 1);


Terrain::Terrain(int gridX, int gridZ)
{
	m_mesh = GenerateMesh();
	m_mesh->loadToGPU();

	m_modelToWorld = glm::translate(glm::mat4(1.0f),glm::vec3(gridX * TERRAIN_GRID_SQUARE_SIZE, 0.0f, gridZ * TERRAIN_GRID_SQUARE_SIZE));
}

void Terrain::Render(Shader* shader)
{
	m_mesh->Render(shader, m_modelToWorld);
}

std::unique_ptr<Mesh> Terrain::GenerateMesh()
{
	auto mesh = std::make_unique<Mesh>();

	mesh->m_vertices.resize(TERRAIN_VERTEX_COUNT * TERRAIN_VERTEX_COUNT);
	mesh->m_indices.resize(6 * (TERRAIN_VERTEX_COUNT - 1) * (TERRAIN_VERTEX_COUNT - 1));

	Vertex vertex;
	glm::vec3 vector3;
	glm::vec2 vector2;
	unsigned int index = 0;

	// Vertex data
	for (unsigned int i = 0; i < TERRAIN_VERTEX_COUNT; i++) {
		for (unsigned int j = 0; j < TERRAIN_VERTEX_COUNT; j++) {
			// Position
			vector3.x = (float)j / ((float)TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE;
			vector3.y = 0.0f;
			vector3.z = (float)i / ((float)TERRAIN_VERTEX_COUNT - 1) * TERRAIN_SIZE;
			vertex.Position = vector3;
			// Normal
			vertex.Normal = glm::vec3(0.0f,1.0f,0.0f);
			// Texture coordinate
			vector2.x = (float)j / ((float)TERRAIN_VERTEX_COUNT - 1);
			vector2.y = (float)i / ((float)TERRAIN_VERTEX_COUNT - 1);
			vertex.TexCoords = vector2;

			mesh->m_vertices[index++] = vertex;
		}
	}

	// Vertex index
	index = 0;
	for (unsigned int gz = 0; gz < TERRAIN_VERTEX_COUNT - 1; gz++) {
		for (unsigned int gx = 0; gx < TERRAIN_VERTEX_COUNT - 1; gx++) {
			unsigned int topLeft = (gz * TERRAIN_VERTEX_COUNT) + gx;
			unsigned int topRight = topLeft + 1;
			unsigned int bottomLeft = ((gz + 1) * TERRAIN_VERTEX_COUNT) + gx;
			unsigned int bottomRight = bottomLeft + 1;

			mesh->m_indices[index++] = topLeft;
			mesh->m_indices[index++] = bottomLeft;
			mesh->m_indices[index++] = topRight;
			mesh->m_indices[index++] = topRight;
			mesh->m_indices[index++] = bottomLeft;
			mesh->m_indices[index++] = bottomRight;
		}
	}

	return mesh;
}
