#include "PreCompile.h"
#include "Player_Attack_Effect.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsHelper.h"
#include "IceBullet.h"
#include "Icicle_Bullet.h"

APlayer_Attack_Effect::APlayer_Attack_Effect()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderers");
	SetRoot(Renderer);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionGroup(EColOrder::Wapon);
	Collision->SetCollisionType(ECollisionType::RotRect);
	//Renderer->SetPivot(EPivot::BOT);
}

APlayer_Attack_Effect::~APlayer_Attack_Effect()
{
}

void APlayer_Attack_Effect::BeginPlay()
{
	Super::BeginPlay();
	//Sword_Swing_Legend
	//Renderer->SetSprite("DemonSword.png");
	Renderer->CreateAnimation("Sword_Swing_Normal", "Sword_Swing_Normal", 0.1f, false);
	Renderer->CreateAnimation("Sword_Swing_Legend", "Sword_Swing_Legend", 0.1f, false);
	Renderer->SetAutoSize(5.f, true);
	Renderer->SetOrder(ERenderOrder::Attack_Effect);
	//Renderer->ChangeAnimation("Sword_Swing_Legend");

	//Collision->SetScale(Renderer->GetLocalScale());
	FVector asd1 = Renderer->GetLocalScale();
	FVector asd = Renderer->GetWorldScale();
	Collision->SetScale(Renderer->GetWorldScale());
	//Collision->AddPosition({ 0.f, 0.25f });
}

void APlayer_Attack_Effect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Collision->SetScale(Renderer->GetWorldScale());
	StateUpdate(_DeltaTime);

	Collision->CollisionEnter(EColOrder::Boss_IceBullet, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			AIceBullet* IceBullet = dynamic_cast<AIceBullet*>(Actors);
			if (IceBullet != nullptr)
			{
				IceBullet->BombBullet();
				return;
			}
		}
	);

	if (Attack == true)
	{
		ChangeState(AttackState::Attack);
	}
}

void APlayer_Attack_Effect::Effect_AttackStart()
{
	Renderer->AnimationReset();
	Renderer->ChangeAnimation("Sword_Swing_Legend");
	Renderer->SetActive(true);
	Collision->SetActive(true);
	//Collision->SetScale(Renderer->GetWorldScale());
	Attack = false;	
}

void APlayer_Attack_Effect::Effect_Attack(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd() == true)
	{
		ChangeState(AttackState::AttackEnd);
	}
}

void APlayer_Attack_Effect::Effect_EndStart()
{
	Collision->SetActive(false);
	Renderer->SetActive(false);
	//Collision->SetScale({0.f, 0.f});
}

void APlayer_Attack_Effect::Effect_End(float _DeltaTime)
{
	Destroy();
}

void APlayer_Attack_Effect::ChangeState(AttackState _Set)
{	
	if (WapponState != _Set)
	{
		switch (_Set)
		{
		case AttackState::Attack:
			Effect_AttackStart();
			break;
		case AttackState::AttackEnd:
			Effect_EndStart();
			break;
		default:
			break;
		}
	}
	WapponState = _Set;
}

void APlayer_Attack_Effect::StateUpdate(float _DeltaTime)
{
	switch (WapponState)
	{
	case AttackState::Attack:
		Effect_Attack(_DeltaTime);
		break;
	case AttackState::AttackEnd:
		Effect_End(_DeltaTime);
		break;
	default:
		break;
	}
}
