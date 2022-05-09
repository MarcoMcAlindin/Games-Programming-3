#pragma once
#include "Entity.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "InstructionsScene.h"
#include "SceneManager.h"


class Camera;


#define WINDOW_W Application::GetInstance()->GetWindowWidth()
#define WINDOW_H Application::GetInstance()->GetWindowHeight()


enum AppState
{
	INITIALISING, RUNNING, QUITTING
};

enum GameState
{
	GAME,
	DEBUG
};

enum SoundState
{
	OFF,
	ON
};


class Application
{

public:

	/*Public Functions
	-------------------*/
	~Application();

	//Get Application Instance
	static Application* GetInstance();

	//Run function for program entry point
	void Run();


	
	//Getters for Application windo size
	inline int GetWindowHeight() const { return m_windowHeight; }
	inline int GetWindowWidth() const { return m_windowWidth; }

	/*Public Variables
	-------------------*/

	//State of Application
	AppState m_appState = AppState::INITIALISING;

	//State of Game (DEBUG,GAME)
	GameState m_currentGameState = GameState::GAME;

	//Sound State
	SoundState m_appSoundState = SoundState::ON;

private:
	
	/*Private Functions
	-------------------*/

	Application();
	void Initialise();
	void OpenGlInitialise();
	void GameInitialise();
	void Loop();
	void Quit();
	void Update(float deltaTime);
	void Render();
	void Input();

	void LoadModels();
	

	/*Private Variables
	-------------------*/

	//Application Instance pointer
	static Application* m_application;

	//WindowSize
	int m_windowWidth = 1080;
	int m_windowHeight = 700;

	//Window pointer
	SDL_Window* m_window = nullptr;
	//SDL_Context pointer
	SDL_GLContext m_glContext = nullptr;
	//Gamepad pointer
	SDL_Joystick* joystick = nullptr;

	//SceneManager Instance pointer
	static SceneManager* m_sceneManager;
	
	//Scene shared pointers
	std::shared_ptr<MainMenuScene> m_mainMenuScene;
	std::shared_ptr<InstructionsScene> m_instructionsScene;
	std::shared_ptr<GameScene> m_gameScene;
	std::shared_ptr<GameOverScene> m_gameOverScene;

	//sound boolean
	bool m_sound = true;
	
	//Game delta time
	float m_worldDeltaTime = 0.f;

	
	//Game Sounds
	std::vector<std::string> soundList;
	std::vector<soundType> soundTypes;
	std::vector<std::string> soundsToUse;
};

