#include "GameScene.h"
#include "Components.h"
#include "Input.h"
#include "pch.h"
#include "PauseButton.h"
#include "QuitButton.h"
#include "MainMenuButton.h"
#include "CameraButton.h"
#include "Skybox.h"
#include "BoxShape.h"
#include "EnemyComponent.h"
#include "ThirdPersonCamera.h"
#include "LevelViewCamera.h"
#include "CharacterController.h"
#include <random>

static DirectionalLight* m_directionalLight = new DirectionalLight();


GameScene::GameScene()
{

}




void GameScene::OnCreate()
{
	Scene::OnCreate();

	//skybox = new Skybox(Resources::GetInstance()->GetShader("skybox"));

	m_orbPositions[0] =  glm::vec3(10.0f, 1.0f,10.0f) ;
	m_orbPositions[1] =  glm::vec3(-10.0f, 1.0f,-10.0f);
	m_orbPositions[2] =  glm::vec3(-5.0f, 1.0f,10.0f);
	m_orbPositions[3] =  glm::vec3(2.0f, 1.0f,10.0f) ;
	

	m_playerScore = 0;
	/*=============================================================================
						CREATE UI ENTITIES
	=============================================================================*/


	//SETUP FOG 
	m_fog = Fog::GetInstance();
	m_fog->SetColor(glm::vec3(0.0001f,.0001f,.0001f));
	m_fog->SetHeight(0.25f);
	m_fog->SetMaxDist(8.0f);
	m_fog->SetMinDist(1.0f);

	/*------------------------------------------------
						PLAYER ENTITY                
	-------------------------------------------------*/

	//Create entity, insert in entities map
	Entity* tempEntity = new Entity("Player");
	m_entities.insert({tempEntity->m_name, tempEntity});

	//Initialise animator, add all necessery animations
	Animator* anim = new Animator(std::make_shared<Animation>(ASSET_PATH + "Models/Player/Idle_Player.dae", Resources::GetInstance()->GetModel("Models/Player/Idle_Player.dae")), Resources::GetInstance()->GetShader("model_animation"), Resources::GetInstance()->GetModel("Models/Player/Idle_Player.dae"));
	anim->AddAnimation(std::make_shared<Animation>(ASSET_PATH + "Models/Player/Dying_Player.dae", Resources::GetInstance()->GetModel("Models/Player/Dying_Player.dae")), "Die");
	anim->AddAnimation(std::make_shared<Animation>(ASSET_PATH + "Models/Player/Crouched_Walking.dae", Resources::GetInstance()->GetModel("Models/Player/Crouched_Walking.dae")), "Walk");
	tempEntity->AddComponent(anim);
	
	//Create player component and add to entity
	PlayerComponent* pc = new PlayerComponent();
	pc->SetPlayerSpeed(.25f);
	tempEntity->AddComponent(pc);

	
	CharacterController* cc = new CharacterController();
	tempEntity->AddComponent(cc);

	
	//Rigidbody component
	/*RigidBody* rb = new RigidBody();
	tempEntity->AddComponent(rb);
	rb->Init(new BoxShape(glm::vec3(1.0f,3.0f,1.0f)));
	rb->Get()->setMassProps(0.0f, btVector3(0.0f, 0.0f, 0.0f));*/

	//Set transform values
	tempEntity->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	m_player = tempEntity;

	//----------------------------------------------------------


	/*---------------------------------------------------------
						   ENEMY ENTITY
	----------------------------------------------------------*/
	//Create entity, insert in entities map
	tempEntity = new Entity("Enemy_Mutant");
	m_entities.insert({ tempEntity->m_name, tempEntity });

	//Initialise animator, add all necessery animations
	anim = new Animator(std::make_shared<Animation>(ASSET_PATH + "Models/Mutant/Mutant_Idle.dae", Resources::GetInstance()->GetModel("Models/Mutant/Mutant_Idle.dae")), Resources::GetInstance()->GetShader("model_animation"), Resources::GetInstance()->GetModel("Models/Mutant/Mutant_Idle.dae"));
	anim->AddAnimation(std::make_shared<Animation>(ASSET_PATH + "Models/Mutant/Mutant_Run.dae", Resources::GetInstance()->GetModel("Models/Mutant/Mutant_Run.dae")), "Run");
	anim->AddAnimation(std::make_shared<Animation>(ASSET_PATH + "Models/Mutant/Mutant_Swiping.dae", Resources::GetInstance()->GetModel("Models/Mutant/Mutant_Swiping.dae")), "Attack");
	anim->AddAnimation(std::make_shared<Animation>(ASSET_PATH + "Models/Mutant/Mutant_Walking.dae", Resources::GetInstance()->GetModel("Models/Mutant/Mutant_Walking.dae")), "Walk");
	tempEntity->AddComponent(anim);

	//Rigidbody component
	/*rb = new RigidBody();
	tempEntity->AddComponent(rb);
	rb->Init(new BoxShape(glm::vec3(1.0f, 3.0f, 1.0f)));
	rb->Get()->setMassProps(0.0f, btVector3(0.0f, 0.0f, 0.0f));*/

	//Enemy Component
	EnemyComponent* ec = new EnemyComponent();
	tempEntity->AddComponent(ec);

	//Set transform values
	tempEntity->GetTransform()->SetPosition(glm::vec3(4.0f, 0.0f, 5.0f));
	
	//Create entity, insert in entities map
	tempEntity = new Entity("Enemy_Orange");
	m_entities.insert({ tempEntity->m_name, tempEntity });

	//Initialise animator, add all necessery animations
	anim = new Animator(std::make_shared<Animation>(ASSET_PATH + "Models/Orange/Orange_Idle.dae", Resources::GetInstance()->GetModel("Models/Orange/Orange_Idle.dae")), Resources::GetInstance()->GetShader("model_animation"), Resources::GetInstance()->GetModel("Models/Orange/Orange_Idle.dae"));
	anim->AddAnimation(std::make_shared<Animation>(ASSET_PATH + "Models/Orange/Orange_Run.dae", Resources::GetInstance()->GetModel("Models/Orange/Orange_Run.dae")), "Run");
	tempEntity->AddComponent(anim);

	//Rigidbody component
	/*rb = new RigidBody();
	tempEntity->AddComponent(rb);
	rb->Init(new BoxShape(glm::vec3(1.0f, 3.0f, 1.0f)));
	rb->Get()->setMassProps(0.0f, btVector3(0.0f, 0.0f, 0.0f));*/

	//Enemy Component
	ec = new EnemyComponent();
	tempEntity->AddComponent(ec);

	//Set transform values
	tempEntity->GetTransform()->SetPosition(glm::vec3(-4.0f, 0.0f, -5.0f));

	

	tempEntity = new Entity("Trunk");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Trunk/TREE_TRUNK_26_10K.dae"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetScale(glm::vec3(.5f, .5f, .5f));
	tempEntity->GetTransform()->SetPosition(glm::vec3(8.0f, -0.2f, 7.5f));
	tempEntity->GetTransform()->RotateEulerAxis(90.0f, glm::vec3(1.0f,0.0f,0.0f));
	//rb = new RigidBody();
	//tempEntity->AddComponent(rb);
	/*rb->Init(new BoxShape(glm::vec3(1.0f, 3.0f, 1.0f)));
	rb->Get()->setMassProps(0.0f, btVector3(0.0f, 0.0f, 0.0f));*/

	tempEntity = new Entity("Trunk1");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Trunk/TREE_TRUNK_26_10K.dae"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetScale(glm::vec3(.5f, .5f, .5f));
	tempEntity->GetTransform()->SetPosition(glm::vec3(9.0f, -0.2f, -11.0f));
	tempEntity->GetTransform()->RotateEulerAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	 //rb = new RigidBody();
	//tempEntity->AddComponent(rb);
	/*rb->Init(new BoxShape(glm::vec3(1.0f, 3.0f, 1.0f)));
	rb->Get()->setMassProps(0.0f, btVector3(0.0f, 0.0f, 0.0f));*/

	tempEntity = new Entity("Trunk2");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Trunk/TREE_TRUNK_26_10K.dae"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetScale(glm::vec3(.5f, .5f, .5f));
	tempEntity->GetTransform()->SetPosition(glm::vec3(-10.0f, -0.2f, -7.0f));
	tempEntity->GetTransform()->RotateEulerAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	/* rb = new RigidBody();
	tempEntity->AddComponent(rb);
	rb->Init(new BoxShape(glm::vec3(1.0f, 3.0f, 1.0f)));
	rb->Get()->setMassProps(0.0f, btVector3(0.0f, 0.0f, 0.0f));*/


	tempEntity = new Entity("Trunk3");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Trunk/TREE_TRUNK_26_10K.dae"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetScale(glm::vec3(.5f, .5f, .5f));
	tempEntity->GetTransform()->SetPosition(glm::vec3(-11.0f, -0.25f, 11.0f));
	tempEntity->GetTransform()->RotateEulerAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	/* rb = new RigidBody();
	tempEntity->AddComponent(rb);
	rb->Init(new BoxShape(glm::vec3(1.0f, 3.0f, 1.0f)));
	rb->Get()->setMassProps(0.0f, btVector3(0.0f, 0.0f, 0.0f));*/

	tempEntity = new Entity("Trunk4");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Trunk/TREE_TRUNK_26_10K.dae"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetScale(glm::vec3(.5f, .5f, .5f));
	tempEntity->GetTransform()->SetPosition(glm::vec3(0.0f, -0.25f, -2.0f));
	tempEntity->GetTransform()->RotateEulerAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	/* rb = new RigidBody();
	tempEntity->AddComponent(rb);
	rb->Init(new BoxShape(glm::vec3(1.0f, 3.0f, 1.0f)));
	rb->Get()->setMassProps(0.0f, btVector3(0.0f, 0.0f, 0.0f));*/

	tempEntity = new Entity("Trunk5");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Trunk/TREE_TRUNK_26_10K.dae"), Resources::GetInstance()->GetShader("basic_lighting")));
	/* rb = new RigidBody();
	tempEntity->AddComponent(rb);
	rb->Init(new BoxShape(glm::vec3(1.0f, 3.0f, 1.0f)));
	rb->Get()->setMassProps(0.0f, btVector3(0.0f, 0.0f, 0.0f));*/
	tempEntity->GetTransform()->SetScale(glm::vec3(.5f, .5f, .5f));
	tempEntity->GetTransform()->SetPosition(glm::vec3(-3.0f, -0.25f, 4.0f));
	tempEntity->GetTransform()->RotateEulerAxis(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));



	tempEntity = new Entity("Ground");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Ground/Level.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetScale(glm::vec3(.2f, .2f, .2f));
	tempEntity->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	/*rb = new RigidBody();
	tempEntity->AddComponent(rb);
	rb->Init(new BoxShape(glm::vec3(30.0,0.3f,30.0f)));
	rb->Get()->setMassProps(0.0f,btVector3(0.0f,0.0f,0.0f));*/

	tempEntity = new Entity("Orb");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	m_orbSphere = tempEntity;
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Sphere/Sphere.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetScale(glm::vec3(.2f, 0.2f, 0.2f));
	//tempEntity = new Entity("Enemy");
	//m_entities.insert({ tempEntity->m_name, tempEntity });
	//tempEntity->AddComponent(new Animator(std::make_shared<Animation>(ASSET_PATH + "Models/Idle_Enemy_Orange.dae", Resources::GetInstance()->GetModel("Models/Idle_Enemy_Orange.dae")), Resources::GetInstance()->GetShader("model_animation"), Resources::GetInstance()->GetModel("Models/Idle_Enemy_Orange.dae")));
	tempEntity->GetTransform()->SetPosition(glm::vec3(2.0f,0.5f,0.0f));
	

	SpawnTrees();

	tempEntity = new Entity("Pause_Button");
	tempEntity->AddComponent(new PauseButton(Resources::GetInstance()->GetTexture("Images/Buttons/Pause_Button.png"), glm::vec3(5.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(100.0f, 100.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Pause_Menu");
	tempEntity->AddComponent(new Sprite(Resources::GetInstance()->GetTexture("Images/Pause_Menu.png"),glm::vec3(300.0f,70.0f,0.0f), glm::vec3(1.0f, 1.0f, 1.0f), .65f, glm::vec2(450.0f, 600.0f)));
	tempEntity->AddComponent(new QuitButton(Resources::GetInstance()->GetTexture("Images/Buttons/Quit_Button.png"), glm::vec3(380.0f, 250.0f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), 0.75f, glm::vec2(300.0f, 200.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->isActive = false;

	tempEntity = new Entity("Camera_1_Button");
	tempEntity->AddComponent(new CameraButton1(Resources::GetInstance()->GetTexture("Images/Buttons/Camera_3.png"), glm::vec3(95.0f, 610.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(80.0f, 80.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("Camera_2_Button");
	tempEntity->AddComponent(new CameraButton2(Resources::GetInstance()->GetTexture("Images/Buttons/Camera_1.png"), glm::vec3(10.0f, 610.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(80.0f, 80.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });

	tempEntity = new Entity("skybox");
	Skybox* sb = new Skybox(Resources::GetInstance()->GetShader("skybox"));
	tempEntity->AddComponent(sb);
	m_entities.insert({ tempEntity->m_name, tempEntity });


	/*tempEntity = new Entity("Score_Bar");
	tempEntity->AddComponent(new Sprite(Resources::GetInstance()->GetTexture("Images/Score_Bar.png"), glm::vec3(960.0f, 460.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(80.0f, 230.0f)));
	tempEntity->AddComponent(new Sprite(Resources::GetInstance()->GetTexture("Images/Circle.png"), glm::vec3(985.0f, 290.0f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(30.0f, 30.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });*/

	tempEntity = new Entity("Press_C");
	tempEntity->AddComponent(new Sprite(Resources::GetInstance()->GetTexture("Images/Press_C.png"), glm::vec3(320.0f, 560.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.f, glm::vec2(500.0f, 70.0f)));
	m_UI_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->isActive = false;

	m_orb = new PointLight();




	tempEntity = new Entity("Camera_Player");
	m_sceneCameras.insert({ tempEntity->m_name, tempEntity });
	tempEntity->GetTransform()->SetPosition(glm::vec3(0.f, 1.6f, -3.3f));
	tempEntity->GetTransform()->RotateEulerAxis(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	CameraComponent* cameraComponent = new CameraComponent();
	tempEntity->AddComponent(cameraComponent);
	cameraComponent->Start(GetEntity("Player")->GetTransform());
	SetCamera(cameraComponent->m_camera);	
	


	tempEntity = new Entity("Camera_2");
	tempEntity->GetTransform()->SetPosition(glm::vec3(0.f, 15.0f, 21.5f));
	tempEntity->GetTransform()->RotateEulerAxis(35.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	LevelViewCamera* levelCamera = new LevelViewCamera();
	tempEntity->AddComponent(levelCamera);
	levelCamera->Start();
	m_sceneCameras.insert({tempEntity->m_name, tempEntity});
	




}

void GameScene::OnDestroy()
{

}

void GameScene::OnActivate()
{
	Scene::OnActivate();
}

void GameScene::OnDeactivate()
{

}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

}

void GameScene::Render()
{
	
	Scene::Render();
																																																																																																																																																																																																																																																				 

	m_activeCamera->Recalculate();
}

void GameScene::Input()
{
	Scene::Input();
}

void GameScene::SpawnTrees()
{
	
	
	Entity* tempEntity = new Entity("Tree");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Tree/Tree0.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetPosition(glm::vec3( 25.0f, 0.0f, 25.0f));
	tempEntity->GetTransform()->SetScale(glm::vec3(1.0f,1.0f, 1.0f));


	tempEntity = new Entity("Tree1");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Tree/Tree0.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetPosition(glm::vec3(0, 0.0f, 25.0f));
	tempEntity->GetTransform()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	

	tempEntity = new Entity("Tree2");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Tree/Tree0.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 35.0f));
	tempEntity->GetTransform()->SetScale(glm::vec3(0.4f, 0.4f, 0.4f));

	tempEntity = new Entity("Tree3");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Tree/Tree0.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetPosition(glm::vec3(23.0f, 0.0f, 35.0f));
	tempEntity->GetTransform()->SetScale(glm::vec3(0.7f, 0.7f, 0.7f));



	tempEntity = new Entity("Tree4");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Tree/Tree0.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetPosition(glm::vec3(10.0f, 0.0f, 30.0f));
	tempEntity->GetTransform()->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));


	tempEntity = new Entity("Tree5");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Tree/Tree0.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetPosition(glm::vec3(0.0f, 0.0f, 30.0f));
	tempEntity->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

	tempEntity = new Entity("Tree6");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Tree/Tree0.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetPosition(glm::vec3(18.0f, 0.0f, 25.0f));
	tempEntity->GetTransform()->SetScale(glm::vec3(0.7f, 0.7f, 0.7f));


	tempEntity = new Entity("Tree7");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Tree/Tree0.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetPosition(glm::vec3(15.0, 0.0f, 49.0f));
	tempEntity->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

	tempEntity = new Entity("Tree8");
	m_entities.insert({ tempEntity->m_name, tempEntity });
	tempEntity->AddComponent(new MeshRenderer(Resources::GetInstance()->GetModel("Models/Props/Tree/Tree0.obj"), Resources::GetInstance()->GetShader("basic_lighting")));
	tempEntity->GetTransform()->SetPosition(glm::vec3(2.0f, 0.0f, 40.0f));
	tempEntity->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));


}

