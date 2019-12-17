#pragma once

#include <glm/vec3.hpp>

class Light {
public:
	inline const glm::vec3& GetAmbient() const { return m_ambient; }
	inline const glm::vec3& GetDiffuse() const { return m_diffuse; }
	inline const glm::vec3& GetSpecular() const { return m_specular; }
	inline void setAmbient(const glm::vec3& ambient) { m_ambient = ambient; }
	inline void setDiffuse(const glm::vec3& diffuse) { m_diffuse = diffuse; }
	inline void setSpecular(const glm::vec3& specular) { m_specular = specular; }

protected:
	Light() = default;

protected:
	glm::vec3 m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::vec3 m_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
};

class DirectedLight :public Light {
public:
	DirectedLight(const glm::vec3& direction)
		:Light(),
		m_direction(direction)
	{

	}

	inline const glm::vec3& GetDirection() const { return m_direction; }
	inline void SetDirection(const glm::vec3& direction) { m_direction = direction; }

private:
	glm::vec3 m_direction;
};
