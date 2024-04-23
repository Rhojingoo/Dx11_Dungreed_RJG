#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <cmath>
#include <EngineCore/DefaultSceneComponent.h>
#include "Player_Hand.h"
#include "Target.h"
#include "Player_Smoke_Effect.h"
#include "Player_AfterImage.h"
#include "IceBullet.h"
#include "Icicle_Bullet.h"

APlayer::APlayer()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetPivot(EPivot::BOT);
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(EColOrder::Player);
	Collision->SetCollisionType(ECollisionType::RotRect);
	


	SetRoot(Root);
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

	for (int a = 0; a < 10; a++)
	{
		After_Image[a] = GetWorld()->SpawnActor<APlayer_AfterImage>("AfterImage");
	}
	

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
	Collision->SetScale({ Renderer->GetWorldScale().X / 2, Renderer->GetWorldScale().Y / 2,1.f});
	Collision->AddPosition({0.f, 0.25f });
	
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
	PlayAfterImage(_DeltaTime, PlayerPos);	


	Collision->CollisionEnter(EColOrder::Boss_IceBullet, [=](std::shared_ptr<UCollision> _Collison)
		{		
			AActor* Actors =_Collison->GetActor();
			AIceBullet* IceBullet = dynamic_cast<AIceBullet*>(Actors);
			if (IceBullet != nullptr)
			{
				IceBullet->BombBullet();
				return;
			}
			int a = 0;
		}
	);

	//Collision->CollisionExit(EColOrder::Boss_IceBullet, [=](std::shared_ptr<UCollision> _Collison)
	//	{
	//		int a = 0;
	//	}
	//);

	//Collision->CollisionStay(EColOrder::Boss_IceBullet, [=](std::shared_ptr<UCollision> _Collison)
	//	{
	//		int a = 0;
	//	}
	//);
}


