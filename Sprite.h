#pragma once
#pragma once
#include "Component.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"
class Sprite : public Component
{

public:

	Sprite(std::shared_ptr<Texture> texture,glm::vec3 position, glm::vec3 color,float opacity, glm::vec2 scale);
	

	virtual void OnRender() override;
	virtual void OnUpdate(float deltaTime) override;
	
	std::shared_ptr<ShaderProgram> m_program;
	std::shared_ptr<Texture> m_texture;

	void SetSpriteScale(glm::vec2 scale) { m_scale = scale; }
	glm::vec2 GetSpriteScale() { return m_scale; }


	void SetSpritePos(glm::vec3 position) { m_position.x = position.x; m_position.y = position.y; }
	glm::vec3 GetSpritePos() { return m_position; }

	void AddSpritePosition(glm::vec3 delta) { m_position += delta; }

	void SetOpacity(float opacity) { m_opacity = opacity; }

protected:

	float m_opacity;

private:

	glm::mat4 m_projection;
	GLuint m_vao;

	
	glm::vec2 m_scale;
	glm::vec3 m_position;
	glm::vec3 m_color;

	
};

