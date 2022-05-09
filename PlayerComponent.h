#pragma once
#include "Component.h"
#include "pch.h"

enum PlayerState {
	IDLE_PLAYER,
	WALKING,
	DYING
};

class PlayerComponent : public Component
{
private:
	
	float m_deltaTime;
	bool m_animation;
	float m_playerSpeed;
	bool m_moving;

public:

	PlayerComponent();

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void SetPlayerSpeed(float speed) { m_playerSpeed = speed; }

	bool Move();
	void MoveDebug();

	void MoveForward();
	void MoveBack();
	void MoveLeft();
	void MoveRight();

	float Distance(glm::vec3 a, glm::vec3 b);

	
};

