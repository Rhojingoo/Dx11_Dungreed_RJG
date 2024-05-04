#include "PreCompile.h"
#include "Skeleton.h"
#include "Player.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "Monster_HpBar.h"
#include "Player_Attack_Effect.h"


ASkeleton::ASkeleton()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);


	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(EColOrder::Monster_AttackCol);
	Collision->SetCollisionType(ECollisionType::RotRect);
	Collision->SetScale(FVector(66.0f, 60.0f));

	PlayerCheckCollision = CreateDefaultSubObject<UCollision>("Collision");
	PlayerCheckCollision->SetupAttachment(Root);
	PlayerCheckCollision->SetCollisionGroup(EColOrder::Monster);
	PlayerCheckCollision->SetCollisionType(ECollisionType::RotRect);
	PlayerCheckCollision->SetScale(FVector(66.0f, 60.0f) * 4.0f); // 탐지 범위 설정.

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	EffectRenderer->SetupAttachment(Root);
	EffectRenderer->AddPosition({ 0.f,25.f,0.f });

	SetRoot(Root);
}

ASkeleton::~ASkeleton()
{
}

void ASkeleton::BeginPlay()
{
	Super::BeginPlay();
	Renderer->CreateAnimation("Skeleton_Idle", "Skul_Idle.png", 0.1f, true);
	Renderer->CreateAnimation("Skeleton_Run", "Skul_Run.png", 0.1f, true, 0, 6);
	Renderer->CreateAnimation("Skeleton_Attack", "Skul_Attack.png", 0.1f, true);
	Renderer->SetOrder(ERenderOrder::Monster);
	Renderer->SetAutoSize(2.0f, true);
	Renderer->SetDir(EEngineDir::Right);

	EffectRenderer->CreateAnimation("Die_Effect", "Die_Effect", 0.1f, false);
	EffectRenderer->SetOrder(ERenderOrder::Boss_IceBullet_Effect);
	EffectRenderer->SetAutoSize(4.f, true);

	Hp_Bar = GetWorld()->SpawnActor<AMonster_HpBar>("IcePillar_HP");
	Hp_Bar->SetActorLocation({ 1040.0f, -850.0f, 201.f });

	Renderer->ChangeAnimation("Skeleton_Idle");
}

void ASkeleton::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Pos = GetActorLocation();
	RenderPos = Renderer->GetWorldPosition();
	Hp_Bar->SetActorLocation(RenderPos);
	StateUpdate(_DeltaTime);
	if (Player != nullptr)
	{
		PlayerPos = Player->GetActorLocation();
	}
		
	CollisionCheck_Function(_DeltaTime);
}

void ASkeleton::IdleStart()
{
	Renderer->ChangeAnimation("Skeleton_Idle");	
	PlayerNotCatchTime = 0.0f;
}

void ASkeleton::Idle(float _DeltaTime)
{
	PlayerNotCatchTime += _DeltaTime;

	CollisionCheck_Function(PlayerNotCatchTime);

	if (1.0f <= PlayerNotCatchTime)
	{
		if (AttackOn == true)
		{
			ChangeState(MonsterState::Attack);
			PlayerNotCatchTime = 0.0f;
			return;
		}
		ChangeState(MonsterState::Move);
		PlayerNotCatchTime = 0.0f;		
		return;
	}
}


void ASkeleton::MoveStart()
{
	Renderer->ChangeAnimation("Skeleton_Run");

	if (EEngineDir::Right == Renderer->GetDir())
	{
		Renderer->SetDir(EEngineDir::Left);		
	}
	else
	{
		Renderer->SetDir(EEngineDir::Right);
	}	

	RunTime = 0.0f;
}

void ASkeleton::Move(float _DeltaTime)
{
	RunTime += _DeltaTime;
	FVector V_Run = FVector::Zero;

	CollisionCheck_Function( _DeltaTime);

	SideWallCheck();

	if (EEngineDir::Right == Renderer->GetDir())
	{
		if (SideColor == Color8Bit::Black)
		{
			ChangeState(MonsterState::Idle);
			RunTime = 0.0f;
			return;
		}
		V_Run = FVector::Right * RumSpeed * _DeltaTime;
		AddActorLocation(V_Run);
	}
	else
	{
		if (SideColor == Color8Bit::Black)
		{
			ChangeState(MonsterState::Idle);
			RunTime = 0.0f;
			return;
		}
		V_Run = FVector::Left * RumSpeed * _DeltaTime;
		AddActorLocation(V_Run);
	}

	if (1.0f <= RunTime)
	{
		ChangeState(MonsterState::Idle);
		RunTime = 0.0f;	
		return;
	}
}



void ASkeleton::AttackStart()
{
	Renderer->ChangeAnimation("Skeleton_Attack");
	UEngineSound::SoundPlay("weapon-sound8.wav");
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
void ASkeleton::Attack(float _DeltaTime)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState(MonsterState::Idle);
		return;
	}
}



void ASkeleton::Death(float _DeltaTime)
{
	if (EffectRenderer->IsCurAnimationEnd() == true)
	{
		Destroy();
	}	
}

void ASkeleton::DeathStart()
{
	EffectRenderer->ChangeAnimation("Die_Effect");
	Renderer->SetActive(false);
	MonsterDie = true;
	UEngineSound::SoundPlay("MonsterDie.wav");
}


void ASkeleton::CollisionCheck_Function(float _DeltaTime)
{
	Collision->CollisionEnter(EColOrder::Wapon, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			APlayer_Attack_Effect* Wapon = dynamic_cast<APlayer_Attack_Effect*>(Actors);
			if (Wapon != nullptr)
			{
				float Damage = Wapon->AttackDamage();
				Hp -= Damage;
				float Damageratio = Hp / MaxHp;
				if (Hp <= 0.f)
				{
					PlayerCheckCollision->SetScale({ 0.f, 0.f, 0.f });
					PlayerCheckCollision->SetActive(false);
					ChangeState(MonsterState::Death);
					Damageratio = 0;
					Hp_Bar->AttackDamege(0);
					return;
				}
				Hp_Bar->AttackDamege(Damageratio);
				UEngineSound::SoundPlay("Hit_Monster.wav");
			}
		}
	);

	PlayerCheckCollision->CollisionEnter(EColOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
	{
		AttackOn = true;
		ChangeState(MonsterState::Attack);
		return;
	}
	);
	PlayerCheckCollision->CollisionExit(EColOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
		{
			AttackOn = false;
			return;
		}
	);
}

void ASkeleton::Direction()
{
}

void ASkeleton::SideWallCheck()
{
	std::shared_ptr<UEngineTexture> Tex = UContentsHelper::MapTex;

#ifdef _DEBUG
	if (nullptr == Tex)
	{
		MsgBoxAssert("이미지 충돌체크중 이미지가 존재하지 않습니다.");
	}
#endif

	float4 SideCheck = GetActorLocation();
	SideCheck.Y = (Tex->GetScale().Y * 64.0f) - SideCheck.Y - 15.f;
	SideCheck /= UContentsHelper::TileSize;

	if (EEngineDir::Left == Renderer->GetDir())
	{
		SideCheck.X = SideCheck.X - 0.5f;
	}
	else
	{
		SideCheck.X = SideCheck.X + 0.5f;
	}
	SideColor = Tex->GetColor(SideCheck, Color8Bit::Black);
}

void ASkeleton::StateUpdate(float _DeltaTime)
{
	switch (Monster_state)
	{
	case MonsterState::Idle:
		Idle(_DeltaTime);
		break;
	case MonsterState::Move:
		Move(_DeltaTime);
		break;
	case MonsterState::Attack:
		Attack(_DeltaTime);
		break;
	case MonsterState::Death:
		Death(_DeltaTime);
		break;
	default:
		break;
	}
}

void ASkeleton::ChangeState(MonsterState _Set)
{
	if (Monster_state != _Set)
	{
		switch (_Set)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Move:
			MoveStart();
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		case MonsterState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	Monster_state = _Set;
}
