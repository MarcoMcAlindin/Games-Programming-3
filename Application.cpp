#include "pch.h"
//#include "Application.h"
//#include "Common.h"
//
//#include "Quad.h"
//
//#include "Input.h"
//#include "Resources.h"
//
//
//#include "Light.h"
//#include "Sprite.h"
//#include "Texture.h"
//#include <string>
//
////Include Physics
//#include "Physics.h"
//
////Include ...
//#include "Sound.h"
//
////Include Game Managers
//#include "SoundMgr.h"
//
////Include Components
//#include "Components.h"
//
////Iclude Collision Shapes
//#include "BoxShape.h"



//Set Application, Sound Manager and SceneManager Instance
Application* Application::m_application = nullptr;
static SceneManager* m_sceneManager = SceneManager::GetInstance();
static SoundMgr* soundMgr = SoundMgr::getInstance();


Application::Application()
{

}

void Application::Initialise()
{

	
	//performing initialization
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		LOG_DEBUG(SDL_GetError());
		exit(-1);
	}

	//setting openGL version to 4.2 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	//setting openGL context to core, not compatibility
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//creating window
	m_window = SDL_CreateWindow("Marco_McAlindin_GP3_Coursework", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL);

	//Activate SDL Capture mouse
	SDL_CaptureMouse(SDL_TRUE);

	OpenGlInitialise();
	
	GameInitialise();
}

void Application::OpenGlInitialise()
{
	//creating context (our opengl statemachine in which all our GL calls will refer to)
	m_glContext = SDL_GL_CreateContext(m_window);


	SDL_GL_SetSwapInterval(1);

	//initialsing glew (do this after establishing context!)
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
		exit(-1);
	}

	//Smooth shading
	GL_ATTEMPT(glShadeModel(GL_SMOOTH));

	//enable depth testing
	GL_ATTEMPT(glEnable(GL_DEPTH_TEST));

	//set less or equal func for depth testing
	GL_ATTEMPT(glDepthFunc(GL_LEQUAL));

	//enabling blending
	glEnable(GL_BLEND);
	GL_ATTEMPT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//turn on back face culling
	GL_ATTEMPT(glEnable(GL_CULL_FACE));
	GL_ATTEMPT(glCullFace(GL_BACK));

	//Disable Face culling
	glDisable(GL_CULL_FACE);

	
}


void Application::GameInitialise()
{

	///*ADD SHADERS TO RESOURCES FOR APPLICATION
	//* ----------------------------------------*/

	////Shader for 2D Textures
	//Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(ASSET_PATH + "Shaders/Texture.vs", ASSET_PATH + "Shaders/Texture.fs"), "sprite");

	////Shaders for model with Directional Light Applied
	//Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(ASSET_PATH + "Shaders/lighting.vs", ASSET_PATH + "Shaders/lighting.fs"), "basic_lighting");
	//
	////Skybox shader
	//Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(ASSET_PATH + "Shaders/skyboxShader.vert", ASSET_PATH + "Shaders/skyboxShader.frag"), "skybox");

	////Shaders for model with Directional Light Applied
	//Resources::GetInstance()->AddShader(std::make_shared<ShaderProgram>(ASSET_PATH + "Shaders/model_animation.vs", ASSET_PATH + "Shaders/model_animation.fs"), "model_animation");
	//

	///*ADD TEXTURES TO RESOURCES FOR APPLICATION
	//* ----------------------------------------*/

	////BUTTONS

	////Sound On
	//Resources::GetInstance()->AddTexture("Images/Buttons/Sound_On.png");
	////Sound Off
	//Resources::GetInstance()->AddTexture("Images/Buttons/Sound_Off.png");
	////Quit Button
	//Resources::GetInstance()->AddTexture("Images/Buttons/Quit_Button.png");
	////Start Button
	//Resources::GetInstance()->AddTexture("Images/Buttons/Start_Button.png");
	////Main Menu Button 
	//Resources::GetInstance()->AddTexture("Images/Buttons/MainMenu_Button.png");
	////Restart Button
	//Resources::GetInstance()->AddTexture("Images/Buttons/Restart_Button.png");
	////Pause Button
	//Resources::GetInstance()->AddTexture("Images/Buttons/Pause_Button.png");
	////Camera 1 Button
	//Resources::GetInstance()->AddTexture("Images/Buttons/Camera_1.png");
	////Camera 2 Button
	//Resources::GetInstance()->AddTexture("Images/Buttons/Camera_3.png");




	////BACKGROUND
	//
	////Main Menu Background
	//Resources::GetInstance()->AddTexture("Images/bkg_img.jpg");
	////Main Menu Title
	//Resources::GetInstance()->AddTexture("Images/Title.png");
	////Game Over BackGround
	//Resources::GetInstance()->AddTexture("Images/Instructions_Screen.png");
	////Game Over Title
	//Resources::GetInstance()->AddTexture("Images/Game_Over.png");
	////Pause Menu 
	//Resources::GetInstance()->AddTexture("Images/Pause_Menu.png");


	////INSTRUCTIONS
	//
	////Camera
	//Resources::GetInstance()->AddTexture("Images/Camera_Instructions.png");
	////Sound
	//Resources::GetInstance()->AddTexture("Images/Sound_Instructions.png");
	////Movement
	//Resources::GetInstance()->AddTexture("Images/Arrows.png");
	//
	////SCORE 

	//Resources::GetInstance()->AddTexture("Images/Circle.png");
	//Resources::GetInstance()->AddTexture("Images/Score_Bar.png");
	//Resources::GetInstance()->AddTexture("Images/Press_C.png");






	///*ADD MODELS TO RESOURCES FOR APPLICATION
	//* ----------------------------------------*/
	//

	//



	//
	////Make shared pointers for application scenes
	//m_mainMenuScene = std::make_shared<MainMenuScene>("Main_Menu", 0);
	//m_instructionsScene = std::make_shared<InstructionsScene>("Instructions_Scene", 1);
	//m_gameScene = std::make_shared<GameScene>("Game_Scene", 2);
	//m_gameOverScene = std::make_shared<GameOverScene>("Game_Over_Scene", 3);

	//
	////Add Scenes to Scene Manager
	//SceneManager::GetInstance()->AddScene(m_mainMenuScene);
	//SceneManager::GetInstance()->AddScene(m_instructionsScene);
	//SceneManager::GetInstance()->AddScene(m_gameScene);
	//SceneManager::GetInstance()->AddScene(m_gameOverScene);

	//
	//

	////Initialise Sound For Application
	//if (soundMgr->initMixer())
	//{
	//	// Load game sounds
	//	soundList = { "theme", "sphere", "walk"  };
	//	soundTypes = { soundType::music, soundType::sfx ,soundType::sfx };
	//	soundsToUse = { ASSET_AUDIO_PATH_Theme + "theme.mp3", ASSET_AUDIO_PATH_SFX + "sphere.wav",ASSET_AUDIO_PATH_SFX + "walk.wav" };
	//	for (unsigned int sounds = 0; sounds < soundList.size(); sounds++)
	//	{
	//		soundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	//	}

	//	// Play the theme on a constant loop
	//	soundMgr->getSnd("theme")->play(-1);
	//}

	////Load First needed scene
	//SceneManager::GetInstance()->LoadScene(0);

	//Release unused resources
	//Resources::GetInstance()->ReleaseUnusedResources();
}

void Application::Loop()
{
	//Set appstate to running
	m_appState = AppState::RUNNING;

	auto prevTicks = std::chrono::high_resolution_clock::now();

	while (m_appState != AppState::QUITTING)
	{
		Input();

		//Calculate application time
		auto currentTicks = std::chrono::high_resolution_clock::now();
		float deltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(currentTicks - prevTicks).count() / 100000;
		m_worldDeltaTime = deltaTime;
		prevTicks = currentTicks;

		////PLACE IN GAME 
		//Physics::GetInstance()->Update(deltaTime);
		//
		////Update and Render functions
		//Update(deltaTime);

		//Render();

		//switch (m_appSoundState)
		//{
		//case ON:

		//	if (!m_sound)
		//	{
		//		soundMgr->getSnd("theme")->play(-1);
		//		
		//		m_sound = true;
		//	}
		//	
		//	break;
		//case OFF:
		//	Mix_HaltMusic();
		//	soundMgr->getSnd("sphere")->Stop();
		//	m_sound = false;
		//	break;
		//}

		//Swap window buffers
		SDL_GL_SwapWindow(m_window);
	}
}

void Application::Quit()
{
	//Quit Physics Engine
	Physics::GetInstance()->Quit();
	
	//Close SDL
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}

void Application::Input()
{
	SceneManager::GetInstance()->Input();
}

void Application::Update(float deltaTime)
{
	if (INPUT->GetKey(SDLK_d)) m_currentGameState = GameState::DEBUG;
	SceneManager::GetInstance()->Update(deltaTime);
	
}

void Application::Render()
{
	/* Clear context */
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SceneManager::GetInstance()->Render();
}


Application::~Application()
{

}

Application* Application::GetInstance()
{
	//Return instance if not null, initialize otherwise
	if (m_application == nullptr)
	{
		m_application = new Application();
	}
	return m_application;
}

void Application::Run()
{
	Initialise();
	Loop();
	Quit();
}


void Application::LoadModels()
{
	//Player
	Resources::GetInstance()->AddModel("Models/Player/Idle_Player.dae");
	Resources::GetInstance()->AddModel("Models/Player/Dying_Player.dae");
	Resources::GetInstance()->AddModel("Models/Player/Crouched_Walking.dae");

	//Mutant
	Resources::GetInstance()->AddModel("Models/Mutant/Mutant_Idle.dae");
	Resources::GetInstance()->AddModel("Models/Mutant/Mutant_Run.dae");
	Resources::GetInstance()->AddModel("Models/Mutant/Mutant_Swiping.dae");
	Resources::GetInstance()->AddModel("Models/Mutant/Mutant_Walking.dae");


	//Orange Enemy
	Resources::GetInstance()->AddModel("Models/Orange/Orange_Idle.dae");
	Resources::GetInstance()->AddModel("Models/Orange/Orange_Run.dae");
	Resources::GetInstance()->AddModel("Models/Orange/Orange_Swiping.dae");
	Resources::GetInstance()->AddModel("Models/Orange/Orange_Walking.dae");

	//PROPS
	Resources::GetInstance()->AddModel("Models/Props/Tree/Tree0.obj");
	Resources::GetInstance()->AddModel("Models/Props/Trunk/TREE_TRUNK_26_10K.dae");
	Resources::GetInstance()->AddModel("Models/Props/Ground/Level.obj");
	Resources::GetInstance()->AddModel("Models/Props/Sphere/Sphere.obj");
}

