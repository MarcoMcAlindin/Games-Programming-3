#include "StartButton.h"
#include "SceneManager.h"

void StartButton::OnUpdate(float deltaTime)
{
	Button::OnUpdate(deltaTime);
}

void StartButton::OnRender()
{
	Button::OnRender();
}

void StartButton::OnClick()
{
	switch (SceneManager::GetInstance()->GetCurrentSceneID())
	{
	case 0:
		SceneManager::GetInstance()->LoadScene(1);
		break;

	case 1:
		SceneManager::GetInstance()->LoadScene(2);
		break;
	default:
		break;
	}

	Button::OnClick();
}