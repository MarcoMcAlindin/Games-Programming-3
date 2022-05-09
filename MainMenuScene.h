#pragma once
#include "Scene.h"

class Scene;

class MainMenuScene : public Scene
{
public:

	

	MainMenuScene();

	MainMenuScene(std::string name, int id) : Scene(name, id) {};

	void OnCreate() override;
	void OnDestroy() override;

	void OnActivate() override;
	void OnDeactivate() override;


	void Update(float deltaTime) override;
	void Render() override;
	void Input() override;


	
};

