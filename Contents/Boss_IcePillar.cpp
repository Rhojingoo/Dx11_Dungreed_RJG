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
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);
	Renderer->SetScale(FVector(62.0f, 33.0f, 100.0f));
	Renderer->AddPosition({ 0.0f, 0.0f, 0.0f });

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
		case IcePillarState::Attack01:
			IcePillar_AttackStart_1();
			break;
		case IcePillarState::Attack02:
			IcePillar_AttackStart_2();
			break;
		case IcePillarState::Attack03:
			IcePillar_AttackStart_3();
			break;
		case IcePillarState::Attack04:
			IcePillar_AttackStart_4();
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
	case IcePillarState::Attack01:
		IcePillar_Attack_1(_DeltaTime);
		break;
	case IcePillarState::Attack02:
		IcePillar_Attack_2(_DeltaTime);
		break;
	case IcePillarState::Attack03:
		IcePillar_Attack_3(_DeltaTime);
		break;
	case IcePillarState::Attack04:
		IcePillar_Attack_4(_DeltaTime);
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



void ABoss_IcePillar::IcePillar_Attack_4(float _DeltaTime)
{
}

void ABoss_IcePillar::IcePillar_AttackStart_4()
{
}



void ABoss_IcePillar::IcePillar_AttackStart_3()
{
}

void ABoss_IcePillar::IcePillar_Attack_3(float _DeltaTime)
{
	if (SetBullet == true)
	{
		FVector ChildRot =Renderer->GetWorldRotation();
		float ChildRotZ = ChildRot.Z * UEngineMath::DToR;

		FVector ChidRotNomal = ChildRot;
		ChidRotNomal.Z = 0;
		ChidRotNomal.X = cos(ChildRot.Z) ;
		ChidRotNomal.Y = sin(ChildRot.Z) ;
		ChidRotNomal.Normalize2D();
		ChidRotNomal *= UEngineMath::DToR;

		if (AttackCount < 3)
		{

			if (false == IceBullet[1]->IsFire())
			{
				if (ChildRot.Z >= 30.f + 45.f && ChildRot.Z <= ((30.f + 45.f) + 1.5f))
				{
					IceBullet[1]->SetActorLocation(RenderPos);
					IceBullet[1]->SetTarget(-ChidRotNomal);
					IceBullet[1]->TargetOn();
					IceBullet[1]->FireOn();
				}
			}

			if (false == IceBullet[2]->IsFire())
			{
				if (ChildRot.Z >= (60.f + 45.f) && ChildRot.Z <= ((60.f + 45.f) + 1.5f))
				{
					IceBullet[2]->SetActorLocation(RenderPos);
					IceBullet[2]->SetTarget(-ChidRotNomal);
					IceBullet[2]->TargetOn();
					IceBullet[2]->FireOn();
				}
			}

			if (false == IceBullet[3]->IsFire())
			{
				if (ChildRot.Z >= (90.f + 45.f) && ChildRot.Z <= ((90.f + 45.f) + 1.5f))
				{
					IceBullet[3]->SetActorLocation(RenderPos);
					IceBullet[3]->SetTarget(-ChidRotNomal);
					IceBullet[3]->TargetOn();
					IceBullet[3]->FireOn();
				}
			}
			if (false == IceBullet[4]->IsFire())
			{
				if (ChildRot.Z >= (120.f + 45.f) && ChildRot.Z <= ((120.f + 45.f) + 1.5f))
				{
					IceBullet[4]->SetActorLocation(RenderPos);
					IceBullet[4]->SetTarget(-ChidRotNomal);
					IceBullet[4]->TargetOn();
					IceBullet[4]->FireOn();
				}
			}

			if (false == IceBullet[5]->IsFire())
			{
				if (ChildRot.Z >= (150.f + 45.f - 180.f) && ChildRot.Z <= ((150.f + 45.f - 180.f) + 1.5f))
				{
					IceBullet[5]->SetActorLocation(RenderPos);
					IceBullet[5]->SetTarget(-ChidRotNomal);
					IceBullet[5]->TargetOn();
					IceBullet[5]->FireOn();
				}
			}

			if (false == IceBullet[6]->IsFire())
			{
				if (ChildRot.Z >= (180.f + 45.f - 180.f) && ChildRot.Z <= ((180.f + 45.f - 180.f) + 1.5f))
				{
					IceBullet[6]->SetActorLocation(RenderPos);
					IceBullet[6]->SetTarget(-ChidRotNomal);
					IceBullet[6]->TargetOn();
					IceBullet[6]->FireOn();
				}
			}

			if (false == IceBullet[0]->IsFire())
			{
				if (ChildRot.Z >= (-180.f + 45.f) && ChildRot.Z <= ((-180.f + 45.f) + 1.5f))
				{
					IceBullet[0]->SetActorLocation(RenderPos);
					IceBullet[0]->SetTarget(-ChidRotNomal);
					IceBullet[0]->TargetOn();
					IceBullet[0]->FireOn();
				}
			}

			if (false == IceBullet[7]->IsFire())
			{
				if (ChildRot.Z >= (-150.f + 45.f) && ChildRot.Z <= ((-150.f + 45.f) + 1.5f))
				{
					IceBullet[7]->SetActorLocation(RenderPos);
					IceBullet[7]->SetTarget(-ChidRotNomal);
					IceBullet[7]->TargetOn();
					IceBullet[7]->FireOn();
				}
			}

			if (false == IceBullet[8]->IsFire())
			{
				if (ChildRot.Z >= (-120.f + 45.f) && ChildRot.Z <= ((-120.f + 45.f) + 1.5f))
				{
					IceBullet[8]->SetActorLocation(RenderPos);
					IceBullet[8]->SetTarget(-ChidRotNomal);
					IceBullet[8]->TargetOn();
					IceBullet[8]->FireOn();
				}
			}

			if (false == IceBullet[9]->IsFire())
			{
				if (ChildRot.Z >= (-90.f + 45.f) && ChildRot.Z <= ((-90.f + 45.f) + 1.5f))
				{
					IceBullet[9]->SetActorLocation(RenderPos);
					IceBullet[9]->SetTarget(-ChidRotNomal);
					IceBullet[9]->TargetOn();
					IceBullet[9]->FireOn();
				}
			}

			if (false == IceBullet[10]->IsFire())
			{
				if (ChildRot.Z >= (-60.f + 45.f) && ChildRot.Z <= ((-60.f + 45.f) + 1.5f))
				{
					IceBullet[10]->SetActorLocation(RenderPos);
					IceBullet[10]->SetTarget(-ChidRotNomal);
					IceBullet[10]->TargetOn();
					IceBullet[10]->FireOn();
				}
			}

			if (false == IceBullet[11]->IsFire())
			{
				if (ChildRot.Z >= (-30.f + 45.f) && ChildRot.Z <= ((-30.f + 45.f) + 1.5f))
				{
					IceBullet[11]->SetActorLocation(RenderPos);
					IceBullet[11]->SetTarget(-ChidRotNomal);
					IceBullet[11]->TargetOn();
					IceBullet[11]->FireOn();
				}
			}

			if (false == IceBullet[12]->IsFire())
			{
				if (ChildRot.Z >= (-180.f + 15.f) && ChildRot.Z <= ((-180.f + 15.f) + 1.5f))
				{
					IceBullet[12]->SetActorLocation(RenderPos);
					IceBullet[12]->SetTarget(-ChidRotNomal);
					IceBullet[12]->TargetOn();
					IceBullet[12]->FireOn();
				}
			}


			for (int a = 0; a < 13; a++)
			{
				if (true != IceBullet[a]->IsFire())
				{
					Renderer->AddRotationDeg(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
					return;
				}
			}
			AttackCount++;
			for (int a = 0; a < 13; a++)
			{
				IceBullet[a]->FireOff();
			}
		}
		else
		{
			AttackEnd = true;
		}

	}
	if (AttackEnd == true)
	{
		AttackCount = 0;
	}
	Renderer->AddRotationDeg(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
}



void ABoss_IcePillar::IcePillar_AttackStart_2()
{
	SetBullet = true;
}

void ABoss_IcePillar::IcePillar_Attack_2(float _DeltaTime)
{
	if (SetBullet == true)
	{
		FVector RootRENDERPos = Root->GetWorldRotation();
		GetActorTransform().GetRotation();
		FVector ParentPos =  GetActorLocation();
		FVector ChidPos1 = Renderer->GetWorldPosition();
		FVector DirPos = ChidPos1 - ParentPos;
		DirPos.Normalize2D();
		DirPos.Z = 0;
		DirPos *= UEngineMath::DToR;
		if (AttackCount < 3)
		{
			if (RootRENDERPos.Z >= 30.f + 45.f && RootRENDERPos.Z <= ((30.f + 45.f) + 1.f))
			{
				IceBullet[1]->SetActorLocation(RenderPos);
				IceBullet[1]->SetTarget(-DirPos);
				IceBullet[1]->TargetOn();
				IceBullet[1]->FireOn();
			}

			if (RootRENDERPos.Z >= (60.f + 45.f) && RootRENDERPos.Z <= ((60.f + 45.f) + 1.f))
			{
				IceBullet[2]->SetActorLocation(RenderPos);
				IceBullet[2]->SetTarget(-DirPos);
				IceBullet[2]->TargetOn();
				IceBullet[2]->FireOn();
			}

			if (RootRENDERPos.Z >= (90.f + 45.f) && RootRENDERPos.Z <= ((90.f + 45.f) + 1.f))
			{
				IceBullet[3]->SetActorLocation(RenderPos);
				IceBullet[3]->SetTarget(-DirPos);
				IceBullet[3]->TargetOn();
				IceBullet[3]->FireOn();
			}

			if (RootRENDERPos.Z >= (120.f + 45.f) && RootRENDERPos.Z <= ((120.f + 45.f) + 1.f))
			{
				IceBullet[4]->SetActorLocation(RenderPos);
				IceBullet[4]->SetTarget(-DirPos);
				IceBullet[4]->TargetOn();
				IceBullet[4]->FireOn();
			}

			if (RootRENDERPos.Z >= (150.f + 45.f - 180.f) && RootRENDERPos.Z <= ((150.f + 45.f - 180.f) + 1.f))
			{
				IceBullet[5]->SetActorLocation(RenderPos);
				IceBullet[5]->SetTarget(-DirPos);
				IceBullet[5]->TargetOn();
				IceBullet[5]->FireOn();
			}

			if (RootRENDERPos.Z >= (180.f + 45.f - 180.f) && RootRENDERPos.Z <= ((180.f + 45.f - 180.f) + 1.f))
			{
				IceBullet[6]->SetActorLocation(RenderPos);
				IceBullet[6]->SetTarget(-DirPos);
				IceBullet[6]->TargetOn();
				IceBullet[6]->FireOn();
			}

			if (RootRENDERPos.Z >= (-180.f + 45.f) && RootRENDERPos.Z <= ((-180.f + 45.f) + 1.f))
			{
				IceBullet[0]->SetActorLocation(RenderPos);
				IceBullet[0]->SetTarget(-DirPos);
				IceBullet[0]->TargetOn();
				IceBullet[0]->FireOn();
			}

			if (RootRENDERPos.Z >= (-150.f + 45.f) && RootRENDERPos.Z <= ((-150.f + 45.f) + 1.f))
			{
				IceBullet[7]->SetActorLocation(RenderPos);
				IceBullet[7]->SetTarget(-DirPos);
				IceBullet[7]->TargetOn();
				IceBullet[7]->FireOn();
			}

			if (RootRENDERPos.Z >= (-120.f + 45.f) && RootRENDERPos.Z <= ((-120.f + 45.f) + 1.f))
			{
				IceBullet[8]->SetActorLocation(RenderPos);
				IceBullet[8]->SetTarget(-DirPos);
				IceBullet[8]->TargetOn();
				IceBullet[8]->FireOn();
			}

			if (RootRENDERPos.Z >= (-90.f + 45.f) && RootRENDERPos.Z <= ((-90.f + 45.f) + 1.f))
			{
				IceBullet[9]->SetActorLocation(RenderPos);
				IceBullet[9]->SetTarget(-DirPos);
				IceBullet[9]->TargetOn();
				IceBullet[9]->FireOn();
			}

			if (RootRENDERPos.Z >= (-60.f + 45.f) && RootRENDERPos.Z <= ((-60.f + 45.f) + 1.f))
			{
				IceBullet[10]->SetActorLocation(RenderPos);
				IceBullet[10]->SetTarget(-DirPos);
				IceBullet[10]->TargetOn();
				IceBullet[10]->FireOn();
			}

			if (RootRENDERPos.Z >= (-30.f + 45.f) && RootRENDERPos.Z <= ((-30.f + 45.f) + 1.f))
			{
				IceBullet[11]->SetActorLocation(RenderPos);
				IceBullet[11]->SetTarget(-DirPos);
				IceBullet[11]->TargetOn();
				IceBullet[11]->FireOn();
			}
			if (RootRENDERPos.Z >= (-180.f + 15.f) && RootRENDERPos.Z <= ((-180.f + 15.f) + 1.f))
			{
				IceBullet[12]->SetActorLocation(RenderPos);
				IceBullet[12]->SetTarget(-DirPos);
				IceBullet[12]->TargetOn();
				IceBullet[12]->FireOn();
			}


			for (int a = 0; a < 13; a++)
			{
				if (true != IceBullet[a]->IsFire())
				{
					Renderer->AddRotationDeg(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
					AddActorRotation(float4{ 0.0f, 0.0f, 1.0f } *500.0f * _DeltaTime);
					return;
				}
			}
			AttackCount++;
			for (int a = 0; a < 13; a++)
			{
				IceBullet[a]->FireOff();
			}
		}
		else
		{
			AttackEnd = true;
		}

	}
	if (AttackEnd == true)
	{
		AttackCount = 0;
	}
	Renderer->AddRotationDeg(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
	AddActorRotation(float4{ 0.0f, 0.0f, 1.0f } *500.0f * _DeltaTime);
}


void ABoss_IcePillar::IcePillar_AttackStart_1()
{
}

void ABoss_IcePillar::IcePillar_Attack_1(float _DeltaTime)
{

	if (SetBullet == true)
	{
		static int Num = 0;
		static float check = 0.0f;

		FireTime += _DeltaTime;

		if ((FireTime - check) >= 0.05f)
		{
			if (Num < 13)
			{
				if (AttackDirSet == false)
				{
					BulletDir = RenderPos - PlayerPos;
					AttackDirSet = true;
				}

				IceBullet[Num]->SetActorLocation(Renderer->GetWorldPosition());
				//BulletDir = RenderPos - CPlayerpos;
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
				AttackEnd = true;
				AttackDirSet = false;
			}
		}
	}
	if (AttackEnd == true)
	{

	}
	Renderer->AddRotationDeg(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
}


void ABoss_IcePillar::BeginPlay()
{
	Super::BeginPlay();

	for (int Num = 0; Num <= 12; Num++)
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
