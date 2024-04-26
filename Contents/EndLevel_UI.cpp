#include "PreCompile.h"
#include "EndLevel_UI.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>



AEndLevel_UI::AEndLevel_UI()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	LogoRenderer->SetupAttachment(Root);
	LogoRenderer->AddPosition({ 0.f,150.f });
	

	//GameEnd_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//GameEnd_Renderer->SetupAttachment(Root);
	//GameEnd_Renderer->AddPosition({ 0.f,-150.f });

	//GameEnd_Collision = CreateDefaultSubObject<UCollision>("Collision");
	//GameEnd_Collision->SetupAttachment(GameEnd_Renderer);
	//GameEnd_Collision->SetCollisionGroup(EColOrder::GameEnd_UI);
	//GameEnd_Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

AEndLevel_UI::~AEndLevel_UI()
{
}


void AEndLevel_UI::BeginPlay()
{
	Super::BeginPlay();

	LogoRenderer->SetSprite("ExplorationFailure.png");
	//LogoRenderer->SetSprite("ExplorationSuccess.png");
	LogoRenderer->SetAutoSize(3.f, true);
	LogoRenderer->SetOrder(ERenderOrder::ForeGround);

	//GameEnd_Renderer->SetSprite("ExitOn_Kor.png");
	//GameEnd_Renderer->SetSprite("ExitOff_Kor.png");
	//GameEnd_Renderer->SetAutoSize(4.5f, true);
	//GameEnd_Renderer->SetOrder(ERenderOrder::ForeGround);
}

void AEndLevel_UI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}



void AEndLevel_UI::StartUIOn()
{

}

void AEndLevel_UI::StartUIOff()
{
}

void AEndLevel_UI::EndUIOn()
{
}

void AEndLevel_UI::EndUIOff()
{
}

