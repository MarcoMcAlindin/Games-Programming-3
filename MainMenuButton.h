#pragma once
#include "Button.h"
class MainMenuButton : public Button
{

public:

	MainMenuButton(std::shared_ptr<Texture> texture, glm::vec3 position, glm::vec3 color, float opacity, glm::vec2 scale) : Button(texture, position, color, opacity, scale) {};

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	virtual void OnClick() override;

private:


};

