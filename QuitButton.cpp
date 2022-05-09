#include "QuitButton.h"
#include "SceneManager.h"

void QuitButton::OnUpdate(float deltaTime)
{
	Button::OnUpdate(deltaTime);
}

void QuitButton::OnRender()
{
	Button::OnRender();
}

void QuitButton::OnClick()
{
	
	Application::GetInstance()->m_appState = AppState::QUITTING;
	Button::OnClick();
}