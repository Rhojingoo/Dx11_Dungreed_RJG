#include "PreCompile.h"
#include "Icicle_Bullet.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>


AIcicle_Bullet::AIcicle_Bullet()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	EffectRenderer->SetupAttachment(Root);
	EffectRenderer->SetPivot(EPivot::BOT);
	SetRoot(Root);
}

AIcicle_Bullet::~AIcicle_Bullet()
{
}

void AIcicle_Bullet::AttackOn()
{
	Attack_Start = true;
	EffectRenderer->ChangeAnimation("Icicle_Effect");
}

void AIcicle_Bullet::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetAutoSize(3.f, true);
	Renderer->CreateAnimation("Icicle_Bullet", "Icicle_Bullet", 0.1f, false);
	//Renderer->ChangeAnimation("IceSpear");
	Renderer->SetOrder(ERenderOrder::Boss_Bullet);
	Renderer->AddPosition({ 0.f, 0.f, 0.f });


	EffectRenderer->CreateAnimation("Icicle_Effect", "Icicle_Effect", 0.1f, false);
	EffectRenderer->SetOrder(ERenderOrder::Effect_Front);
	EffectRenderer->SetAutoSize(4.f, true);
	EffectRenderer->AddPosition({ 0.f, 250.f, 0.f });
}

void AIcicle_Bullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}


void AIcicle_Bullet::EffectStart()
{
	EffectRenderer->ChangeAnimation("Icicle_Effect");
}
void AIcicle_Bullet::Effect(float _DeltaTime)
{
	if (Attack_Start == true)
	{
		if (EffectRenderer->IsCurAnimationEnd() == true)
		{
			EffectEnd = true;
			ChangeState(Iciclestate::Icicle);
		}
	}
}



void AIcicle_Bullet::SpearStart()
{
	Renderer->ChangeAnimation("Icicle_Bullet");
}

void AIcicle_Bullet::Spear(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd() == true)
	{
		EffectEnd = true;
		ChangeState(Iciclestate::Attack);
	}
}



void AIcicle_Bullet::AttackStart()
{
}

void AIcicle_Bullet::Attack(float _DeltaTime)
{
	AttPos += FVector::Down * Speed * _DeltaTime;
	AddActorLocation(AttPos);

	Destroy_Time += _DeltaTime;
	if (Destroy_Time > 5.5f)
	{
		Destroy();
	}
}





void AIcicle_Bullet::ChangeState(Iciclestate _Set)
{
	if (Icicle_state != _Set)
	{
		switch (_Set)
		{
		case Iciclestate::Effect:
			EffectStart();
			break;
		case Iciclestate::Icicle:
			SpearStart();
			break;
		case Iciclestate::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}

	Icicle_state = _Set;
}

void AIcicle_Bullet::StateUpdate(float _DeltaTime)
{
	switch (Icicle_state)
	{
	case Iciclestate::Effect:
		Effect(_DeltaTime);
		break;
	case Iciclestate::Icicle:
		Spear(_DeltaTime);
		break;
	case Iciclestate::Attack:
		Attack(_DeltaTime);
		break;
	default:
		break;
	}
}
