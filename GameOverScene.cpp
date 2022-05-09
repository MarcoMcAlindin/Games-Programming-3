#include "GameOverScene.h"
#include "Application.h"
#include "Button.h"

GameOverScene::GameOverScene(){}

void GameOverScene::OnCreate()
{
	Entity* tempEntity = new Entity("BackgroundImage");
	tempEntity->AddComponent(new Sprite(Resources::GetInstance()->GetTexture("Images/Instructions_Screen.png"), glm::vec3(0.0f, 0.0f, -.05f), glm::vec3(1.0f, 1.0f, 1.0f), 0.4f, glm::vec2(Application::GetInstance()->GetWindowWidth() + 100.0f, Application::GetInstance()->GetWindowHeight() + 100.0f)));
	m_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Title");
	tempEntity->AddComponent(new Button(Resources::GetInstance()->GetTexture("Images/Game_Over.png"), glm::vec3(120.0f, 30.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(800.0f, 700.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Start_Button");
	tempEntity->AddComponent(new Button(Resources::GetInstance()->GetTexture("Images/Buttons/Restart_Button.png"), glm::vec3(20.0f, 530.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(300.0f, 200.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Quit_Button");
	tempEntity->AddComponent(new Button(Resources::GetInstance()->GetTexture("Images/Buttons/Quit_Button.png"), glm::vec3(750.0f, 530.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(300.0f, 200.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

}

void GameOverScene::OnDestroy() {}

void GameOverScene::OnActivate() {}

void GameOverScene::OnDeactivate() {}

void GameOverScene::Update(float deltaTime) 
{
	Scene::Update(deltaTime);
}

void GameOverScene::Render() 
{
	Scene::Render();
}

void GameOverScene::Input() 
{
	Scene::Input();
}




