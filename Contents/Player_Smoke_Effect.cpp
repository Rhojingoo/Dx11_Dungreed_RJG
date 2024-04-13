#include "PreCompile.h"
#include "Player_Attack_Effect.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsHelper.h"
#include "Player_Smoke_Effect.h"


APlayer_Smoke_Effect::APlayer_Smoke_Effect()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderers");
	SetRoot(Renderer);
}

APlayer_Smoke_Effect::~APlayer_Smoke_Effect()
{
}

void APlayer_Smoke_Effect::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetPivot(EPivot::BOT);
	Renderer->CreateAnimation("Run_Smoke", "Run_Smoke.png", 0.1f, false);
	Renderer->CreateAnimation("Dash_Smoke", "Dash_Smoke.png", 0.1f, false);
	Renderer->SetAutoSize(1.f, true);
	Renderer->SetOrder(ERenderOrder::Effect_Back);
	Renderer->ChangeAnimation("Run_Smoke");
}

void APlayer_Smoke_Effect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (Smoke_Switch == true)
	{
		//if (Dash_SmokeOn == true)
		//{
		//	Renderer->ChangeAnimation("Dash_Smoke");
		//	Dash_SmokeOn = false;
		//}
		//if (Run_SmokeON == true)
		//{
		//	Renderer->ChangeAnimation("Run_Smoke");
		//	Run_SmokeON = false;
		//}	
	}
	if (Dash_SmokeOn == true)
	{
		Renderer->ChangeAnimation("Dash_Smoke");
		Dash_SmokeOn = false;
	}
	if (Run_SmokeON == true)
	{
		Renderer->ChangeAnimation("Run_Smoke");
		Run_SmokeON = false;
	}
}
