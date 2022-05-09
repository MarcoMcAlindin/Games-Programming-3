	
#ifndef _CBUTTON_H
#define _CBUTTON_H
#include "Sprite.h"
#include "Application.h"

class Button : public Sprite
{
public:

	Button(std::shared_ptr<Texture> texture, glm::vec3 position, glm::vec3 color, float opacity, glm::vec2 scale);

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	virtual void OnClick();

	bool isPressed(glm::vec2 theAreaClicked);
	bool isHovered(glm::vec2 theAreaHovered);
	
	bool getClicked();
	void setClicked(bool state);
	void SetTexture(std::shared_ptr<Texture> texture) { m_texture = texture; }


protected:

	bool clicked = false;


private:

	
	

};
#endif