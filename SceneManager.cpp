#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager* SceneManager::m_instance = nullptr;

SceneManager* SceneManager::GetInstance() 
{
	if (m_instance == nullptr)
	{
		m_instance = new SceneManager;
	}
	return m_instance;
}

void SceneManager::Update(float deltaTime) 
{
	if(m_currentScene) m_currentScene->Update(deltaTime);
}

void SceneManager::Render() 
{
	if(m_currentScene) m_currentScene->Render();
}

void SceneManager::Input() 
{
	if(m_currentScene) m_currentScene->Input();
}

unsigned int SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	auto tempScene = m_scenes.insert(std::make_pair(currentSceneID, scene));

	currentSceneID++;

	tempScene.first->second->OnCreate();

	return currentSceneID - 1;

}

void SceneManager::LoadScene(unsigned int sceneID)
{
	auto temp = m_scenes.find(sceneID);

	if (temp != m_scenes.end()) 
	{
		if (m_currentScene) m_currentScene->OnDeactivate();

		m_currentScene = temp->second;
		m_currentScene->OnActivate();
	}
}
