#include "pch.h"
#include "CameraComponent.h"
#include "Camera.h"
#include "Input.h"
#include "Log.h"
#include "Resources.h"

void CameraComponent::OnUpdate(float deltaTime)
{
	//if(m_Target != nullptr) RecalculateOffset();
}

void CameraComponent::OnRender()
{
}

void CameraComponent::Start()
{
	//Set camera object
	m_camera = new Camera(m_entity->GetTransform());


}

void CameraComponent::Start(Transform* target)
{
	m_camera = new Camera(m_entity->GetTransform());
	InitialiseTargetSystem(target);
}

void CameraComponent::InitialiseTargetSystem(Transform* target)
{
	m_Target = target;
	m_cameraOffset = target->GetPosition() - m_entity->GetTransform()->GetPosition();
}

void CameraComponent::RecalculateOffset() 
{
	m_entity->GetTransform()->SetPosition(m_Target->GetPosition() - m_cameraOffset);
}
