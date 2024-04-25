#include "PreCompile.h"
#include "Boss.h"
#include "Boss_IcePillar.h"
#include "IceSpear.h"
#include "Icicle_Bullet.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Boss_HpBar.h"
#include "Player_Attack_Effect.h"

float ABoss::IcePillarPos = 0.f;


ABoss::ABoss()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);

	Effect_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Effect_Renderer->SetupAttachment(Root);
	Effect_Renderer->SetPivot(EPivot::BOT);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionGroup(EColOrder::Boss);
	Collision->SetCollisionType(ECollisionType::RotRect);

	SetRoot(Root);
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
	Renderer->CreateAnimation("Boss_Die", "Boss_Die", 0.1f, false);
	Renderer->CreateAnimation("Boss_Enter", "Boss_Enter", 0.1f, false);
	Renderer->CreateAnimation("Boss_Exit", "Boss_Exit", 0.1f, false);
	Renderer->CreateAnimation("Boss_Idle", "Boss_Idle", 0.1f);
	Renderer->SetAutoSize(3.f, true);


	//이펙트 렌더 설정
	Effect_Renderer->SetOrder(ERenderOrder::Effect_Front);
	Effect_Renderer->SetActive(false);
	Effect_Renderer->SetAutoSize(1.5f, true);
	Effect_Renderer->AddPosition({ 0.f,50.f});
	Effect_Renderer->CreateAnimation("Stun", "Stun.png", 0.1f, true);


	Collision->SetScale({ Renderer->GetWorldScale().X / 2, Renderer->GetWorldScale().Y / 2,200.f });
	Collision->AddPosition({ 0.f, 0.25f });

	Boss_HpBAR = GetWorld()->SpawnActor<ABoss_HpBar>("Boss_HPBar");


	Renderer->SetOrder(ERenderOrder::Boss);
}

void ABoss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FVector BossPos = GetActorLocation();
	for (int Num = 0; Num < 4; Num++)
	{
		//IcePillar[0]->SetActorLocation({ BossPos });
		IcePillar[Num]->SetActorLocation({BossPos});
	}
	StateUpdate(_DeltaTime);
	if (Death == false)
	{
		Direction();
		IcePallarCheck();
	}
	{
		//std::string Msg = std::format("BossCollisionPos : {}\n", Collision->GetWorldPosition().ToString());
		//UEngineDebugMsgWindow::PushMsg(Msg);
	}

	Collision->CollisionEnter(EColOrder::Wapon, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			APlayer_Attack_Effect* Wapon = dynamic_cast<APlayer_Attack_Effect*>(Actors);
			if (Wapon != nullptr)
			{
				if (DamageOn == true)
				{
					float Damage = Wapon->AttackDamage();
					Hp -= Damage;
					float Damageratio = Hp / Max_Hp;
					Damageratio = 1 - Damageratio;
					if (Hp <= 0.f)
					{
						Effect_Renderer->SetActive(false);
						StateChange(BossState::Death);
						Damageratio = 0;
						Boss_HpBAR->AttackDamege(1);
						Death = true;
						return;
					}
					Boss_HpBAR->AttackDamege(Damageratio);
				}		
				return;
			}
		}
	);
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
		case BossState::Patton3:
			Boss_Patton3Start();
			break;
		case BossState::Patton4:
			Boss_Patton4Start();
			break;
		case BossState::Patton5:
			Boss_Patton5Start();
			break;
		case BossState::Ready:
			Boss_ReadyStart(); 
			break;
		case BossState::Ready2:
			Boss_ReadyStart2();
			break;
		case BossState::Fainting:
			Boss_FaintingStart();
			break;
		case BossState::TeleportIn:
			Boss_TeleportInStart();
			break;
		case BossState::TeleportOut:
			Boss_TeleportOutStart();
			break;
		case BossState::Death:
			Boss_DeathStart();
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
	case BossState::Patton5:
		Boss_Patton5(_DeltaTime);
		break;

	case BossState::Ready:
		Boss_Ready(_DeltaTime);
		break;
	case BossState::Ready2:
		Boss_Ready2(_DeltaTime);
		break;
	case BossState::Fainting:
		Boss_Fainting(_DeltaTime);
		break;;
	case BossState::TeleportIn:
		Boss_TeleportIn(_DeltaTime);
		break;
	case BossState::TeleportOut:
		Boss_TeleportOut(_DeltaTime);
		break;
	case BossState::Death:
		Boss_Death(_DeltaTime);
		break;
	default:
		break;
	}
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
		Bullet_Pos[a] = IcePillar[a]->GetPos();
		IcePillar[a]->StateChange(IcePillarState::Intro);
	}
}

void ABoss::Boss_Intro(float _DeltaTime)
{
	for (int Num = 0; Num < 4; Num++)
	{
		if (IcePillar[Num]->ISIntro() != true)
		{
			return;
		}		
	}
	for (int Num = 0; Num < 4; Num++)
	{
		IcePillar[Num]->StateChange(IcePillarState::Idle);
	}
	StateChange(BossState::Idle);
}


void ABoss::Boss_IdleStart()
{
	Renderer->ChangeAnimation("Boss_Idle");

	for (int Num = 0; Num < 4; Num++)
	{
		if (IcePillar[Num] == nullptr)
		{
			continue;
		}
		IcePillar[Num]->SetPos({ Bullet_Pos[Num].X, Bullet_Pos[Num].Y });
		IcePillar[Num]->AttackEndFalse();
		IcePillar[Num]->SetActorRotation({ PlRotation[Num] });
	}
}

void ABoss::Boss_Idle(float _DeltaTime)
{
	Boss_Time += _DeltaTime;
	if (Boss_Time > 3.f)
	{
		if (IntroOn == false)
		{
			{
				StateChange(BossState::Intro);
				IntroOn = true;
				Boss_Time = 0.f;
			}
		}
		else if (Regenerate == true)
		{
			for (int Num = 0; Num < 4; Num++)
			{
				if (IcePillar[Num]->ISREgenerate() != true)
				{
					return;
				}
			}
			for (int Num = 0; Num < 4; Num++)
			{
				IcePillar[Num]->StateChange(IcePillarState::Idle);
			}
			Regenerate = false;
		}
		else
		{
			//UEngineInput::IsDown('1')

			if (UEngineInput::IsDown('3'))
			{
				StateChange(BossState::Patton1);
				Boss_Time = 0.f;
			}
			if (UEngineInput::IsDown('4'))
			{
				StateChange(BossState::Patton2);
				Boss_Time = 0.f;
			}
			if (UEngineInput::IsDown('5'))
			{
				StateChange(BossState::Patton3);
				Boss_Time = 0.f;
			}
			if (UEngineInput::IsDown('6'))
			{
				StateChange(BossState::Patton4);
				Boss_Time = 0.f;
			}
			if (UEngineInput::IsDown('7'))
			{
				StateChange(BossState::Patton5);
				Boss_Time = 0.f;
			}
			if (UEngineInput::IsDown('8'))
			{
				SpearCreat = false;
				IceSpear_Aattack();
				Boss_Time = 0.f;
			}


			//Boss_Time += _DeltaTime;
			//if (Boss_Time > 3.f)
			//{
			//	//StateChange(BossState::Patton1);
			//	//StateChange(BossState::Patton2);
			//	//StateChange(BossState::Patton3);
			//	Boss_Time = 0.f;
			//}
		}
	}
}


void ABoss::Boss_Patton1Start()
{	
	for (int Num = 0; Num < 4; Num++)
	{
		if (IcePillar[Num] == nullptr)
		{
			continue;
		}
		IcePillar[Num]->SetPos({ Bullet_Pos[Num].X, Bullet_Pos[Num].Y });
		IcePillar[Num]->AttackEndFalse();
		IcePillar[Num]->SetActorRotation({ PlRotation[Num] });
		IcePillar[Num]->StateChange(IcePillarState::Attack01);
	}
	Attack_Check = true;
	IcePillarPos = 0.f;
	Boss_Time = 0.f;
}
void ABoss::Boss_Patton1(float _DeltaTime)
{
	{			
		if (Attack_Check == true)
		{
			if (IcePillarPos < 7.f)
			{
				IcePillarPos += 50.f * _DeltaTime;
				if (IcePillar[0] != nullptr)
					IcePillar[0]->AddPos({ -IcePillarPos, IcePillarPos / 2 });
				if (IcePillar[1] != nullptr)
					IcePillar[1]->AddPos({ IcePillarPos, IcePillarPos / 2 });
				if (IcePillar[2] != nullptr)
					IcePillar[2]->AddPos({ -IcePillarPos,-IcePillarPos / 1000 });
				if (IcePillar[3] != nullptr)
					IcePillar[3]->AddPos({ IcePillarPos,-IcePillarPos / 1000 });
			}
			else
			{	
				for (int Num = 0; Num < 4; Num++)
				{
					if (IcePillar[Num] == nullptr)
					{
						continue;
					}

					IcePillar[Num]->FireOn();
				}
				Attack_Check = false;
				//IcePillarPos = 0.f;				
			}
		}
		else
		{
			for (int Num = 0; Num < 4; Num++)
			{
				if (IcePillar[Num] == nullptr)
				{
					continue;
				}

				if (true != IcePillar[Num]->IsAttackEnd())
				{
					return;
				}
			}
			for (int Num = 0; Num < 4; Num++)
			{
				if (IcePillar[Num] == nullptr)
				{
					continue;
				}
				IcePillar[Num]->StateChange(IcePillarState::Idle);
			}
			StateChange(BossState::Ready); 
			IcePillarPos = 0.f;
			return;
		}
	}
}

void ABoss::Boss_Patton2Start()
{
	for (int Num = 0; Num < 4; Num++)
	{
		if (IcePillar[Num] == nullptr)
		{
			continue;
		}
		IcePillar[Num]->StateChange(IcePillarState::Attack02);
	}
	Attack_Check = true;
}
void ABoss::Boss_Patton2(float _DeltaTime)
{
	if (Attack_Check == true)
	{
		for (int Num = 0; Num < 4; Num++)
		{
			if (IcePillar[Num] == nullptr)
			{
				continue;
			}
			if (true != IcePillar[Num]->IsAttackEnd())
			{
				return;
			}
		}
		for (int Num = 0; Num < 4; Num++)
		{
			if (IcePillar[Num] == nullptr)
			{
				continue;
			}
			IcePillar[Num]->StateChange(IcePillarState::Idle);
		}
		Attack_Check = false;
		StateChange(BossState::Ready);
	}
}

void ABoss::Boss_Patton3Start()
{
	for (int Num = 0; Num < 4; Num++)
	{
		if (IcePillar[Num] == nullptr)
		{
			continue;
		}
		IcePillar[Num]->SetPos({ Bullet_Pos[Num].X, Bullet_Pos[Num].Y });
		IcePillar[Num]->AttackEndFalse();
		IcePillar[Num]->StateChange(IcePillarState::Attack03);
		IcePillar[Num]->SetActorRotation({ PlRotation[Num] });
	}
	Attack_Check = true;	
	IcePillarPos = 0.f;
}
void ABoss::Boss_Patton3(float _DeltaTime)
{	
	if (Attack_Check == true)
	{	
		if (IcePillarPos < 7.f)
		{
			IcePillarPos += 50.f * _DeltaTime;
			if (IcePillar[0] != nullptr)
			IcePillar[0]->AddPos({ -IcePillarPos, -IcePillarPos * 1.3f });
			if (IcePillar[1] != nullptr)
			IcePillar[1]->AddPos({ IcePillarPos, -IcePillarPos * 1.3f });
			return;
		}
		else
		{
			for (int Num = 0; Num < 4; Num++)
			{
				if (IcePillar[Num] == nullptr)
				{
					continue;
				}
				IcePillar[Num]->FireOn();
			}
			Attack_Check = false;			
		}
	}
	else
	{
		for (int Num = 0; Num < 4; Num++)
		{
			if (IcePillar[Num] == nullptr)
			{
				continue;
			}
			if (true != IcePillar[Num]->IsAttackEnd())
			{
				return;
			}
		}
		for (int Num = 0; Num < 4; Num++)
		{
			if (IcePillar[Num] == nullptr)
			{
				continue;
			}
			IcePillar[Num]->StateChange(IcePillarState::Idle);
		}
		StateChange(BossState::Ready);
		IcePillarPos = 0.f;
		return;
	}
}

void ABoss::Boss_Patton4Start()
{
	for (int Num = 0; Num < 4; Num++)
	{
		if (IcePillar[Num] == nullptr)
		{
			continue;
		}
		IcePillar[Num]->SetPos({ Bullet_Pos[Num].X, Bullet_Pos[Num].Y });
		IcePillar[Num]->AttackEndFalse();
		IcePillar[Num]->SetActorRotation({ PlRotation[Num] });
	}

	for (int Num = 0; Num < 4; Num++)
	{
		if (IcePillar[Num] == nullptr)
		{
			continue;
		}
		IcePillar[Num]->SetPos({ Bullet_Pos[Num].X, Bullet_Pos[Num].Y });
		IcePillar[Num]->AttackEndFalse();
		IcePillar[Num]->StateChange(IcePillarState::Attack04);
		IcePillar[Num]->SetActorRotation({ 0.f,0.f,0.f });
	}
}
void ABoss::Boss_Patton4(float _DeltaTime)
{
	if (Attack_Check == false)
	{
		FVector AttrackDir = Player->GetActorLocation() - GetActorLocation();
		AttrackDir.Normalize2D();
		AttrackDir.Z = 0;
		AttrackDir.X *= UEngineMath::DToR;
		AttrackDir.Y *= UEngineMath::DToR;
		float CursorAngleRad = std::atan2(AttrackDir.Y, AttrackDir.X);
		CursorAngleRad = CursorAngleRad * UEngineMath::RToD;
		//IcePillar[0]->SetActorRotation({ 0.f,0.f,CursorAngleRad - 45.f });
		for (int Num = 0; Num < 4; Num++)
		{
			if (IcePillar[Num] == nullptr)
			{
				continue;
			}
			IcePillar[Num]->SetActorRotation({ 0.f,0.f,CursorAngleRad - 45.f });
		}
		Attack_Check = true;
	}
	else
	{
		for (int Num = 0; Num < 4; Num++)
		{
			if (IcePillar[Num] == nullptr)
			{
				continue;
			}
			if (true != IcePillar[Num]->IsAttackEnd())
			{
				return;
			}
		}
		StateChange(BossState::Ready2);
		Attack_Check = false;
		return;
		//if (UEngineInput::IsDown('1'))
		//{
		//	StateChange(BossState::Idle);
		//	Boss_Time = 0.f;
		//}
	}
}

void ABoss::Boss_Patton5Start()
{
	FVector Setpos = Player->GetActorLocation();
	std::shared_ptr<AIcicle_Bullet> Bullet[4];

	for (int Num = 0; Num < 4; Num++)
	{
		Bullet[Num] = GetWorld()->SpawnActor<AIcicle_Bullet>("IcicleBullet");
		float offset = (Num - 1.5) * 100.f; 
		Bullet[Num]->SetActorLocation({ Setpos.X + offset, Setpos.Y+200, Setpos.Z+1 });
		FVector asd =Bullet[Num]->GetActorLocation();
		Bullet[Num]->AttackOn();
	}
	IcicleCreat = false;
}
void ABoss::IcePallarCheck()
{
	for (int Num = 0; Num < 4; Num++)
	{
		if (IcePillar[Num]->IsDeath() == false)
		{
			return;
		}		
	}
	StateChange(BossState::Fainting);
}

void ABoss::Boss_FaintingStart()
{
	Effect_Renderer->SetActive(true);
	Effect_Renderer->ChangeAnimation("Stun");
	DamageOn = true;
	Boss_Time = 0.f;
}
void ABoss::Boss_Fainting(float _DeltaTime)
{
	std::shared_ptr<UEngineTexture> Tex = UContentsHelper::MapTex;

	#ifdef _DEBUG
		if (nullptr == Tex)
		{
			MsgBoxAssert("이미지 충돌체크중 이미지가 존재하지 않습니다.");
		}
	#endif

	Color8Bit GroundColor;
	Color8Bit SkyUpGRColor;
	Color8Bit SkyGRColor;

	float4 PlayerLocation = GetActorLocation();
	float4 PlayerUpLocation = GetActorLocation();
	if (Foot_Collision_Check_At_Town == true)
	{
		PlayerLocation.Y = -PlayerLocation.Y;
	}
	else
	{
		PlayerLocation.Y = (Tex->GetScale().Y * 64.0f) - PlayerLocation.Y;
		PlayerLocation /= UContentsHelper::TileSize;
		PlayerUpLocation = PlayerLocation;
		PlayerUpLocation.Y = PlayerUpLocation.Y - 1.f;
	}


	GroundColor = Tex->GetColor(PlayerLocation, Color8Bit::Black);
	SkyGRColor = Tex->GetColor(PlayerLocation, Color8Bit::Green);
	SkyUpGRColor = Tex->GetColor(PlayerUpLocation, Color8Bit::Green);



	//if (Color == Color8Bit::Black || SkyGrColor == Color8Bit::Green)
	//{
	//	if (UPColor == Color8Bit::Green)
	//	{
	//		SkyGround = true;
	//		if (State.GetCurStateName() == "Player_Jump")
	//			return;
	//	}
	//	else if (SkyGround == true || Color == Color8Bit::Black)
	//	{
	//		//SkyGround = true;
	//		GravityVector = FVector::Zero;
	//		JumpOn = false;

	//		if (State.GetCurStateName() == "Player_Jump")
	//			SkyGround = false;
	//	}
	//}

	if (GroundColor == Color8Bit::Black|| SkyGRColor == Color8Bit::Green)
	{

		if (SkyUpGRColor == Color8Bit::Green/)
		{				
			return;
		}
		else
		{
			Boss_Time += _DeltaTime;
			if (Boss_Time > 3.5f)
			{
				Boss_Time = 0.f;
				for (int a = 0; a < 4; a++)
				{
					IcePillar[a]->SetPos({ Bullet_Pos[a].X, Bullet_Pos[a].Y });
					IcePillar[a]->AttackEndFalse();
					IcePillar[a]->SetActive(true);
					IcePillar[a]->Regenerate();
				}
				Regenerate = true;
				StateChange(BossState::TeleportOut);
				Effect_Renderer->SetActive(false);
				DamageOn = false;
			}
		}
	}
	else
	{
		GravityVector += GravityAcc * _DeltaTime;
		GravityVector.Z = 0.f;
		FVector Bosspos = GetActorLocation();
		AddActorLocation({ GravityVector * _DeltaTime });
	}
}


void ABoss::Boss_Patton5(float _DeltaTime)
{
	if (IcicleCreat == false)
	{
		FVector Setpos = Player->GetActorLocation();
		std::shared_ptr<AIcicle_Bullet> Bullet[4];

		for (int Num = 0; Num < 4; Num++)
		{
			Bullet[Num] = GetWorld()->SpawnActor<AIcicle_Bullet>("IcicleBullet");
			int offset = (Num - 1.5) * 150;
			Bullet[Num]->SetActorLocation({ Setpos.X + offset, Setpos.Y + 200.f,Setpos.Z + 1 });
			Bullet[Num]->AttackOn();
		}
		IcicleCreat = true;
	}

	if (UEngineInput::IsDown('1'))
	{
		StateChange(BossState::Idle);
		Boss_Time = 0.f;
	}
}

void ABoss::IceSpear_Aattack()
{
	if (SpearCreat == false)
	{
		IceSpear = GetWorld()->SpawnActor<AIceSpear>("IcePillar");
		FVector Setpos = Player->GetActorLocation();
		Setpos.Y -= 35;

		IceSpear->SetActorLocation({ Setpos});
		IceSpear->SetPlayer(Player);
		IceSpear->AttackOn();
		SpearCreat = true;
	}
	
	if (Player->GetActorLocation().X - GetActorLocation().X >= 0.f)
	{
		IceSpear->Attack_Left();
	}
	else
	{
		IceSpear->Attack_Right();
	}
}



void ABoss::Boss_TeleportInStart()
{
	Renderer->ChangeAnimation("Boss_Enter");

	for (int a = 0; a < 4; a++)
	{
		IcePillar[a]->ClearRocation();
		IcePillar[a]->SetPos({ 0.f ,0.f });
	}
	IcePillar[0]->AddPos({ -Bullet,Bullet });
	IcePillar[1]->AddPos({ Bullet,Bullet });
	IcePillar[2]->AddPos({ -Bullet,-Bullet });
	IcePillar[3]->AddPos({ Bullet,-Bullet });

	for (int a = 0; a < 4; a++)
	{
		IcePillar[a]->StateChange(IcePillarState::Regenerate);
	}
}
void ABoss::Boss_TeleportIn(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd() == true)
	{
		for (int a = 0; a < 4; a++)
		{
			if (IcePillar[a]->ISREgenerate() == false)
			{
				return;
			}
		}
		for (int a = 0; a < 4; a++)
		{
			IcePillar[a]->StateChange(IcePillarState::Idle);
		}
		StateChange(BossState::Idle);
	}
}

void ABoss::Boss_TeleportOutStart()
{	
	Renderer->ChangeAnimation("Boss_Exit");
}


void ABoss::Boss_DeathStart()
{
	Renderer->ChangeAnimation("Boss_Die");
}
void ABoss::Boss_Death(float _DeltaTime)
{
}


void ABoss::Boss_TeleportOut(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd() == true)
	{
		float X_Pos = UContentsHelper::Random(MinX_Map_Pos, MaxX_Map_Pos);
		float Y_Pos = UContentsHelper::Random(MinY_Map_Pos, MaxY_Map_Pos);
		float Z_Pos = GetActorLocation().Z;
		SetActorLocation(FVector{ X_Pos , Y_Pos ,Z_Pos });
		StateChange(BossState::TeleportIn);
	}
}


void ABoss::Boss_ReadyStart2()
{
	for (int a = 0; a < 4; a++)
	{
		IcePillar[a]->SetPos({ Bullet_Pos[a].X, Bullet_Pos[a].Y });
		IcePillar[a]->AttackEndFalse();
		IcePillar[a]->SetActorRotation({ PlRotation[a] });
		IcePillar[a]->StateChange(IcePillarState::Idle);
	}
	int a = 0;
}

void ABoss::Boss_Ready2(float _DeltaTime)
{
	for (int a = 0; a < 4; a++)
	{
		IcePillar[a]->SetPos({ Bullet_Pos[a].X, Bullet_Pos[a].Y });
		IcePillar[a]->AttackEndFalse();
		IcePillar[a]->StateChange(IcePillarState::Idle);
	}
	StateChange(BossState::Idle);
	return;
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
		for (int a = 0; a < 4; a++)
		{
			IcePillar[a]->SetPos({ Bullet_Pos[a].X, Bullet_Pos[a].Y });
			IcePillar[a]->AttackEndFalse();
			IcePillar[a]->StateChange(IcePillarState::Idle);
		}
		StateChange(BossState::Idle);
		IcePillarPos = 7.f;
		return;
	}
}



void ABoss::CreateIcePillar()
{
	for (int Num = 0; Num < 4; Num++)
	{
		IcePillar[Num] = GetWorld()->SpawnActor<ABoss_IcePillar>("IcePillar");
		IcePillar[Num]->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	}
	
	//IcePillarPosSetting();
}

void ABoss::IcePillarPosSetting()
{
	IcePillar[0]->AddPos({ -Bullet,Bullet });
	IcePillar[1]->AddPos({ Bullet,Bullet });
	IcePillar[2]->AddPos({ -Bullet,-Bullet });
	IcePillar[3]->AddPos({ Bullet,-Bullet });

	for (int Num = 0; Num < 4; Num++)
	{
		PlRotation[Num] = IcePillar[Num]->GetActorTransform().GetRotation();
		Bullet_Pos[Num] = IcePillar[Num]->GetPos();
		IcePillar[Num]->StateChange(IcePillarState::Intro);
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
