#include "InstructionsScene.h"
#include "StartButton.h"
#include "MainMenuButton.h"

InstructionsScene::InstructionsScene() {}

void InstructionsScene::OnCreate() 
{
	Scene::OnCreate();

	Entity* tempEntity = new Entity("Main_Menu_Button");
	tempEntity->AddComponent(new MainMenuButton(Resources::GetInstance()->GetTexture("Images/Buttons/MainMenu_Button.png"), glm::vec3(20.0f, 520.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(300.0f, 200.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Start_Game_Button");
	tempEntity->AddComponent(new StartButton(Resources::GetInstance()->GetTexture("Images/Buttons/Start_Button.png"), glm::vec3(750.0f, 520.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(300.0f, 200.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	new Entity("Sound_Instructions_Button");
	tempEntity->AddComponent(new Button(Resources::GetInstance()->GetTexture("Images/Sound_Instructions.png"), glm::vec3(620.0f, 50.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(300.0f, 300.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Camera_Instructions");
	tempEntity->AddComponent(new Button(Resources::GetInstance()->GetTexture("Images/Camera_Instructions.png"), glm::vec3(20.0f, 20.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(300.0f, 300.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Movement_Instructions");
	tempEntity->AddComponent(new Button(Resources::GetInstance()->GetTexture("Images/Arrows.png"), glm::vec3(330.0f, 200.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(500.0f, 500.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

}

void InstructionsScene::OnDestroy() {}

void InstructionsScene::OnActivate() {}

void InstructionsScene::OnDeactivate() {}

void InstructionsScene::Update(float deltaTime) 
{
	Scene::Update(deltaTime);
}

void InstructionsScene::Render() 
{
	Scene::Render();
}

void InstructionsScene::Input() 
{
	Scene::Input();
}
