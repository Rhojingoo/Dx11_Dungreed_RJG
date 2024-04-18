#include "PreCompile.h"
#include "Boss.h"
#include "Boss_IcePillar.h"
#include "Player.h"
#include <EngineCore/Renderer.h>


ABoss::ABoss()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
	Renderer->SetPivot(EPivot::BOT);
}

ABoss::~ABoss()
{
}

void ABoss::SetPlayer(std::shared_ptr<APlayer> _Set)
{
	Player = _Set;
	for (int Num = 0; Num < 4; Num++)
	{
		IcePillar[Num]->SetPlayer(_Set);
	}
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
	//SetActorScale3D(FVector(320.0f, 320.0f, 100.0f));

	CreateIcePillar();

	Renderer->CreateAnimation("Boss_Attack", "Boss_Attack", 0.1f);
	Renderer->CreateAnimation("Boss_Die", "Boss_Die", 0.1f);
	Renderer->CreateAnimation("Boss_Enter", "Boss_Enter", 0.1f, false);
	Renderer->CreateAnimation("Boss_Exit", "Boss_Exit", 0.1f, false);
	Renderer->CreateAnimation("Boss_Idle", "Boss_Idle", 0.1f);

	Renderer->SetAutoSize(3.f, true);
	//Renderer->ChangeAnimation("Boss_Idle");

	Renderer->SetOrder(ERenderOrder::Boss);
}

void ABoss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FVector BossPos = GetActorLocation();
	for (int Num = 0; Num < 4; Num++)
	{
		IcePillar[Num]->SetActorLocation({BossPos});
	}
	StateUpdate(_DeltaTime);
	Direction();
}

void ABoss::StateChange(BossState _State)
{
	if (Boss_State != _State)
	{
		switch (_State)
		{
		case BossState::Intro:
			Boss_IntroStart();
			break;
		case BossState::Idle:
			Boss_IdleStart();
			break;
			//case BossState::Patton1:
			//	Boss_Patton1();
			//	break;
			//case BossState::Patton2:
			//	Boss_Patton2();
			//	break;
			//case BossState::Patton3:
			//	Boss_Patton3();
			//	break;
			//case BossState::Patton4:
			//	Boss_Patton4();
			//	break;
		default:
			break;
		}
	}
	Boss_State = _State;
}

void ABoss::StateUpdate(float _DeltaTime)
{
	switch (Boss_State)
	{
	case BossState::Intro:
		Boss_Intro(_DeltaTime);
		break;
	case BossState::Idle:
		Boss_Idle(_DeltaTime);
		break;
	case BossState::Patton1:
		Boss_Patton1(_DeltaTime);
		break;
	case BossState::Patton2:
		Boss_Patton2(_DeltaTime);
		break;
	case BossState::Patton3:
		Boss_Patton3(_DeltaTime);
		break;
	case BossState::Patton4:
		Boss_Patton4(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABoss::Boss_Intro(float _DeltaTime)
{
	for (int a = 0; a < 4; a++)
	{
		if (IcePillar[a]->ISIntro() != true)
		{
			return;
		}		
	}

	StateChange(BossState::Idle);
}

void ABoss::Boss_IntroStart()
{
	Renderer->ChangeAnimation("Boss_Enter");

	IcePillar[0]->SetPos({ -200.f,200.f });
	IcePillar[1]->SetPos({ 200.f,200.f });
	IcePillar[2]->SetPos({ -200.f,-200.f });
	IcePillar[3]->SetPos({ 200.f,-200.f });

	IcePillar[0]->StateChange(IcePillarState::Intro);
	IcePillar[1]->StateChange(IcePillarState::Intro);
	IcePillar[2]->StateChange(IcePillarState::Intro);
	IcePillar[3]->StateChange(IcePillarState::Intro);
}



void ABoss::Boss_Idle(float _DeltaTime)
{
	if (IntroOn == false)
	{
		Intro_time += _DeltaTime;
		if (Intro_time > 3.f)
		{
			StateChange(BossState::Intro);
			IntroOn = true;
		}
	}

}

void ABoss::Boss_IdleStart()
{
	Renderer->ChangeAnimation("Boss_Idle");

	IcePillar[0]->SetPos({ 0.f,0.f });
	IcePillar[1]->SetPos({ 0.f,0.f });
	IcePillar[2]->SetPos({ 0.f,0.f });
	IcePillar[3]->SetPos({ 0.f,0.f });

	//IcePillar[0]->SetPos({ -200.f,200.f });
	//IcePillar[1]->SetPos({ 200.f,200.f });
	//IcePillar[2]->SetPos({ -200.f,-200.f });
	//IcePillar[3]->SetPos({ 200.f,-200.f });
}

void ABoss::Boss_Patton1(float _DeltaTime)
{
}

void ABoss::Boss_Patton2(float _DeltaTime)
{
}

void ABoss::Boss_Patton3(float _DeltaTime)
{
}

void ABoss::Boss_Patton4(float _DeltaTime)
{
}

void ABoss::CreateIcePillar()
{
	for (int Num = 0; Num < 4; Num++)
	{
		IcePillar[Num] = GetWorld()->SpawnActor<ABoss_IcePillar>("IcePillar");
		IcePillar[Num]->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	}
}

void ABoss::Direction()
{
	if (Player != nullptr)
	{
		float Dir = Player->GetActorLocation().X - GetActorLocation().X;
		if (Dir > 0.f)
		{
			Renderer->SetDir(EEngineDir::Right);
		}
		else
		{
			Renderer->SetDir(EEngineDir::Left);
		}
	}
}
