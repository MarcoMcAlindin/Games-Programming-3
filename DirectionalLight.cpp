#include "DirectionalLight.h"
#include "Application.h"

DirectionalLight* DirectionalLight::m_directionalLightInstance = NULL;

DirectionalLight::DirectionalLight()
{
	m_position = glm::vec3(0.2f,10.0f,2.0f);
	m_color = glm::vec3(1.0f, 1.0f, 1.0f);
	m_direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	m_ambient = glm::vec3(0.5f, 0.5f, 0.5f);
	m_diffuse = glm::vec3(0.05f, 0.05f, 0.05f);
	m_specular = glm::vec3(0.2f, 0.2f, 0.2f);

	m_ambientStrength = .0f;
	m_specularStrength = .3f;

	//Add Directional Light values to tweakBar
	/*TwAddVarRW(Application::GetInstance()->m_tweakBar, "CameraPosition.x", TW_TYPE_FLOAT, &m_position.x, " label='Camera X' keyIncr=1 keyDecr=CTRL+1 min=-10 max=10 step=0.01 ");
	TwAddVarRW(Application::GetInstance()->m_tweakBar, "CameraPosition.x", TW_TYPE_FLOAT, &m_position.y, " label='Camera X' keyIncr=1 keyDecr=CTRL+1 min=-10 max=10 step=0.01 ");
	TwAddVarRW(Application::GetInstance()->m_tweakBar, "CameraPosition.x", TW_TYPE_FLOAT, &cameraX, " label='Camera X' keyIncr=1 keyDecr=CTRL+1 min=-10 max=10 step=0.01 ");
	TwAddVarRW(Application::GetInstance()->m_tweakBar, "CameraPosition.x", TW_TYPE_FLOAT, &cameraX, " label='Camera X' keyIncr=1 keyDecr=CTRL+1 min=-10 max=10 step=0.01 ");
	TwAddVarRW(Application::GetInstance()->m_tweakBar, "CameraPosition.x", TW_TYPE_FLOAT, &cameraX, " label='Camera X' keyIncr=1 keyDecr=CTRL+1 min=-10 max=10 step=0.01 ");
	TwAddVarRW(Application::GetInstance()->m_tweakBar, "CameraPosition.x", TW_TYPE_FLOAT, &cameraX, " label='Camera X' keyIncr=1 keyDecr=CTRL+1 min=-10 max=10 step=0.01 ");*/
}

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {

	m_direction = direction;
	m_specular = specular;
	m_diffuse = diffuse;
	m_ambient = ambient;

}

DirectionalLight* DirectionalLight::GetInstance() 
{
		if (m_directionalLightInstance == NULL)
		{
			m_directionalLightInstance = new DirectionalLight();
		}
		return DirectionalLight::m_directionalLightInstance;

	
}



