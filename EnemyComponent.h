#pragma once
#include "Component.h"
#include "pch.h"

enum EnemyState
{
	IDLE,
	MOVING,
	ATTACK
};

class EnemyComponent : public Component
{
private:

	float m_deltaTime;
	bool m_animation;
	float m_EnemySpeed;
	bool m_moving;

	EnemyState m_currentState = EnemyState::IDLE;

	std::vector<glm::vec3> m_movePositions;
	glm::vec3 m_currentDestination;

	float m_currentTime;
	float m_waitTime;
public:

	EnemyComponent();

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void SetEnemySpeed(float speed) { m_EnemySpeed = speed; }

	bool Move();
	void MoveDebug();

	void MoveForward();
	void MoveBack();
	void MoveLeft();
	void MoveRight();

	float Distance(glm::vec3 a, glm::vec3 b);

	void SetMovementPosition(glm::vec3 pos) { m_movePositions.push_back(pos); };

};

