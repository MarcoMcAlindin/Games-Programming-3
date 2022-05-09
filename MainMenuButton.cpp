#include "MainMenuButton.h"
#include "SceneManager.h"

void MainMenuButton::OnUpdate(float deltaTime)
{
	Button::OnUpdate(deltaTime);
}

void MainMenuButton::OnRender()
{
	Button::OnRender();
}

void MainMenuButton::OnClick()
{
	SceneManager::GetInstance()->LoadScene(0);
	Button::OnClick();
}