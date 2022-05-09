#include "Scene.h"
#include "Resources.h"
#include "Entity.h"
#include "Sprite.h"
#include "Application.h"
#include "Input.h"
#include "Button.h"
#include "SoundButton.h"

Scene::Scene()
{

}

Scene::Scene(std::string name, int id)
{
	m_sceneName = name;
	m_sceneID = id;
}

void Scene::OnCreate()
{
	Entity* tempEntity = new Entity("Sound_Button");
	tempEntity->AddComponent(new SoundButton(Resources::GetInstance()->GetTexture("Images/Buttons/Sound_On.png"), glm::vec3(930.0f, 10.0f, .2f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(200.0f, 100.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });


	CONSOLE_LOG_DEBUG(m_sceneName + " " + "Created...", 2);
}

void Scene::Update(float deltaTime)
{
	for (auto e : m_entities)
	{
		e.second->OnUpdate(deltaTime);
	}

	for (auto e : m_UI_entities)
	{
		e.second->OnUpdate(deltaTime);
	}

	for (auto e : m_sceneCameras)
	{
		e.second->OnUpdate(deltaTime);
	}
}

void Scene::Render()
{
	for (auto e : m_entities)
	{
		e.second->OnRender();
	}

	for (auto e : m_UI_entities)
	{
		e.second->OnRender();
	}

	for (auto e : m_sceneCameras)
	{
		e.second->OnRender();
	}
}

void Scene::Input()
{

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_QUIT:
			Application::GetInstance()->m_appState = AppState::QUITTING;
			break;
		case SDL_WINDOWEVENT_CLOSE:

			Application::GetInstance()->m_appState = AppState::QUITTING;
			break;
		case SDL_KEYDOWN:

			INPUT->SetKey(event.key.keysym.sym, true);
			break;
		case SDL_KEYUP:

			INPUT->SetKey(event.key.keysym.sym, false);
			break;
		case SDL_MOUSEMOTION:

			INPUT->MoveMouse(glm::vec2(event.motion.x, event.motion.y));

			break;

		case SDL_MOUSEBUTTONDOWN:

			areaClicked = { event.motion.x, event.motion.y };
			break;

		case SDL_MOUSEBUTTONUP:

			m_buttonClicked = false;
			areaClicked = glm::vec2(NULL, NULL);
			break;
		}


	}
}

void Scene::OnActivate()
{
	CONSOLE_LOG_DEBUG(m_sceneName + " " + "Activated/Loaded...", 3);
}

void Scene::OnDeactivate()
{

}

