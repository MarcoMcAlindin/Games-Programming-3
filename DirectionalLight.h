#pragma once
#include "pch.h"
class DirectionalLight
{
public:

	DirectionalLight();
	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	
	
	glm::vec3 Position() { return m_position; }
	glm::vec3 Direction() { return m_direction; }
	glm::vec3 Ambient() { return m_ambient; }
	glm::vec3 Diffuse() { return m_diffuse; }
	glm::vec3 Specular() { return m_specular; }
	glm::vec3 Color() { return m_color; }

	float AmbientStrength() { return m_ambientStrength; }
	float SpecularStrength() { return m_specularStrength; }

	void SetDirection(glm::vec3 direction) { m_direction = direction; }
	void SetAmbient(glm::vec3 ambient) { m_ambient = ambient; }
	void SetDiffuse(glm::vec3 diffuse) { m_diffuse = diffuse; }
	void SetSpecular(glm::vec3 specular) { m_specular = specular; }
	void SetPosition(glm::vec3 position) { m_position = position; }

	void SetAmbientStrength(float strength) { m_ambientStrength = strength; }
	void SetSpecularStrength(float strength) { m_specularStrength = strength; }


	static DirectionalLight* GetInstance();

private:

	static DirectionalLight* m_directionalLightInstance;

	

	glm::vec3 m_direction;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_color;
	glm::vec3 m_position;

	float m_ambientStrength;
	float m_specularStrength;


	
	

};

