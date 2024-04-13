#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <cmath>
#include <EngineCore/DefaultSceneComponent.h>
#include "Player_Hand.h"
#include "Target.h"
#include "Player_Smoke_Effect.h"

APlayer::APlayer()
{
	//UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	//Renderer->SetupAttachment(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetPivot(EPivot::BOT);


	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Renderer);
	//Collision->SetScale(FVector(1000.f, 0.5f, 1.0f));
	//Collision->AddPosition({ 0.0f, 0.f, 0.0f });

	//ChildRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//ChildRenderer->SetupAttachment(Renderer);
	//ChildRenderer->SetScale(FVector(0.5f, 0.5f, 1.0f));
	//ChildRenderer->AddPosition({ 0.0f, 0.25f, 0.0f });
	//ChildRenderer->SetPivot(EPivot::BOT);

	SetRoot(Renderer);
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	Cursor = GetWorld()->SpawnActor<ATarget>("Target");
	Cursor->SetActorLocation({ 640.0f, -360.0f, 200.0f });

	Right_Hand = GetWorld()->SpawnActor<APlayer_Hand>("R_Hand");
	Right_Hand->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	Right_Hand->SetTarget(Cursor);

	Smoke_Effect = GetWorld()->SpawnActor<APlayer_Smoke_Effect>("Smoke");
	Smoke_Effect->SetActorLocation({0.0f, 0.0f, 200.0f });	
	Renderer->CreateAnimation("Player_Idle", "Player_Idle",0.1f);
	Renderer->CreateAnimation("Player_Jump", "Player_Jump", 0.1f);
	Renderer->CreateAnimation("Player_Run", "Player_Run", 0.1f);
	Renderer->CreateAnimation("Player_Die", "Player_Die", 0.1f);

	Renderer->CreateAnimation("Boss_Attack", "Boss_Idle", 0.1f);
	Renderer->CreateAnimation("Boss_Die", "Boss_Die", 0.1f);
	Renderer->CreateAnimation("Boss_Enter", "Boss_Enter", 0.1f);
	Renderer->CreateAnimation("Boss_Exit", "Boss_Exit", 0.1f);
	Renderer->CreateAnimation("Boss_Idle", "Boss_Idle", 0.1f);

	//Renderer->SetSprite("CuttingTest.png", 11);
	Renderer->SetAutoSize(3.f, true);
	Renderer->SetOrder(ERenderOrder::Player);	
	//Collision->SetOrder(ERenderOrder::Collision);
	Renderer->ChangeAnimation("Player_Idle");
	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);
	DebugFunction();
	FVector PlayerPos = GetActorLocation();
	Right_Hand->SetActorLocation({ PlayerPos });


	
}