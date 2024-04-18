#include "PreCompile.h"
#include "Boss_IcePillar.h"
#include "IceBullet.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ABoss_IcePillar::ABoss_IcePillar()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);
	Renderer->SetScale(FVector(62.0f, 33.0f, 100.0f));
	Renderer->AddPosition({ 0.0f, 0.0f, 0.0f });

	//Hand_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer1");
	//Hand_Renderer->SetupAttachment(Root);
	//Hand_Renderer->SetPivot(EPivot::BOT);
	//Hand_Renderer->CreateAnimation("Player_Hand", "Player_Hand", 0.1f);
	//Hand_Renderer->ChangeAnimation("Player_Hand");
	//Hand_Renderer->SetScale(FVector(9.0f, 9.0f, 100.0f));
	//Hand_Renderer->AddPosition({ 20.0f, 0.0f, 0.0f });

	SetRoot(Root);
}

ABoss_IcePillar::~ABoss_IcePillar()
{
}

void ABoss_IcePillar::StateChange(IcePillarState _State)
{
	if (IcePillar_State != _State)
	{
		switch (_State)
		{
		case IcePillarState::None:
			break;
		case IcePillarState::Intro:
			IcePillar_IntroStart();
			break;
		case IcePillarState::Idle:
			IcePillar_IdleStart();
			break;
		case IcePillarState::Attack:
			IcePillar_AttackStart();
			break;
		//case IcePillarState::Rotation:
		//	break;
		//case IcePillarState::Stop:
		//	IcePillar_Stop(_DeltaTime);
		//	break;
		default:
			break;
		}
	}
	IcePillar_State = _State;
}

void ABoss_IcePillar::StateUpdate(float _DeltaTime)
{
	switch (IcePillar_State)
	{
	case IcePillarState::None:
		break;
	case IcePillarState::Intro:
		IcePillar_Intro(_DeltaTime);
		break;
	case IcePillarState::Idle:
		IcePillar_Idle(_DeltaTime);
		break;
	case IcePillarState::Rotation:
		IcePillar_Rotation(_DeltaTime);
		break;
	case IcePillarState::Stop:
		IcePillar_Stop(_DeltaTime);
		break;
	case IcePillarState::Attack:
		IcePillar_Attack(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABoss_IcePillar::IcePillar_Intro(float _DeltaTime)
{
	AddActorRotation(float4{ 0.0f, 0.0f, 1.0f } *180.0f * _DeltaTime);
	Renderer->AddRotationDeg(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
	IntroCheck = Renderer->IsCurAnimationEnd();
	//IntroCheck = true;
	//if(IntroCheck == true)
	//	int a = 0;
}

void ABoss_IcePillar::IcePillar_IntroStart()
{
	Renderer->ChangeAnimation("IcePillar");
}

void ABoss_IcePillar::IcePillar_Idle(float _DeltaTime)
{
	Renderer->AddRotationDeg(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
}

void ABoss_IcePillar::IcePillar_IdleStart()
{
}

void ABoss_IcePillar::IcePillar_Rotation(float _DeltaTime)
{
}

void ABoss_IcePillar::IcePillar_Stop(float _DeltaTime)
{
}

void ABoss_IcePillar::IcePillar_Attack(float _DeltaTime)
{
	if (UEngineInput::IsPress('1'))
	{
		SetBullet = true;
	}
	if (SetBullet == true)
	{
		static int Num = 0;
		static float check = 0.0f;

		FireTime += _DeltaTime;

		if ((FireTime - check) >= 0.05f)
		{
			if (Num < 12)
			{
				IceBullet[Num]->SetActorLocation(RenderPos);
				BulletDir = RenderPos - PlayerPos;
				BulletDir.Normalize2D();
				BulletDir.Z = 0;
				BulletDir.X *= UEngineMath::DToR;
				BulletDir.Y *= UEngineMath::DToR;
				IceBullet[Num]->SetTarget(BulletDir);
				IceBullet[Num]->TargetOn();

				++Num;
				check = FireTime;
			}
			else
			{
				Num = 0;
				SetBullet = false;
			}
		}
	}

	//Renderer->AddRotationDeg(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
}

void ABoss_IcePillar::IcePillar_AttackStart()
{
}

void ABoss_IcePillar::BeginPlay()
{
	Super::BeginPlay();

	for (int Num = 0; Num < 12; Num++)
	{
		IceBullet[Num] = GetWorld()->SpawnActor<AIceBullet>("IceBullet");
		IceBullet[Num]->SetActorLocation({640.0f, -360.0f, 200.0f});
	}

	Renderer->SetAutoSize(4.0f, true);
	Renderer->CreateAnimation("IcePillar", "IcePillar", 0.1f, false);
	Renderer->CreateAnimation("IcePillarDestroy", "IcePillarDestroy", 0.1f);

	Renderer->SetOrder(ERenderOrder::Boss_Bullet);
}

void ABoss_IcePillar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Pos = GetActorLocation();
	RenderPos = Renderer->GetWorldPosition();
	StateUpdate(_DeltaTime);

	
	if (Player != nullptr)
	{
		PlayerPos = Player->GetActorLocation();
	}	

	

}
