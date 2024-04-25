#include "PreCompile.h"
#include "Player_Attack_Effect.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsHelper.h"
#include "IceBullet.h"
#include "Icicle_Bullet.h"

Sword_Type APlayer_Attack_Effect::SwordType = Sword_Type::Lasli_Sword;


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

	Renderer->CreateAnimation("Sword_Swing_Normal", "Sword_Swing_Normal", 0.1f, false);
	Renderer->CreateAnimation("Sword_Swing_Legend", "Sword_Swing_Legend", 0.1f, false);
	Renderer->CreateAnimation("FireSword_Swing_Legend", "FireSword_Swing_Legend", 0.1f, false);	
	Renderer->SetAutoSize(5.f, true);
	Renderer->SetOrder(ERenderOrder::Attack_Effect);


	FVector asd1 = Renderer->GetLocalScale();
	FVector asd = Renderer->GetWorldScale();
	Collision->SetScale(Renderer->GetWorldScale());
	if (SwordType == Sword_Type::Lasli_Sword)
	{
		Renderer->ChangeAnimation("Sword_Swing_Legend");
	}
	else if (SwordType == Sword_Type::Fire_Sword)
	{
		Renderer->ChangeAnimation("FireSword_Swing_Legend");
	}
}	 

void APlayer_Attack_Effect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Collision->SetScale(Renderer->GetWorldScale());
	StateUpdate(_DeltaTime);
	CollisionCheck_Function();	

	if (Attack == true)
	{
		ChangeState(AttackState::Attack);
	}
}

void APlayer_Attack_Effect::Effect_AttackStart()
{
	Renderer->AnimationReset();
	if (SwordType == Sword_Type::Lasli_Sword)
	{
		Renderer->ChangeAnimation("Sword_Swing_Legend");

		Sword_Damage = UContentsHelper::Random(Lasli_Sword_MinDamage, Lasli_Sword_MaxDamage);
	}
	else if (SwordType == Sword_Type::Fire_Sword)
	{
		Renderer->ChangeAnimation("FireSword_Swing_Legend");
		Sword_Damage = UContentsHelper::Random(Fire_Sword_MinDamage, Fire_Sword_MaxDamage);
	}
	Renderer->SetActive(true);
	Collision->SetActive(true);
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

void APlayer_Attack_Effect::SwordEffectType_Choice(Sword_Type _Set)
{
	SwordType = _Set;
}

void APlayer_Attack_Effect::CollisionCheck_Function()
{
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
}
