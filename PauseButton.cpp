#include "PauseButton.h"
#include "SceneManager.h"

void PauseButton::OnUpdate(float deltaTime)
{
	Button::OnUpdate(deltaTime);
}

void PauseButton::OnRender()
{
	Button::OnRender();
}

void PauseButton::OnClick()
{
	switch (SceneManager::GetInstance()->m_currentScene->m_gamePause)
	{
	case PAUSED:
		SceneManager::GetInstance()->m_currentScene->m_gamePause = GamePause::PLAYING;
		SceneManager::GetInstance()->m_currentScene->GetUIEntity("Pause_Menu")->isActive = false;
		break;

	case PLAYING:
		SceneManager::GetInstance()->m_currentScene->m_gamePause = GamePause::PAUSED;
		SceneManager::GetInstance()->m_currentScene->GetUIEntity("Pause_Menu")->isActive = true;


		break;
	default:
		break;
	}

	Button::OnClick();
}