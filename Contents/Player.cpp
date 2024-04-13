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
	SetRoot(Renderer);
	//Renderer->SetScale(FVector(300.0f, 300.0f, 300.0f));


	//ChildRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	//ChildRenderer->SetupAttachment(Root);
	//ChildRenderer->SetPivot(EPivot::BOT);
	//ChildRenderer->SetSprite("DemonSword.png");
	//ChildRenderer->SetScale(FVector(48.0f, 180.0f, 100.0f));
	//ChildRenderer->AddPosition({ 30.0f, 110.0f, 0.0f });

	//SetRoot(Root);
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

	//Left_Hand = GetWorld()->SpawnActor<APlayer_Hand>("L_Hand");
	//Left_Hand->SetActorLocation({ 640.0f, -360.0f, 200.0f });	

	//Sowrd = GetWorld()->SpawnActor<ALegendSowrd>("Sowrd");
	//Sowrd->SetActorLocation({ 640.0f, -360.0f, 200.0f });


	//SetActorScale3D(FVector(32.0f, 32.0f, 100.0f));
	
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
	Renderer->SetOrder(7);
	
	
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
	//ChildRenderer->SetRotationDeg(SwordRotation);

	//Sowrd->AddActorRotation(SwordRotation);
	//Sowrd->GetActorTransform().AddRotationDeg(SwordRotation);
	//Sowrd->GetActorTransform().SetRotationDeg(SwordRotation);
	//Sowrd->SetActorRotation(SwordRotation);
	//Left_Hand->SetActorLocation({ PlayerPos.X - 20,PlayerPos.Y - 25, PlayerPos.Z - 1 });
	int a = 0;
	//Left_Hand->SetActorLocation();
}