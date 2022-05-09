#pragma once
#include "Scene.h"
class GameOverScene :  public Scene
{
public:
	GameOverScene();

	GameOverScene(std::string name, int id) : Scene(name, id) {};

	void OnActivate() override;
	void OnDeactivate() override;

	void OnCreate() override;
	void OnDestroy() override;

	void Update(float deltaTime) override;
	void Render() override;
	void Input() override;

	
};

