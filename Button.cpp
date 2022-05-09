#include "Input.h"
#include "Log.h"
#include "Button.h"
#include "pch.h"
#include "Application.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "SceneManager.h"




Button::Button(std::shared_ptr<Texture> texture, glm::vec3 position, glm::vec3 color, float opacity, glm::vec2 scale) : Sprite(texture, position, color, opacity, scale)
{
	
}


/*
=================================================================
Update the sprite position
=================================================================
*/


bool Button::isPressed(glm::vec2 theAreaClicked)
{
	glm::vec2 areaClicked = theAreaClicked;
	if (areaClicked.x > this->GetSpritePos().x && areaClicked.x < this->GetSpritePos().x + this->GetSpriteScale().x && areaClicked.y > this->GetSpritePos().y && areaClicked.y < this->GetSpritePos().y + this->GetSpriteScale().y)
	{
		this->clicked = true;
		return true;
	}
	else return false;
	

}
void Button::OnUpdate(float deltaTime)
{

	if (!SceneManager::GetInstance()->m_currentScene->m_buttonClicked && isPressed(SceneManager::GetInstance()->m_currentScene->areaClicked)) {
		OnClick();
	}
}

bool Button::isHovered(glm::vec2 theAreaHovered) 
{
	glm::vec2 areaHovered = theAreaHovered;
	if (areaHovered.x > this->GetSpritePos().x && areaHovered.x < this->GetSpritePos().x + this->GetSpriteScale().x && areaHovered.y > this->GetSpritePos().y && areaHovered.y < this->GetSpritePos().y + this->GetSpriteScale().y)
	{	
		return true;
	}
	return false;
}

void Button::OnRender() 
{
	Sprite::OnRender();
}


bool Button::getClicked()
{
	return this->clicked;
}

void Button::setClicked(bool state)
{
	this->clicked = state;
}

void Button::OnClick()
{
	SceneManager::GetInstance()->m_currentScene->m_buttonClicked = true;
}