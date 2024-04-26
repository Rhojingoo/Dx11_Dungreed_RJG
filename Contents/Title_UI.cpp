#include "PreCompile.h"
#include "Title_UI.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ATitle_UI::ATitle_UI()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	GameStart_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");	
	GameStart_Renderer->SetupAttachment(Root);
	GameStart_Renderer->AddPosition({ 0.f,-50.f });

	GameStart_Collision = CreateDefaultSubObject<UCollision>("Collision");
	GameStart_Collision->SetupAttachment(GameStart_Renderer);
	GameStart_Collision->SetCollisionGroup(EColOrder::GameStart_UI);
	GameStart_Collision->SetCollisionType(ECollisionType::Rect);


	GameEnd_Renderer =  CreateDefaultSubObject<USpriteRenderer>("Renderer");
	GameEnd_Renderer->SetupAttachment(Root);
	GameEnd_Renderer->AddPosition({ 0.f,-150.f });

	GameEnd_Collision = CreateDefaultSubObject<UCollision>("Collision");
	GameEnd_Collision->SetupAttachment(GameEnd_Renderer);
	GameEnd_Collision->SetCollisionGroup(EColOrder::GameEnd_UI);
	GameEnd_Collision->SetCollisionType(ECollisionType::Rect);


	SetRoot(Root);
}

ATitle_UI::~ATitle_UI()
{
}

void ATitle_UI::BeginPlay()
{
	Super::BeginPlay();

	//GameStart_Renderer->SetSprite("PlayOn_Kor.png");
	GameStart_Renderer->SetSprite("PlayOff_Kor.png");
	GameStart_Renderer->SetAutoSize(4.5f, true);
	GameStart_Renderer->SetOrder(ERenderOrder::ForeGround);

	//GameEnd_Renderer->SetSprite("ExitOn_Kor.png");
	GameEnd_Renderer->SetSprite("ExitOff_Kor.png");
	GameEnd_Renderer->SetAutoSize(4.5f, true);
	GameEnd_Renderer->SetOrder(ERenderOrder::ForeGround);
}

void ATitle_UI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATitle_UI::StartUIOn()
{
	GameStart_Renderer->SetSprite("PlayOn_Kor.png");
}

void ATitle_UI::StartUIOff()
{
	GameStart_Renderer->SetSprite("PlayOff_Kor.png");
}

void ATitle_UI::EndUIOn()
{
	GameEnd_Renderer->SetSprite("ExitOn_Kor.png");
}

void ATitle_UI::EndUIOff()
{
	GameEnd_Renderer->SetSprite("ExitOff_Kor.png");
}
