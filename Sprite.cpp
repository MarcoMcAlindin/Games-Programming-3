#include "Sprite.h"
#include <string>
#include "Application.h"
#include "Entity.h"
#include "Common.h"
#include "pch.h"
#include "Camera.h"
#include "Log.h"
#include "Vertex.h"

Sprite::Sprite(std::shared_ptr<Texture> texture, glm::vec3 position, glm::vec3 color, float opacity, glm::vec2 scale)
{
	
	m_texture = texture;
	m_position = position;
	m_scale = scale;
	m_opacity = opacity;
	m_color = color;

	m_program = Resources::GetInstance()->GetShader("sprite");

	unsigned int vbo;

	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_projection = glm::ortho(0.0f, static_cast<float>(Application::GetInstance()->GetWindowWidth()), static_cast<float>(Application::GetInstance()->GetWindowHeight()), 0.0f, -1.0f, 1.0f);

}


void Sprite::OnRender()
{
	m_program->Use();

	glm::mat4 transform = glm::mat4(1.0f);

	transform = glm::translate(transform, m_position);
	transform = glm::scale(transform, glm::vec3(m_scale.x,m_scale.y,1.0f));


	GLuint loc = glGetUniformLocation(m_program->Get(), "transform");
	glUniformMatrix4fv(loc, 1, false, (const GLfloat*)glm::value_ptr(transform));

	loc = glGetUniformLocation(m_program->Get(), "opacity");
	glUniform1f(loc, m_opacity);

	loc = glGetUniformLocation(m_program->Get(), "myTexture");
	glUniform1i(loc, 0);


	loc = glGetUniformLocation(m_program->Get(), "color");
	glUniform3f(loc, m_color.x, m_color.y, m_color.z);

	loc = glGetUniformLocation(m_program->Get(), "projection");
	glUniformMatrix4fv(loc, 1, false, (const GLfloat*)glm::value_ptr(m_projection));

	m_texture->Bind();
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);





}


void Sprite::OnUpdate(float deltaTime)
{
	
}

