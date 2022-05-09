#pragma once
#include "pch.h"
#include "Component.h"
#include "ShaderProgram.h"
#include "Texture.h"

class Skybox : public Component
{
private:

	/*Private Functions
	--------------------*/
	
	
	

	

	/*Private Variables
	--------------------*/

	//Shader program
	std::shared_ptr <ShaderProgram> m_program;
	//Skybox Texture
	Texture skybox;
	//Vertex Array, Buffer Objects and Cubemap Texture
	GLuint skyboxVAO, skyboxVBO, cubemapTexture;
	//Faces
	std::vector<std::string> faces;

	glm::mat4 view;
	glm::mat4 projection;
	
	//Uniform Locations
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;
	GLuint modelMatrixLocation;
	
	
public:
	/*Public Functions
	--------------------*/
	// Inherited via Component
	
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	/*Public Functions
	--------------------*/

	Skybox(std::shared_ptr <ShaderProgram> program);

	
};

