#include "PointLight.h"
PointLight::PointLight()
{
	m_color = glm::vec3(0.1f,0.8f,0.2f);

	m_ambient = glm::vec3(m_color.x, m_color.y, m_color.z);
	m_diffuse = glm::vec3(m_color.x, m_color.y, m_color.z);
	m_specular = glm::vec3(m_color.x, m_color.y, m_color.z);

	m_constant = 1.0f;
	m_linear = 0.4f;
	m_quadratic = 0.7f;
}