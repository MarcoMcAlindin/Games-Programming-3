#include "EnemyComponent.h"
#include "Entity.h"
#include "Input.h"
#include "Application.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "Animator.h"
#include "Animation.h"



EnemyComponent::EnemyComponent()
{
	
	m_EnemySpeed = 0.2f;
}
void EnemyComponent::OnRender() {

}

void EnemyComponent::OnUpdate(float deltaTime)
{
	m_deltaTime = deltaTime;
	switch (m_currentState)
	{
	case EnemyState::IDLE:
		m_currentTime = deltaTime;

		break;
	case EnemyState::MOVING:
		if (Move()) {

		}
		break;
	case EnemyState::ATTACK:

		break;
	}

	if (Distance(m_entity->GetTransform()->GetPosition(), SceneManager::GetInstance()->m_currentScene->GetEntity("Player")->GetTransform()->GetPosition()) <  2.0f)
	{
		m_entity->GetTransform()->SetRotation(glm::quatLookAt(m_entity->GetTransform()->GetRight(), m_entity->GetTransform()->GetUp()));

		Move();
	}

}




bool EnemyComponent::Move()
{

	m_entity->GetTransform()->AddPosition(m_EnemySpeed * m_deltaTime * m_entity->GetTransform()->GetForward());
	m_entity->GetComponent<Animator>()->SetCurrentAnimation(m_entity->GetComponent<Animator>()->GetAnimation("Walk"));
	return false;
}



float EnemyComponent::Distance(glm::vec3 a, glm::vec3 b)
{
	float dist;
	dist = std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	return dist;
}
