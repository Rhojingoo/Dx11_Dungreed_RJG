#include "PreCompile.h"
#include "MonsterBullet.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

AMonsterBullet::AMonsterBullet()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	//Renderer->SetPivot(EPivot::BOT);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionGroup(EColOrder::Monter_Bullet);
	Collision->SetCollisionType(ECollisionType::RotRect);

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	EffectRenderer->SetupAttachment(Root);
	SetRoot(Root);
}

AMonsterBullet::~AMonsterBullet()
{
}

float AMonsterBullet::Getdamage()
{
	Damage = UContentsHelper::Random(MinDamage, MaxDamage);
	return Damage;
}

void AMonsterBullet::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetAutoSize(4.f, true);
	Renderer->CreateAnimation("IceBat_Bullet", "IceBat_Bullet", 0.1f, true);
	Renderer->CreateAnimation("RangeBallBullet", "RangeBallBullet", 0.1f, true);
	Renderer->SetOrder(ERenderOrder::Monster_Bullet);
	Renderer->ChangeAnimation("RangeBallBullet");

	EffectRenderer->CreateAnimation("RangeBallBullet_Destroy", "RangeBallBullet_Destroy", 0.1f, false);
	EffectRenderer->SetOrder(ERenderOrder::Effect_Front);
	EffectRenderer->SetAutoSize(4.f, true);
}

void AMonsterBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Collision->SetPosition({ Renderer->GetWorldPosition() * 0.0001f });

	StateUpdate(_DeltaTime);
}

void AMonsterBullet::AttackStart()
{
	DestroyTime = 0.f;
	
}

void AMonsterBullet::Attack(float _DeltaTime)
{
	if (TargetSwitch == true)
	{
		if (OtherBulletFire == false)
		{
			FVector Target = -TargetPos * Speed;

			AddActorLocation(Target);
			float CursorAngleRad = std::atan2(TargetPos.Y, TargetPos.X);
			CursorAngleRad = CursorAngleRad * UEngineMath::RToD;
			SetActorRotation(FVector(0.0f, 0.0f, CursorAngleRad + 90));
		}
		else
		{
			FVector Target = -TargetPos * Speed * _DeltaTime;
			AddActorLocation(-Target);
			float CursorAngleRad = std::atan2(TargetPos.Y, TargetPos.X);
			CursorAngleRad = CursorAngleRad * UEngineMath::RToD;
			SetActorRotation(FVector(0.0f, 0.0f, CursorAngleRad + 90));

			DestroyTime += _DeltaTime;
			if (DestroyTime > 5.f)
			{
				Destroy();
			}
		}
	}
}

void AMonsterBullet::ColEnterStart()
{
	Renderer->SetActive(false);
	EffectRenderer->ChangeAnimation("RangeBallBullet_Destroy");
}

void AMonsterBullet::ColEnter(float _DeltaTime)
{
	if (EffectRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

void AMonsterBullet::ChangeState(BulletState _Set)
{
	if (_Set != Bullet_State)
	{
		switch (_Set)
		{
		case BulletState::Attack:
			AttackStart();
			break;
		case BulletState::Collision:
			ColEnterStart();
			break;
		case BulletState::End:
			break;
		default:
			break;
		}
	}
	Bullet_State = _Set;
}

void AMonsterBullet::StateUpdate(float _DeltaTime)
{
	switch (Bullet_State)
	{
	case BulletState::Attack:
		Attack(_DeltaTime);
		break;
	case BulletState::Collision:
		ColEnter(_DeltaTime);
		break;
	case BulletState::End:
		break;
	default:
		break;
	}
}
