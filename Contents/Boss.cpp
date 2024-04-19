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
		case BossState::Patton1:
			Boss_Patton1Start();
			break;
		case BossState::Patton2:
			Boss_Patton2Start();
			break;
		case BossState::Ready:
			Boss_ReadyStart(); 
			break;
		case BossState::Ready2:
			Boss_ReadyStart2();
			break;;
		case BossState::Patton3:
			Boss_Patton3Start();
			break;
		case BossState::Patton4:
			Boss_Patton4Start();
			break;
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
	case BossState::Ready:
		Boss_Ready(_DeltaTime);
		break;
	case BossState::Ready2:
		Boss_Ready2(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABoss::Boss_Intro(float _DeltaTime)
{
	for (int a = 0; a < 4; a++)
	{
		//if (IcePillar[0]->ISIntro() != true)
		//{
		//	return;
		//}

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

	IcePillar[0]->AddPos({ -Bullet,Bullet });
	IcePillar[1]->AddPos({ Bullet,Bullet });
	IcePillar[2]->AddPos({ -Bullet,-Bullet });
	IcePillar[3]->AddPos({ Bullet,-Bullet });

	PlRotation[0] = IcePillar[0]->GetActorTransform().GetRotation();
	PlRotation[1] = IcePillar[1]->GetActorTransform().GetRotation();
	PlRotation[2] = IcePillar[2]->GetActorTransform().GetRotation();
	PlRotation[3] = IcePillar[3]->GetActorTransform().GetRotation();

	for (int a = 0; a < 4; a++)
	{
		//Bullet_Pos[0] = IcePillar[a]->GetPos();
		//IcePillar[0]->StateChange(IcePillarState::Intro);
		Bullet_Pos[a] = IcePillar[a]->GetPos();
		IcePillar[a]->StateChange(IcePillarState::Intro);
	}


}



void ABoss::Boss_Idle(float _DeltaTime)
{
	if (IntroOn == false)
	{
		Boss_Time += _DeltaTime;
		if (Boss_Time > 3.f)
		{
			StateChange(BossState::Intro);
			IntroOn = true;
			Boss_Time = 0.f;
		}
	}
	else
	{
		if (UEngineInput::IsPress('1'))
		{
			StateChange(BossState::Patton1);
			Boss_Time = 0.f;
		}
		if (UEngineInput::IsPress('2'))
		{
			StateChange(BossState::Patton2);
			Boss_Time = 0.f;
		}
		if (UEngineInput::IsPress('3'))
		{
			StateChange(BossState::Patton3);
			Boss_Time = 0.f;
		}

		Boss_Time += _DeltaTime;
		if (Boss_Time > 3.f)
		{
			//StateChange(BossState::Patton1);
			//StateChange(BossState::Patton2);
			//StateChange(BossState::Patton3);
			Boss_Time = 0.f;
		}
	}
}

void ABoss::Boss_IdleStart()
{
	Renderer->ChangeAnimation("Boss_Idle");

	IcePillar[0]->AddPos({ 0.f,0.f });
	IcePillar[1]->AddPos({ 0.f,0.f });
	IcePillar[2]->AddPos({ 0.f,0.f });
	IcePillar[3]->AddPos({ 0.f,0.f });
}

void ABoss::Boss_Patton1Start()
{	
	for (int a = 0; a < 4; a++)
	{
		IcePillar[a]->StateChange(IcePillarState::Attack01);
	}
	Attack_Check = true;
}

void ABoss::Boss_Patton1(float _DeltaTime)
{
	{		
		static float IcePillarPos = 0.f;
		if (Attack_Check == true)
		{
			if (IcePillarPos < 7.f)
			{
				IcePillarPos += 50.f * _DeltaTime;
				IcePillar[0]->AddPos({ -IcePillarPos, IcePillarPos / 2 });
				IcePillar[1]->AddPos({ IcePillarPos, IcePillarPos / 2 });
				IcePillar[2]->AddPos({ -IcePillarPos,-IcePillarPos / 1000 });
				IcePillar[3]->AddPos({ IcePillarPos,-IcePillarPos / 1000 });
				return;
			}
			else
			{	
				for (int a = 0; a < 4; a++)
				{
					IcePillar[a]->FireOn();
				}
				Attack_Check = false;
				IcePillarPos = 0.f;				
			}
		}
		else
		{
			for (int a = 0; a < 4; a++)
			{
				if (true != IcePillar[a]->IsAttackEnd())
				{
					return;
				}
			}
			StateChange(BossState::Ready);
		}
	}
}


void ABoss::Boss_Patton2Start()
{
	for (int a = 0; a < 4; a++)
	{
		IcePillar[a]->StateChange(IcePillarState::Attack02);
	}
	Attack_Check = true;
}

void ABoss::Boss_Patton2(float _DeltaTime)
{
	static float IcePillarPos = 0.f;
	if (Attack_Check == true)
	{
		for (int a = 0; a < 4; a++)
		{
			if (true != IcePillar[a]->IsAttackEnd())
			{
				return;
			}
		}
		Attack_Check = false;
		StateChange(BossState::Ready2);
	}
}

void ABoss::Boss_Patton3Start()
{
	for (int a = 0; a < 4; a++)
	{
		IcePillar[a]->SetPos({ Bullet_Pos[a].X, Bullet_Pos[a].Y });
		IcePillar[a]->AttackEndFalse();
		IcePillar[a]->StateChange(IcePillarState::Attack03);
		IcePillar[a]->SetActorRotation({ PlRotation[a] });
	}
	//IcePillar[0]->SetActorRotation({ PlRotation[0] });
	//IcePillar[1]->SetActorRotation({ PlRotation[1] });
	//IcePillar[2]->SetActorRotation({ PlRotation[2] });
	//IcePillar[3]->SetActorRotation({ PlRotation[3] });

	Attack_Check = true;	
}

void ABoss::Boss_Patton3(float _DeltaTime)
{
	static float IcePillarPos = 0.f;
	if (Attack_Check == true)
	{
	
		if (IcePillarPos < 7.f)
		{
			IcePillarPos += 50.f * _DeltaTime;
			IcePillar[0]->AddPos({ -IcePillarPos, -IcePillarPos * 1.2f });
			IcePillar[1]->AddPos({ IcePillarPos, -IcePillarPos * 1.2f });
			//IcePillar[2]->AddPos({ -IcePillarPos,-IcePillarPos / 1000 });
			//IcePillar[3]->AddPos({ IcePillarPos,-IcePillarPos / 1000 });
			return;
		}
		else
		{
			for (int a = 0; a < 4; a++)
			{
				IcePillar[a]->FireOn();
			}
			Attack_Check = false;
			//IcePillarPos = 0.f;
		}
	}
	else
	{
		for (int a = 0; a < 4; a++)
		{
			if (true != IcePillar[a]->IsAttackEnd())
			{
				return;
			}
		}
		StateChange(BossState::Ready);
	}
}




void ABoss::Boss_Patton4(float _DeltaTime)
{

}

void ABoss::Boss_Patton4Start()
{
}



void ABoss::Boss_Ready2(float _DeltaTime)
{	
	for (int a = 0; a < 4; a++)
	{
		//IcePillar[a]->SetPos({ Bullet_Pos[a].X, Bullet_Pos[a].Y });
		//IcePillar[a]->AttackEndFalse();
		IcePillar[a]->StateChange(IcePillarState::Idle);
	}
	StateChange(BossState::Idle);
}

void ABoss::Boss_ReadyStart2()
{
	for (int a = 0; a < 4; a++)
	{
		IcePillar[a]->SetPos({ Bullet_Pos[a].X, Bullet_Pos[a].Y });
		IcePillar[a]->AttackEndFalse();
		IcePillar[a]->SetActorRotation({ PlRotation[a] });
	}
	//IcePillar[0]->SetActorRotation({ PlRotation[0] });
	//IcePillar[1]->SetActorRotation({ PlRotation[1] });
	//IcePillar[2]->SetActorRotation({ PlRotation[2] });
	//IcePillar[3]->SetActorRotation({ PlRotation[3] });
}

void ABoss::Boss_ReadyStart()
{
	for (int a = 0; a < 4; a++)
	{
		IcePillar[a]->SetPos({ Bullet_Pos[a].X, Bullet_Pos[a].Y });
		IcePillar[a]->AttackEndFalse();
		IcePillar[a]->StateChange(IcePillarState::Idle);
	}
}

void ABoss::Boss_Ready(float _DeltaTime)
{
	static float IcePillarPos = 7.f;
	if (IcePillarPos >= 0.f)
	{
		IcePillarPos -= 50.f * _DeltaTime;
		IcePillar[0]->AddPos({ IcePillarPos,-IcePillarPos / 2 });
		IcePillar[1]->AddPos({ -IcePillarPos,-IcePillarPos / 2 });
		IcePillar[2]->AddPos({ IcePillarPos,IcePillarPos / 1000 });
		IcePillar[3]->AddPos({ -IcePillarPos,IcePillarPos / 1000 });
	}
	else
	{
		IcePillarPos = 0;
		for (int a = 0; a < 4; a++)
		{
			IcePillar[a]->SetPos({ Bullet_Pos[a].X, Bullet_Pos[a].Y });
			IcePillar[a]->AttackEndFalse();
			IcePillar[a]->StateChange(IcePillarState::Idle);
		}
		StateChange(BossState::Idle);
		IcePillarPos = 7.f;
	}
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
