#include "CameraButton.h"
#include "SceneManager.h"
#include "CameraComponent.h"



void CameraButton::OnUpdate(float deltaTime)
{
	Button::OnUpdate(deltaTime);
	
	
	
}

void CameraButton::OnRender()
{
	Button::OnRender();
}

void CameraButton::OnClick()
{
	SwitchCamera();
	Button::OnClick();
}

void CameraButton::SwitchCamera()
{
	
}

