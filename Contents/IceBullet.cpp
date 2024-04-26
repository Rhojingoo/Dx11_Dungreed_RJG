#include "PreCompile.h"
#include "IceBullet.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteInstancingRender.h>

AIceBullet::AIceBullet()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	EffectRenderer->SetupAttachment(Root);
	EffectRenderer->SetPivot(EPivot::BOT);


	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionGroup(EColOrder::Boss_IceBullet);
	Collision->SetCollisionType(ECollisionType::RotRect);

	SetRoot(Root);
}

AIceBullet::~AIceBullet()
{
}

void AIceBullet::AttackStart()
{
	DestroyTime = 0.f;
}



float AIceBullet::Getdamage()
{
	Damage = UContentsHelper::Random(MinDamage, MaxDamage);
	return Damage;
}

void AIceBullet::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetAutoSize(4.0f, true);

	Renderer->CreateAnimation("IceBullet", "IceBullet", 0.1f, false);
	Renderer->ChangeAnimation("IceBullet");
	Renderer->SetOrder(ERenderOrder::Boss_IceBullet);

	EffectRenderer->CreateAnimation("IceBulletEfferct", "IceBulletEfferct", 0.5f, false);
	EffectRenderer->SetOrder(ERenderOrder::Boss_IceBullet_Effect);
	EffectRenderer->SetAutoSize(4.f, true);
	
	//GetWorld()->InstancingOn<USpriteInstancingRender>(ERenderOrder::Boss_IceBullet);
	//Collision->SetScale({ Renderer->GetWorldScale().X / 2, Renderer->GetWorldScale().Y / 2, 10.f });
	//aaaaaCollision->AddPosition({ 0.85f, 0.0f });
}

void AIceBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Collision->SetPosition({ Renderer->GetWorldPosition() * 0.0001f });

	{
		std::string Msg = std::format("BulletCollisionPos : {}\n", Collision->GetWorldPosition().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	StateUpdate(_DeltaTime);
}


void AIceBullet::Attack(float _DeltaTime)
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
			FVector Target = -TargetPos * Speed* _DeltaTime;
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

void AIceBullet::ColEnterStart()
{
	Renderer->SetActive(false);
	EffectRenderer->ChangeAnimation("IceBulletEfferct");
	//Renderer->ChangeAnimation("IceBulletEfferct");
}

void AIceBullet::ColEnter(float _DeltaTime)
{
	if (EffectRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}

	//if (Renderer->IsCurAnimationEnd())
	//{
	//	Destroy();
	//}
}

void AIceBullet::ChangeState(IceBulletState _Set)
{
	if (_Set != IceState)
	{
		switch (_Set)
		{
		case IceBulletState::Attack:
			AttackStart();
			break;
		case IceBulletState::Collision:
			ColEnterStart();
			break;
		case IceBulletState::End:
			break;
		default:
			break;
		}
	}
	IceState = _Set;
}

void AIceBullet::StateUpdate(float _DeltaTime)
{
	switch (IceState)
	{
	case IceBulletState::Attack:
		Attack(_DeltaTime);
		break;
	case IceBulletState::Collision:
		ColEnter(_DeltaTime);
		break;
	case IceBulletState::End:
		break;
	default:
		break;
	}	
}
