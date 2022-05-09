#pragma once
#include "Scene.h"
#include "pch.h"

class SceneManager
{
private:

	
	std::unordered_map<unsigned int, std::shared_ptr<Scene>> m_scenes;

	unsigned int currentSceneID;

	static SceneManager* m_instance;

public:

	SceneManager();

	static SceneManager* GetInstance();

	void Update(float deltaTime);

	void Render();

	void Input();

	void LoadScene(unsigned int sceneID);

	unsigned int AddScene(std::shared_ptr<Scene> scene);

	std::shared_ptr<Scene> m_currentScene;

	int GetCurrentSceneID() { return m_currentScene->m_sceneID; }

	

};

