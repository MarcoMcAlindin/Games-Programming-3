#include "Skybox.h"
#include "pch.h"
#include "MeshRenderer.h"
#include "Entity.h"
#include "Common.h"
#include "Application.h"
#include "Camera.h"

Skybox::Skybox( std::shared_ptr<ShaderProgram> program)
{
	
	m_program = program;

	
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	// skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	std::vector<std::string> faces
	{
		ASSET_PATH + "Images/Textures/skybox/redeclipse_rt.jpg",
		ASSET_PATH + "Images/Textures/skybox/redeclipse_lf.jpg",
		ASSET_PATH + "Images/Textures/skybox/redeclipse_up.jpg",
		ASSET_PATH + "Images/Textures/skybox/redeclipse_dn.jpg",
		ASSET_PATH + "Images/Textures/skybox/redeclipse_ft.jpg",
		ASSET_PATH + "Images/Textures/skybox/redeclipse_bk.jpg",
	};

	cubemapTexture = skybox.loadCubemap(faces); //Load the cubemap using "faces" into cubemapTextures

	m_program->Use();
	GLuint skyboxLocation = glGetUniformLocation(m_program->Get(), "skybox");
	glUniform1i(skyboxLocation, 1);
	


}

void Skybox::OnRender()
{
	// change depth function so depth test passes when values are equal to depth buffer's content
	glDepthFunc(GL_LEQUAL);
	m_program->Use();


	view = glm::mat4(glm::mat3(SceneManager::GetInstance()->m_currentScene->GetCamera()->GetView()));
	viewMatrixLocation = glGetUniformLocation(m_program->Get(), "view");
	glUniformMatrix4fv(viewMatrixLocation, 1, false, (const GLfloat*)glm::value_ptr(view));

	projection = SceneManager::GetInstance()->m_currentScene->GetCamera()->GetProj();
	viewMatrixLocation = glGetUniformLocation(m_program->Get(), "projection");
	glUniformMatrix4fv(viewMatrixLocation, 1, false, (const GLfloat*)glm::value_ptr(projection));

	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	// set depth function back to default
	glDepthFunc(GL_LESS);


}

void Skybox::OnUpdate(float deltaTime)
{

}
