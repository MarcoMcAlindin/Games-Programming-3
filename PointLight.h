#pragma once
#include "pch.h"
class PointLight
{
public:

	glm::vec3 Position() {}

	float Constant() { return m_constant; }
	float Linear() { return m_linear; }
	float Quadratic() { return m_quadratic; }

	glm::vec3 Ambient() { return m_ambient; }
	glm::vec3 Diffuse() { return m_diffuse; }
	glm::vec3 Specular() { return m_specular; }

	PointLight();
private:

	glm::vec3 m_position;

	glm::vec3 m_color;

	float m_constant;
	float m_linear;
	float m_quadratic;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

