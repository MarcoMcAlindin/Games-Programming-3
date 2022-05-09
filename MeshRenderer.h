#pragma once

#include "Component.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "Animator.h"


class MeshRenderer : public Component
{
private:

	//Pointers to model and shader program 
	std::shared_ptr<Model> m_model;
	std::shared_ptr <ShaderProgram> m_program;
	

	std::shared_ptr<ShaderProgram> m_depthShader;

	/*UNIFORM LOCATIONS
	* ------------------*/

	//Matrices
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;
	GLuint modelMatrixLocation;
	GLuint inverseNormalMatrixLocation;

	//Camera position
	GLuint cameraPosLocation;

	//Directional Light
	GLuint m_DLightPositionLoc;
	GLuint m_DLightDirectionLoc;
	GLuint m_DLightAmbientLoc;
	GLuint m_DLightDiffuseLoc;
	GLuint m_DLSpecularLoc;

	//Point Light

	GLuint m_PLightPositionLoc;
	GLuint m_PLightConstantLoc;
	GLuint m_PLightLinearLoc;
	GLuint m_PLightQuadraticLoc;

	GLuint m_PLightAmbientLoc;
	GLuint m_PLightDiffuseLoc;
	GLuint m_PLightSpecularLoc;

	
	//-----------------------


	//Values for shader uniforms
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model;
	glm::vec3 viewPosition;
	glm::mat3 inverseNormalMatrix;
	glm::mat4 lightSpaceMatrix;

	glm::mat4 lightProjection, lightView;

	float nearPlane = 1.0f, farPlane = 7.5f;


	/*unsigned int depthMapFBO;
	unsigned int depthMap;*/



public:

	
	MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr <ShaderProgram> program);
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void ShadowMappingSetup();

	void ShadowMappingRender();
};



