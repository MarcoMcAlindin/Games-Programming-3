#include "CharacterController.h"
#include "Entity.h"

CharacterController::CharacterController()
{

}

void CharacterController::OnUpdate(float deltaTime)
{
	/*========================================================
					PROCESS INPUT AND MOVE ENTITY 
	=========================================================*/


	if (INPUT->GetKey(SDLK_UP))
	{
		m_entity->GetTransform()->AddPosition(m_entity->GetTransform()->GetForward() * deltaTime * m_characterSpeed);
	}

	if (INPUT->GetKey(SDLK_DOWN))
	{
		m_entity->GetTransform()->AddPosition(m_entity->GetTransform()->GetForward() * deltaTime * -m_characterSpeed);
	}

	if (INPUT->GetKey(SDLK_LEFT))
	{
		m_entity->GetTransform()->AddPosition(m_entity->GetTransform()->GetRight() * deltaTime * -m_characterSpeed);
	}

	if (INPUT->GetKey(SDLK_RIGHT))
	{
		m_entity->GetTransform()->AddPosition(m_entity->GetTransform()->GetRight() * deltaTime * m_characterSpeed);
	}
}

void CharacterController::OnRender()
{

}

