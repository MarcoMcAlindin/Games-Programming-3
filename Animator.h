#pragma once
#include "Animation.h"
#include "Component.h"
#include "SceneManager.h"

class Animator : public Component
{
public:

	/*Public variables
	----------------------*/

	std::unordered_map<std::string, std::shared_ptr<Animation>> m_animations;
    
	/*Public Methods
	----------------------*/

	//Constructors
	Animator();
    Animator(std::shared_ptr<Animation> Animation, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Model> model);    

	//Play Current Animation
    void PlayAnimation(std::shared_ptr<Animation> animation);
    
	//Calculate transform of bone
    void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

	//Inherited virtual Methods from Component class
    void OnUpdate(float deltaTime) override;
    void OnRender() override;


	void AddAnimation(std::shared_ptr<Animation> animation, std::string name) { m_animations.insert({ name, animation }); }


	//Getters

	std::vector<glm::mat4> GetFinalBoneMatrices() { return m_FinalBoneMatrices; }
	std::vector<glm::mat4> GetPoseTransforms() { return m_FinalBoneMatrices; }
	std::shared_ptr<Model> GetModel() { return m_model; }
	//Setters

	void SetCurrentAnimation(std::shared_ptr<Animation> animation) { m_CurrentAnimation = animation; }
	std::shared_ptr<Animation> GetAnimation(std::string anim) { return m_animations[anim]; }

	

private:


	/*Private variables
	----------------------*/

	std::shared_ptr<Model> m_model;
	std::shared_ptr <ShaderProgram> m_program;


	std::vector<glm::mat4> m_FinalBoneMatrices;
	std::shared_ptr<Animation> m_CurrentAnimation;
	float m_CurrentTime;
	float m_DeltaTime;

	//Uniform Locations
	GLuint viewMatrixLocation;
	GLuint projectionMatrixLocation;
	GLuint modelMatrixLocation;
	GLuint inverseNormalMatrixLocation;

	GLuint cameraPosLocation ;
	GLuint directionalLightLocations;


	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model;
	glm::vec3 viewPosition;
	glm::mat3 inverseNormalMatrix;
	glm::mat4 lightSpaceMatrix;

	glm::mat4 lightProjection, lightView;

	float nearPlane = 1.0f, farPlane = 7.5f;

	/*Private Methods
	----------------------*/
	
};

