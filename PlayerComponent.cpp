#include "PlayerComponent.h"
#include "Entity.h"
#include "Input.h"
#include "Application.h"
#include "Camera.h"
#include "CameraComponent.h"
#include "Animator.h"
#include "Animation.h"
#include <random>



PlayerComponent::PlayerComponent()
{
	
}
void PlayerComponent::OnRender() {

}

void PlayerComponent::OnUpdate(float deltaTime)
{

	if (SceneManager::GetInstance()->m_currentScene->m_playerScore == 4)
	{
		Application::GetInstance()->m_appState = AppState::QUITTING;
	}
	m_deltaTime = deltaTime;
	switch (Application::GetInstance()->m_currentGameState)
	{
	case GAME:
		/*if (Move()) {
			m_entity->GetComponent<Animator>()->SetCurrentAnimation(m_entity->GetComponent<Animator>()->GetAnimation("Walk"));
			


		}
		else
		{
			m_entity->GetComponent<Animator>()->SetCurrentAnimation(m_entity->GetComponent<Animator>()->GetAnimation("Idle"));
			

		}*/
		
		break;

	case DEBUG:

		
		break;

	}

	if (Distance(m_entity->GetTransform()->GetPosition(), SceneManager::GetInstance()->m_currentScene->m_orbSphere->GetTransform()->GetPosition()) < 3)

	{

		if (INPUT->GetKey(SDLK_c))
		{
			SceneManager::GetInstance()->m_currentScene->m_orbSphere->GetTransform()->SetPosition(SceneManager::GetInstance()->m_currentScene->m_orbPositions[SceneManager::GetInstance()->m_currentScene->m_playerScore]);
			SceneManager::GetInstance()->m_currentScene->m_playerScore += 1;

			SceneManager::GetInstance()->m_currentScene->GetUIEntity("Press_C")->isActive = false;

		}
		else
		{
			SceneManager::GetInstance()->m_currentScene->GetUIEntity("Press_C")->isActive = true;

		}
	}

	if (Distance(m_entity->GetTransform()->GetPosition(), SceneManager::GetInstance()->m_currentScene->m_orbSphere->GetTransform()->GetPosition()) < 8)

	{
		SoundMgr::getInstance()->getSnd("sphere")->play(-1);
	}
	else
	{
		SoundMgr::getInstance()->getSnd("sphere")->Stop();
	}

}

void PlayerComponent::MoveForward()
{
	m_entity->GetTransform()->AddPosition(m_playerSpeed * m_deltaTime * m_entity->GetTransform()->GetForward());
	m_entity->GetTransform()->SetRotation(glm::quatLookAt(-m_entity->GetTransform()->GetForward(), m_entity->GetTransform()->GetUp()));


}

void PlayerComponent::MoveBack()
{
	m_entity->GetTransform()->AddPosition(-m_playerSpeed * m_deltaTime * m_entity->GetTransform()->GetForward());
	m_entity->GetTransform()->SetRotation(glm::quatLookAt(m_entity->GetTransform()->GetForward(), m_entity->GetTransform()->GetUp()));

}

void PlayerComponent::MoveRight()
{
	m_entity->GetTransform()->AddPosition(m_playerSpeed * m_deltaTime * m_entity->GetTransform()->GetRight());
	m_entity->GetTransform()->SetRotation(glm::quatLookAt(-m_entity->GetTransform()->GetRight(), m_entity->GetTransform()->GetUp()));

}

void PlayerComponent::MoveLeft()
{
	m_entity->GetTransform()->AddPosition(-m_playerSpeed * m_deltaTime * m_entity->GetTransform()->GetRight());
	m_entity->GetTransform()->SetRotation(glm::quatLookAt(m_entity->GetTransform()->GetRight(), m_entity->GetTransform()->GetUp()));

}


bool PlayerComponent::Move()
{

	if (INPUT->GetKey(SDLK_UP)) 
	{
		MoveForward();
		return true;
	}
	

	if (INPUT->GetKey(SDLK_DOWN))
	{
		MoveBack();
		return true;

	}
	


	if (INPUT->GetKey(SDLK_RIGHT))
	{
		MoveRight();
		return true;

	}
	

	if (INPUT->GetKey(SDLK_LEFT))
	{
		MoveLeft();
		return true;


	}


	
}

void PlayerComponent::MoveDebug()
{
	if (INPUT->GetKey(SDLK_UP))
	{
		m_entity->GetTransform()->AddPosition(-m_playerSpeed * m_deltaTime * m_entity->GetTransform()->GetForward());
		m_entity->GetTransform()->SetRotation(glm::quatLookAt(m_entity->GetTransform()->GetForward(), m_entity->GetTransform()->GetUp()));

	}

	if (INPUT->GetKey(SDLK_DOWN))
	{
		m_entity->GetTransform()->AddPosition(m_playerSpeed * m_deltaTime * m_entity->GetTransform()->GetForward());
		m_entity->GetTransform()->SetRotation(glm::quatLookAt(-m_entity->GetTransform()->GetForward(), m_entity->GetTransform()->GetUp()));

	}
	if (INPUT->GetKey(SDLK_LEFT))
	{
		m_entity->GetTransform()->AddPosition(-m_playerSpeed * m_deltaTime * m_entity->GetTransform()->GetRight());
		m_entity->GetTransform()->SetRotation(glm::quatLookAt(-m_entity->GetTransform()->GetRight(), m_entity->GetTransform()->GetUp()));

	}


	if (INPUT->GetKey(SDLK_RIGHT))
	{
		m_entity->GetTransform()->AddPosition(m_playerSpeed * m_deltaTime * m_entity->GetTransform()->GetRight());
		m_entity->GetTransform()->SetRotation(glm::quatLookAt(m_entity->GetTransform()->GetRight(), m_entity->GetTransform()->GetUp()));

	}
}

float PlayerComponent::Distance(glm::vec3 a, glm::vec3 b)
{
	float dist;
	dist = std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z)* (a.z - b.z));
	return dist;
}
