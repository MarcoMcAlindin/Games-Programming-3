#pragma once
#include "Button.h"
#include "LevelViewCamera.h"
#include "ThirdPersonCamera.h"
#include "Input.h"
class CameraButton : public Button
{

public:

	CameraButton(std::shared_ptr<Texture> texture, glm::vec3 position, glm::vec3 color, float opacity, glm::vec2 scale) : Button(texture, position, color, opacity, scale) {};

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	virtual void OnClick() override;

protected:

	 virtual void SwitchCamera();

};


class CameraButton1 : public CameraButton
{
public :

	CameraButton1(std::shared_ptr<Texture> texture, glm::vec3 position, glm::vec3 color, float opacity, glm::vec2 scale) : CameraButton(texture, position, color, opacity, scale) {};

	virtual void OnUpdate(float deltaTime) override { CameraButton::OnUpdate(deltaTime); if (INPUT->GetKey(SDLK_2)) { SwitchCamera(); Fog::GetInstance()->SetMaxDist(10000.0f);
	} };
	virtual void OnRender() override { CameraButton::OnRender(); };

	virtual void SwitchCamera() override { SceneManager::GetInstance()->m_currentScene->SetCamera(SceneManager::GetInstance()->m_currentScene->m_sceneCameras["Camera_2"]->GetComponent<LevelViewCamera>()->m_camera);};
};

class CameraButton2 : public CameraButton
{
public:

	CameraButton2(std::shared_ptr<Texture> texture, glm::vec3 position, glm::vec3 color, float opacity, glm::vec2 scale) : CameraButton(texture, position, color, opacity, scale) {};

	virtual void OnUpdate(float deltaTime) override { CameraButton::OnUpdate(deltaTime); if (INPUT->GetKey(SDLK_1)) { SwitchCamera(); Fog::GetInstance()->SetMaxDist(10.0f); } };
	virtual void OnRender() override { CameraButton::OnRender(); };


	virtual void SwitchCamera() override { SceneManager::GetInstance()->m_currentScene->SetCamera(SceneManager::GetInstance()->m_currentScene->m_sceneCameras["Camera_Player"]->GetComponent<CameraComponent>()->m_camera); };
};

