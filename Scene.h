#pragma once
#include "Resources.h"
#include "Entity.h"
#include "Sprite.h"
#include "Log.h"
#include "SoundMgr.h"
#include "PointLight.h"
enum GamePause
{
	PAUSED,
	PLAYING
};

class Camera;

class Scene
{
public:


	Scene();

	Scene(std::string name, int id);

	virtual void OnCreate() = 0;

	virtual void OnDestroy() = 0;

	virtual void Update(float deltaTime);

	virtual void Render();

	virtual void Input();
	
	virtual void OnDeactivate() = 0;
	
	virtual void OnActivate() = 0; 

	Camera* GetCamera() { return m_activeCamera; }
	

	void SetCamera(Camera* camera) { m_activeCamera = camera; }

	Entity* GetEntity(std::string name) { return m_entities[name]; }
	Entity* GetUIEntity(std::string name) { return m_UI_entities[name]; }

	glm::vec2 areaClicked;
	glm::vec2 areaHovered;

	bool m_buttonClicked = false;

	int m_sceneID;

	GamePause m_gamePause = GamePause::PLAYING;

	std::unordered_map<std::string, Entity*> m_sceneCameras;

	PointLight* m_orb;

	Entity* m_orbSphere;

	int m_playerScore;

	glm::vec3 m_orbPositions[4];



private:

	

protected:

	std::string m_sceneName = "";

	std::unordered_map<std::string, Entity*> m_entities;

	std::unordered_map<std::string, Entity*> m_UI_entities;


	Camera* m_activeCamera;


};

