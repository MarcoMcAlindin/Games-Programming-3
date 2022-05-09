#pragma once
#include "Scene.h"
#include "DirectionalLight.h"
#include "Skybox.h"
#include "PointLight.h"
#include "Fog.h"



class GameScene : public Scene
{
public:
	GameScene();

	GameScene(std::string name, int id) : Scene(name, id) {};

	void OnActivate() override;
	void OnDeactivate() override;

	void OnCreate() override;
	void OnDestroy() override;

	void Update(float deltaTime) override;
	void Render() override;
	void Input() override;

	void SpawnTrees();

	float cameraX;


	private:

	DirectionalLight* directionalLight;
	Skybox* skybox;
	Fog* m_fog;
	Entity* m_player;

};

	



