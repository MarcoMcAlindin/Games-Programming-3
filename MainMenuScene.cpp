#include "MainMenuScene.h"
#include <windows.h>
#include "Application.h"
#include "Input.h"
#include "StartButton.h"
#include "QuitButton.h"


MainMenuScene::MainMenuScene()
{
}

void MainMenuScene::OnCreate()
{

	Scene::OnCreate();

	Entity* tempEntity = new Entity("BackgroundImage");
	tempEntity->AddComponent(new Sprite(Resources::GetInstance()->GetTexture("Images/bkg_img.jpg"), glm::vec3(0.0f, 0.0f, -.05f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(Application::GetInstance()->GetWindowWidth(), Application::GetInstance()->GetWindowHeight())));
	m_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Title");
	tempEntity->AddComponent(new Button(Resources::GetInstance()->GetTexture("Images/Title.png"), glm::vec3(100.0f, 100.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(900.0f, 200.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Start_Button");
	tempEntity->AddComponent(new StartButton(Resources::GetInstance()->GetTexture("Images/Buttons/Start_Button.png"), glm::vec3(150.0f, 500.0f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(300.0f,200.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Quit_Button");
	tempEntity->AddComponent(new QuitButton(Resources::GetInstance()->GetTexture("Images/Buttons/Quit_Button.png"), glm::vec3(580.0f, 500.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(300.0f, 200.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

}

void MainMenuScene::OnDestroy()
{

}

void MainMenuScene::OnActivate()
{
	Scene::OnActivate();
}

void MainMenuScene::OnDeactivate()
{

}

void MainMenuScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	
}

void MainMenuScene::Render()
{
	Scene::Render();
}

void MainMenuScene::Input()
{
	Scene::Input();
}

