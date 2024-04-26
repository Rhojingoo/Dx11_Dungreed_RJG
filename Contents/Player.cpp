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
#include "IceSpear.h"
#include "Player_HpBar.h"
#include "Town_DungeonDoor.h"
#include "PlayerDamage_Screen.h"


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
	Collision->AddPosition({ 0.f,25.f });

	SetRoot(Root);
}

APlayer::~APlayer()
{
	int a = 0;
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

	Player_HpBAR = GetWorld()->SpawnActor<APlayer_HpBar>("AHP_Bar");

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

	Renderer->SetAutoSize(3.f, true);
	
	Renderer->SetOrder(ERenderOrder::Player);	
	Collision->SetScale({ Renderer->GetWorldScale().X / 2, Renderer->GetWorldScale().Y / 2,1.f});
	
	Renderer->ChangeAnimation("Player_Idle");
	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (Hp <= 0.f)
	{
		if (PlayerDie == false)
		{
			State.ChangeState("Player_Die");
			Right_Hand->Destroy();
			return;
		}
	}
	State.Update(_DeltaTime);
	DebugFunction(_DeltaTime);
	FVector PlayerPos = GetActorLocation();
	Right_Hand->SetActorLocation({ PlayerPos });	
	PlayAfterImage(_DeltaTime, PlayerPos);	
	CollisionCheckFunction();	


	if (UEngineInput::IsPress('Z'))
	{
		std::shared_ptr<APlayerDamage_Screen> DamageScreen = GetWorld()->SpawnActor<APlayerDamage_Screen>("Damage_Screen");	
	}
	





}


void APlayer::CollisionCheckFunction()
{
	Collision->CollisionEnter(EColOrder::Boss_IceBullet, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			AIceBullet* IceBullet = dynamic_cast<AIceBullet*>(Actors);
			if (IceBullet != nullptr)
			{
				if (PlayerDie == false)
				{
					std::shared_ptr<APlayerDamage_Screen> DamageScreen = GetWorld()->SpawnActor<APlayerDamage_Screen>("Damage_Screen");
					IceBullet->BombBullet();
					float Damage = IceBullet->Getdamage();
					Hp -= Damage;
					float ratio = Hp / MaxHp;
					Player_HpBAR->SetRatio(ratio);
				}
				return;
			}
		}
	);

	Collision->CollisionEnter(EColOrder::Boss_Icicle_Bullet, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			AIcicle_Bullet* IceBullet = dynamic_cast<AIcicle_Bullet*>(Actors);
			if (IceBullet != nullptr)
			{
				if (PlayerDie == false)
				{
					std::shared_ptr<APlayerDamage_Screen> DamageScreen = GetWorld()->SpawnActor<APlayerDamage_Screen>("Damage_Screen");
					IceBullet->BombBullet();
					float Damage = IceBullet->Getdamage();
					Hp -= Damage;
					float ratio = Hp / MaxHp;
					Player_HpBAR->SetRatio(ratio);
				}				
				return;
			}
		}
	);

	Collision->CollisionEnter(EColOrder::Boss_IceSpear, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			AIceSpear* IceSpear = dynamic_cast<AIceSpear*>(Actors);
			if (IceSpear != nullptr)
			{
				if (PlayerDie == false)
				{
					std::shared_ptr<APlayerDamage_Screen> DamageScreen = GetWorld()->SpawnActor<APlayerDamage_Screen>("Damage_Screen");
					float Damage = IceSpear->Getdamage();
					Hp -= Damage;
					float ratio = Hp / MaxHp;
					Player_HpBAR->SetRatio(ratio);
				}
				return;
			}
		}
	);


	Collision->CollisionEnter(EColOrder::Door, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			ATown_DungeonDoor* Town = dynamic_cast<ATown_DungeonDoor*>(Actors);
			if (Town != nullptr)
			{
				Town->Dungeon_Enter();
				int a = 0;
				return;
			}
		}
	);
}
