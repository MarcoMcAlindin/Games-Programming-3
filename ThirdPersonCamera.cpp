#include "ThirdPersonCamera.h"
#include "pch.h"
#include "Camera.h"
#include "Input.h"
#include "Log.h"
#include "Resources.h"

void ThirdPersonCamera::OnUpdate(float deltaTime)
{
	m_deltaTime = deltaTime;



	if (SceneManager::GetInstance()->m_currentScene->GetEntity("Player") != nullptr)
		m_playerPos = SceneManager::GetInstance()->m_currentScene->GetEntity("Player")->GetTransform()->GetPosition();

	switch (Application::GetInstance()->m_currentGameState)
	{
	case GameState::GAME:

		RotateAround(SceneManager::GetInstance()->m_currentScene->GetEntity("Player"));
		if (m_playerFollow) FollowPlayer();
		Move(SceneManager::GetInstance()->m_currentScene->GetEntity("Player"));
		break;

	case GameState::DEBUG:



		break;
	}

	/*if(m_playerFollow)
	m_camera->GetParentTransform()->SetPosition(m_playerPos + offset);*/



}

void ThirdPersonCamera::OnRender()
{
}

void ThirdPersonCamera::Start()
{
	CameraComponent::Start();

	//Set initial camera speed
	m_cameraSpeed = 0.25f;

	m_offset = m_entity->GetTransform()->GetPosition();
}

void ThirdPersonCamera::MoveForward()
{
	m_camera->GetParentTransform()->AddPosition(m_cameraSpeed * m_deltaTime * m_camera->GetParentTransform()->GetForward());



}

void ThirdPersonCamera::MoveBack()
{
	m_camera->GetParentTransform()->AddPosition(-m_cameraSpeed * m_deltaTime * m_camera->GetParentTransform()->GetForward());

}

void ThirdPersonCamera::MoveUp()
{
	m_camera->GetParentTransform()->AddPosition(m_cameraSpeed * m_deltaTime * m_camera->GetParentTransform()->GetUp());

}

void ThirdPersonCamera::MoveDown()
{
	m_camera->GetParentTransform()->AddPosition(-m_cameraSpeed * m_deltaTime * m_camera->GetParentTransform()->GetUp());

}

void ThirdPersonCamera::MoveRight()
{
	m_camera->GetParentTransform()->AddPosition(m_cameraSpeed * m_deltaTime * m_camera->GetParentTransform()->GetRight());

}

void ThirdPersonCamera::MoveLeft()
{
	m_camera->GetParentTransform()->AddPosition(-m_cameraSpeed * m_deltaTime * m_camera->GetParentTransform()->GetRight());

}

void ThirdPersonCamera::Move(Entity* player)
{

	if (INPUT->GetKey(SDLK_UP)) MoveForward();

	if (INPUT->GetKey(SDLK_DOWN)) MoveBack();

	if (INPUT->GetKey(SDLK_w)) MoveUp();

	if (INPUT->GetKey(SDLK_s)) MoveDown();

	if (INPUT->GetKey(SDLK_LEFT)) MoveLeft();

	if (INPUT->GetKey(SDLK_RIGHT)) MoveRight();



	PRINT_VEC3("Camera Position ", m_entity->GetTransform()->GetPosition().x, m_entity->GetTransform()->GetPosition().y, m_entity->GetTransform()->GetPosition().z, 9);
}



void ThirdPersonCamera::RotateAround(Entity* player)
{
	m_playerFollow = false;
	if (INPUT->GetKey(SDLK_RIGHT))
	{
		m_entity->GetTransform()->RotateEulerAxis(1.6f, m_entity->GetTransform()->GetUp());
		m_camera->GetParentTransform()->AddPosition(-0.1f * m_camera->GetParentTransform()->GetRight());
	}

	if (INPUT->GetKey(SDLK_LEFT))
	{
		m_entity->GetTransform()->RotateEulerAxis(-1.6f, m_entity->GetTransform()->GetUp());
		m_entity->GetTransform()->AddPosition(0.1f * m_entity->GetTransform()->GetRight());
	}
	m_offset = m_entity->GetTransform()->GetPosition() - player->GetTransform()->GetPosition();
	m_playerFollow = true;
}

void ThirdPersonCamera::FollowPlayer()
{
	m_entity->GetTransform()->SetPosition(m_playerPos + m_offset);
}


