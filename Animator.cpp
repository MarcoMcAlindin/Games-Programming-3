#include "Animator.h"
#include "Entity.h"
#include "pch.h"
#include "Camera.h"
#include "ShaderProgram.h"

Animator::Animator() {}

Animator::Animator(std::shared_ptr<Animation> currentAnimation, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Model> model)
{
	m_program = program;
	m_model = model;
    m_CurrentTime = 0.0;
    m_CurrentAnimation = currentAnimation;
	this->AddAnimation(m_CurrentAnimation, "Idle");

    m_FinalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
        m_FinalBoneMatrices.push_back(glm::mat4(1.0f));

	//GET LOCATIONS FOR SHADER

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
}

void Animator::OnUpdate(float deltaTime)
{
	//m_entity->GetTransform()->AddPosition(m_entity->GetTransform()->GetTransXYZ());

    
    if (m_CurrentAnimation)
    {
        m_CurrentTime += m_CurrentAnimation->GetTicksPerSecond() * deltaTime * 0.2f;
        m_CurrentTime = fmod(m_CurrentTime, m_CurrentAnimation->GetDuration());
        CalculateBoneTransform(&m_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
    }
	
}

void Animator::OnRender()
{
	m_program->Use();

	auto transforms = GetPoseTransforms();
	for (int i = 0; i < transforms.size(); ++i)
	{
		GLuint boneTransformationLocation = glGetUniformLocation(m_program->Get(), (("finalBoneMatrices[") + std::to_string(i) + "]").c_str());
		glUniformMatrix4fv(boneTransformationLocation, 1, false, (const GLfloat*)glm::value_ptr(transforms[i]));

	}


	view = SceneManager::GetInstance()->m_currentScene->GetCamera()->GetView();
	projection = SceneManager::GetInstance()->m_currentScene->GetCamera()->GetProj();
	model = m_entity->GetTransform()->GetTransformationMatrix();
	viewPosition = SceneManager::GetInstance()->m_currentScene->GetCamera()->GetParentTransform()->GetPosition();
	inverseNormalMatrix = glm::transpose(glm::inverse(model));
	/*========================================================================
		GET AND SET UNIFORMS FOR VIEW, PROJECTION, MODEL AND VIEW POSITION
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

	//Get and Set Ambient Light Strength uniform
	directionalLightLocations = glGetUniformLocation(m_program->Get(), "ambientStrength");
	glUniform1f(directionalLightLocations, DirectionalLight::GetInstance()->AmbientStrength());
	//Get and Set Specular Lighting Strength uniform
	directionalLightLocations = glGetUniformLocation(m_program->Get(), "ambientStrength");
	glUniform1f(directionalLightLocations, DirectionalLight::GetInstance()->SpecularStrength());


	/*===================================================================================
							GET AND SET LIGHT UNIFORMS
	====================================================================================*/

	//Get and set light position uniform  
	directionalLightLocations = glGetUniformLocation(m_program->Get(), "light.position");
	glUniform3f(directionalLightLocations, DirectionalLight::GetInstance()->Position().x, DirectionalLight::GetInstance()->Position().y, DirectionalLight::GetInstance()->Position().z);
	//Get and Set Directional light direction uniform
	directionalLightLocations = glGetUniformLocation(m_program->Get(), "light.direction");
	glUniform3f(directionalLightLocations, DirectionalLight::GetInstance()->Direction().x, DirectionalLight::GetInstance()->Direction().y, DirectionalLight::GetInstance()->Direction().z);
	//Get and set light ambient color value uniform  
	directionalLightLocations = glGetUniformLocation(m_program->Get(), "light.ambient");
	glUniform3f(directionalLightLocations, DirectionalLight::GetInstance()->Ambient().x, DirectionalLight::GetInstance()->Ambient().y, DirectionalLight::GetInstance()->Ambient().z);
	//Get and set light diffuse color value uniform  
	directionalLightLocations = glGetUniformLocation(m_program->Get(), "light.diffuse");
	glUniform3f(directionalLightLocations, DirectionalLight::GetInstance()->Diffuse().x, DirectionalLight::GetInstance()->Diffuse().y, DirectionalLight::GetInstance()->Diffuse().z);
	//Get and set light specular value uniform  
	directionalLightLocations = glGetUniformLocation(m_program->Get(), "light.specular");
	glUniform3f(directionalLightLocations, DirectionalLight::GetInstance()->Specular().x, DirectionalLight::GetInstance()->Specular().y, DirectionalLight::GetInstance()->Specular().z);


	//Set fog values
	GLuint fogLocations = glGetUniformLocation(m_program->Get(), "fog.MaxDist");
	glUniform1f(fogLocations, 900.0f);
	fogLocations = glGetUniformLocation(m_program->Get(), "fog.fogHeigth");
	glUniform1f(fogLocations, 900.0f);
	fogLocations = glGetUniformLocation(m_program->Get(), "fog.MinDist");
	glUniform1f(fogLocations, 500.4f);
	fogLocations = glGetUniformLocation(m_program->Get(), "fog.Color");
	glUniform3f(fogLocations, 0.01f, 0.01f, 0.01f);

	//Bind Materials for every mesh of the model
	for (Mesh* mesh : m_model->GetMeshes())
	{
		mesh->BindMaterials(m_program);
	}

}

void Animator::PlayAnimation(std::shared_ptr<Animation> pAnimation)
{
    m_CurrentAnimation = pAnimation;
    m_CurrentTime = 0.0f;
}

void Animator::CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform)
{
    std::string nodeName = node->name;
    glm::mat4 nodeTransform = node->transformation;

    Bone* Bone = m_CurrentAnimation->FindBone(nodeName);

    if (Bone)
    {
        Bone->Update(m_CurrentTime);
        nodeTransform = Bone->GetLocalTransform();
    }

    glm::mat4 globalTransformation = parentTransform * nodeTransform;

    auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end())
    {
        int index = boneInfoMap[nodeName].id;
        glm::mat4 offset = boneInfoMap[nodeName].offset;
        m_FinalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);
}

