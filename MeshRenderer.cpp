#include "pch.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Common.h"
#include "Application.h"
#include "Camera.h"

MeshRenderer::MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program)
{
	m_model = model;
	m_program = program;

	
	/*Get uniform locations
	* -----------------------*/

	//Get view uniform Location
	viewMatrixLocation = glGetUniformLocation(m_program->Get(), "view");
	//Get projection uniform Location
	projectionMatrixLocation = glGetUniformLocation(m_program->Get(), "projection");
	//Get model uniform Location
	modelMatrixLocation = glGetUniformLocation(m_program->Get(), "model");
	//Get camera position uniform Location
	cameraPosLocation = glGetUniformLocation(m_program->Get(), "viewPosition");
	//Get Inverse Matrix Location
	inverseNormalMatrixLocation = glGetUniformLocation(m_program->Get(), "inverseNormalMatrix");

	//Get DL position uniform location
	m_DLightPositionLoc = glGetUniformLocation(m_program->Get(), "directionalLight.position");
	//Get DL direction uniform location
	m_DLightDirectionLoc = glGetUniformLocation(m_program->Get(), "directionalLight.direction");
	//Get DL ambient uniform location
	m_DLightAmbientLoc = glGetUniformLocation(m_program->Get(), "directionalLight.ambient");
	//Get DL diffuse uniform location
	m_DLightDiffuseLoc = glGetUniformLocation(m_program->Get(), "directionalLight.diffuse");
	//Get DL specular uniform location
	m_DLSpecularLoc = glGetUniformLocation(m_program->Get(), "directionalLight.specular");


	m_PLightPositionLoc = glGetUniformLocation(m_program->Get(), "pointLight.position");
	m_PLightConstantLoc = glGetUniformLocation(m_program->Get(), "pointLight.constant");
	m_PLightLinearLoc = glGetUniformLocation(m_program->Get(), "pointLight.linear");
	m_PLightQuadraticLoc = glGetUniformLocation(m_program->Get(), "pointLight.quadratic");

	m_PLightAmbientLoc = glGetUniformLocation(m_program->Get(), "pointLight.ambient");
	m_PLightDiffuseLoc = glGetUniformLocation(m_program->Get(), "pointLight.diffuse");
	m_PLightSpecularLoc = glGetUniformLocation(m_program->Get(), "pointLight.specular");


	//ShadowMappingSetup();

}

void MeshRenderer::OnUpdate(float deltaTime)
{
	m_entity->GetTransform()->AddPosition(m_entity->GetTransform()->GetTransXYZ());

}

void MeshRenderer::OnRender()
{

	//ShadowMappingRender();

	//Activate shader
	m_program->Use();


	//Get Vaules For Shader 
	view = SceneManager::GetInstance()->m_currentScene->GetCamera()->GetView();
	projection = SceneManager::GetInstance()->m_currentScene->GetCamera()->GetProj();
	model = m_entity->GetTransform()->GetTransformationMatrix();
	viewPosition = SceneManager::GetInstance()->m_currentScene->GetCamera()->GetParentTransform()->GetPosition();
	inverseNormalMatrix = glm::transpose(glm::inverse(model));

	/*========================================================================
			SET UNIFORMS FOR VIEW, PROJECTION, MODEL AND VIEW POSITION
	==========================================================================*/

	//Set view matrix uniform
	glUniformMatrix4fv(viewMatrixLocation, 1, false, (const GLfloat*)glm::value_ptr(view));
	//Set projection matrix uniform
	glUniformMatrix4fv(projectionMatrixLocation, 1, false, (const GLfloat*)glm::value_ptr(projection));
	//Set modelmatrix uniform
	glUniformMatrix4fv(modelMatrixLocation, 1, false, (const GLfloat*)glm::value_ptr(model));
	//Set Camera position uniform
	glUniform3f(cameraPosLocation, viewPosition.x, viewPosition.y, viewPosition.z);
	//Set inverse Normal Matrix uniform
	glUniformMatrix3fv(inverseNormalMatrixLocation, 1, false, (const GLfloat*)glm::value_ptr(inverseNormalMatrix));

	/*=================================================================================================================*/

	////Get and Set Ambient Light Strength uniform
	//directionalLightLocations = glGetUniformLocation(m_program->Get(), "ambientStrength");
	//glUniform1f(directionalLightLocations, DirectionalLight::GetInstance()->AmbientStrength());
	////Get and Set Specular Lighting Strength uniform
	//directionalLightLocations = glGetUniformLocation(m_program->Get(), "ambientStrength");
	//glUniform1f(directionalLightLocations, DirectionalLight::GetInstance()->SpecularStrength());


	/*===================================================================================
							  SET LIGHT UNIFORMS
	====================================================================================*/

	//DIRECTIONAL LIGHT

	//Set light position uniform  
	glUniform3f(m_DLightPositionLoc, DirectionalLight::GetInstance()->Position().x, DirectionalLight::GetInstance()->Position().y, DirectionalLight::GetInstance()->Position().z);
	//Set Directional light direction uniform
	glUniform3f(m_DLightDirectionLoc, DirectionalLight::GetInstance()->Direction().x, DirectionalLight::GetInstance()->Direction().y, DirectionalLight::GetInstance()->Direction().z);
	//Set light ambient color value uniform  
	glUniform3f(m_DLightAmbientLoc, DirectionalLight::GetInstance()->Ambient().x, DirectionalLight::GetInstance()->Ambient().y, DirectionalLight::GetInstance()->Ambient().z);
	//Set light diffuse color value uniform  
	glUniform3f(m_DLightDiffuseLoc, DirectionalLight::GetInstance()->Diffuse().x, DirectionalLight::GetInstance()->Diffuse().y, DirectionalLight::GetInstance()->Diffuse().z);
	//Set light specular value uniform  
	glUniform3f(m_DLSpecularLoc, DirectionalLight::GetInstance()->Specular().x, DirectionalLight::GetInstance()->Specular().y, DirectionalLight::GetInstance()->Specular().z);

	//POINT LIGHT (ORB)
	glUniform3f(m_PLightPositionLoc,SceneManager::GetInstance()->m_currentScene->m_orbSphere->GetTransform()->GetPosition().x, SceneManager::GetInstance()->m_currentScene->m_orbSphere->GetTransform()->GetPosition().y, SceneManager::GetInstance()->m_currentScene->m_orbSphere->GetTransform()->GetPosition().z);
	glUniform3f(m_PLightAmbientLoc, SceneManager::GetInstance()->m_currentScene->m_orb->Ambient().x, SceneManager::GetInstance()->m_currentScene->m_orb->Ambient().y, SceneManager::GetInstance()->m_currentScene->m_orb->Ambient().z);
	glUniform3f(m_PLightDiffuseLoc, SceneManager::GetInstance()->m_currentScene->m_orb->Diffuse().x, SceneManager::GetInstance()->m_currentScene->m_orb->Diffuse().y, SceneManager::GetInstance()->m_currentScene->m_orb->Diffuse().z);
	glUniform3f(m_PLightSpecularLoc, SceneManager::GetInstance()->m_currentScene->m_orb->Specular().x, SceneManager::GetInstance()->m_currentScene->m_orb->Specular().y, SceneManager::GetInstance()->m_currentScene->m_orb->Specular().z);

	glUniform1f(m_PLightConstantLoc, SceneManager::GetInstance()->m_currentScene->m_orb->Constant());
	glUniform1f(m_PLightLinearLoc, SceneManager::GetInstance()->m_currentScene->m_orb->Linear());
	glUniform1f(m_PLightQuadraticLoc, SceneManager::GetInstance()->m_currentScene->m_orb->Quadratic());


	/*==================================================================================================================*/

	Fog* fog = Fog::GetInstance();
	//Set fog values
	GLuint fogLocations = glGetUniformLocation(m_program->Get(), "fog.MaxDist");
	glUniform1f(fogLocations, fog->GetMaxDist());
	fogLocations = glGetUniformLocation(m_program->Get(), "fog.fogHeigth");
	glUniform1f(fogLocations, fog->GetHeight());
	fogLocations = glGetUniformLocation(m_program->Get(), "fog.MinDist");
	glUniform1f(fogLocations, fog->GetMinDist());
	fogLocations = glGetUniformLocation(m_program->Get(), "fog.Color");
	glUniform3f(fogLocations, fog->GetColor().x, fog->GetColor().y, fog->GetColor().z);

	//Bind Materials for every mesh of the model
	for (Mesh* mesh : m_model->GetMeshes())
	{
		mesh->BindMaterials(m_program);
	}


}

