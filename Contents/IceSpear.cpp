#include "PreCompile.h"
#include "IceSpear.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

AIceSpear::AIceSpear()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	//Renderer->SetPivot(EPivot::BOT);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionGroup(EColOrder::Boss_IceSpear);
	Collision->SetCollisionType(ECollisionType::RotRect);


	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	EffectRenderer->SetupAttachment(Root);
	//EffectRenderer->SetPivot(EPivot::BOT);
	SetRoot(Root);
}

AIceSpear::~AIceSpear()
{
}

void AIceSpear::AttackOn()
{
	Attack_Start = true;
	EffectRenderer->ChangeAnimation("SpearCreat_Effect");	
}

void AIceSpear::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetAutoSize(2.f, true);
	Renderer->CreateAnimation("IceSpear", "IceSpear", 0.1f, false);
	//Renderer->ChangeAnimation("IceSpear");
	Renderer->SetOrder(ERenderOrder::Boss_Bullet);
	Renderer->AddPosition({ 0.f, 0.f, 0.f });


	EffectRenderer->CreateAnimation("SpearCreat_Effect", "SpearCreat_Effect", 0.1f, false);
	EffectRenderer->SetOrder(ERenderOrder::Effect_Front);
	EffectRenderer->SetAutoSize(4.f, true);
	EffectRenderer->AddPosition({ 0.f, 0.f, 0.f });
}

void AIceSpear::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}


void AIceSpear::EffectStart()
{
	EffectRenderer->ChangeAnimation("SpearCreat_Effect");
}
void AIceSpear::Effect(float _DeltaTime)
{
	if (Attack_Start == true)
	{
		if (EffectRenderer->IsCurAnimationEnd() == true)
		{
			EffectEnd = true;
			ChangeState(Spearstate::Spear);
		}
	}
}



void AIceSpear::SpearStart()
{
	Renderer->ChangeAnimation("IceSpear");
}


void AIceSpear::Spear(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd() == true)
	{
		EffectEnd = true;
		ChangeState(Spearstate::Attack);
	}
}



void AIceSpear::AttackStart()
{
}
void AIceSpear::Attack(float _DeltaTime)
{
	if (RightAttack == true)
	{		
		AttPos += FVector::Right * Speed * _DeltaTime;
		AddActorLocation(AttPos);
	}
	else if(LeftAttack = true)
	{		
		AttPos += FVector::Left * Speed * _DeltaTime;
		AddActorLocation(AttPos);
	}

	Destroy_Time += _DeltaTime;
	if (Destroy_Time > 5.5f)
	{
		Destroy();
	}

	//if (Player->GetActorLocation().X - GetActorLocation().X >= 0.f) {}
}



void AIceSpear::ChangeState(Spearstate _Set)
{
	if (Spear_state != _Set)
	{
		switch (_Set)
		{
		case Spearstate::Effect:
			EffectStart();
			break;
		case Spearstate::Spear:
			SpearStart();
			break;
		case Spearstate::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}

	Spear_state = _Set;
}

void AIceSpear::StateUpdate(float _DeltaTime)
{
	switch (Spear_state)
	{
	case Spearstate::Effect:
		Effect(_DeltaTime);
		break;
	case Spearstate::Spear:
		Spear( _DeltaTime);
		break;
	case Spearstate::Attack:
		Attack( _DeltaTime);
		break;
	default:
		break;
	}
}
