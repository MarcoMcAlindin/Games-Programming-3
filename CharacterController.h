#pragma once
#include "Component.h"
#include "Input.h"
#include "pch.h"
class CharacterController : public Component
{
public:

	CharacterController();

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void SetCharacterSpeed(float speed) { m_characterSpeed = speed; }

private:

	float m_characterSpeed =  1;

};

