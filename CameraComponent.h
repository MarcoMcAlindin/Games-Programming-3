#pragma once
#include "Component.h"
#include "Camera.h"
#include "Transform.h"


class CameraComponent : public Component
{
private:
	glm::vec3 m_cameraOffset;
	
public:
	//public variables
	Camera* m_camera;

	Transform* m_Target = nullptr;

public:

	//public functions
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	virtual void Start();

	virtual void Start(Transform* target);

	void InitialiseTargetSystem(Transform* target);

	void RecalculateOffset();
	
};




