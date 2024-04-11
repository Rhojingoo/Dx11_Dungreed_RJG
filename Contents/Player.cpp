#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	Cursor = GetWorld()->SpawnActor<ATarget>("Target");
	Cursor->SetActorLocation({ 640.0f, -360.0f, 200.0f });


	SetActorScale3D(FVector(320.0f, 320.0f, 100.0f));
	
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
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);
	DebugFunction();
}