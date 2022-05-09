#pragma once
#include "Component.h"
#include "Button.h"

class SoundButton : public Button
{
public:

	/*Public Variables
	--------------------*/

	//Constructor
	SoundButton(std::shared_ptr<Texture> texture, glm::vec3 position, glm::vec3 color, float opacity, glm::vec2 scale) : Button(texture, position, color, opacity, scale) {};



	/*Public Methods
	--------------------*/

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
	virtual void OnClick() override;

private:


	/*Private Variables
	--------------------*/
	

	/*Private Methods
	--------------------*/

};

