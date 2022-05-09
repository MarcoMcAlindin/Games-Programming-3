#pragma once
#include "CameraComponent.h"
class ThirdPersonCamera : public CameraComponent
{
private:

	//Private variables
	float m_cameraSpeed = 0.15f;
	float m_deltaTime;

public:
	

	void SetPlayerFollow() { m_playerFollow = true; }
	//public functions
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	//Movement Methods
	void MoveForward();
	void MoveBack();
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void Move(Entity* player);

	void RotateAround(Entity* player);
	void FollowPlayer();
	virtual void Start() override;

	void SetOffset(glm::vec3 offset) { m_offset = offset; }
	void SetPlayerPosition(glm::vec3 playerPos) { m_playerPos = playerPos; }

	glm::vec3 m_offset;
	glm::vec3 m_playerPos;
	bool m_playerFollow = true;

};

