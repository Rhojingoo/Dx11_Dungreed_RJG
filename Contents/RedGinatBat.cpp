#include "PreCompile.h"
#include "RedGinatBat.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>
#include "Player.h"
#include "MonsterBullet.h"
#include "Monster_HpBar.h"
#include "Player_Attack_Effect.h"


ARedGinatBat::ARedGinatBat()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionGroup(EColOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
	Collision->SetCollisionGroup(EColOrder::Monter_Bullet);

	EffectRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	EffectRenderer->SetupAttachment(Root);

	SetBulletPos();
	SetRoot(Root);
}

ARedGinatBat::~ARedGinatBat()
{
}

void ARedGinatBat::BeginPlay()
{
	Super::BeginPlay();
	Renderer->CreateAnimation("RedGiantBat_Idle", "RedGiantBat_Idle", 0.1f);
	Renderer->CreateAnimation("RedGiantBat_Attack", "RedGiantBat_Attack", 0.1f, false);
	Renderer->SetAutoSize(3.f, true);
	Renderer->ChangeAnimation("RedGiantBat_Idle");
	Renderer->SetOrder(ERenderOrder::Monster);

	EffectRenderer->CreateAnimation("Die_Effect", "Die_Effect", 0.1f, false);
	EffectRenderer->SetOrder(ERenderOrder::Boss_IceBullet_Effect);
	EffectRenderer->SetAutoSize(4.f, true);

	Hp_Bar = GetWorld()->SpawnActor<AMonster_HpBar>("IcePillar_HP");
	Hp_Bar->SetActorLocation({ 1040.0f, -850.0f, 201.f });
}

void ARedGinatBat::Tick(float _DeltaTime)
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

	Direction();
	CollisionCheck_Function();
	Collision->SetPosition({ Renderer->GetWorldPosition() * 0.0001f });
}

void ARedGinatBat::IdleStart()
{
	Renderer->ChangeAnimation("RedGiantBat_Idle");
}
void ARedGinatBat::Idle(float _DeltaTime)
{
	Time += _DeltaTime;
	if (Time > 3.0f)
	{
		ChangeState(MonsterState::Attack);
		Time = 0.f;
	}
}


void ARedGinatBat::AttackStart()
{
	Renderer->ChangeAnimation("RedGiantBat_Attack");

	if (AttackDirSet == false)
	{
		BulletDir = RenderPos - PlayerPos;
		AttackDirSet = true;
	}
	for (int Num = 0; Num < 8; Num++)
	{		
		CreatBullet(BulletDir, (Renderer->GetWorldPosition()+ TargetPos[Num]));
	}
	
}
void ARedGinatBat::Attack(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd() == true)
	{
		ChangeState(MonsterState::Idle);
	}
}


void ARedGinatBat::DeathStart()
{
	EffectRenderer->ChangeAnimation("Die_Effect");
	Renderer->SetActive(false);
	MonsterDie = true;
}
void ARedGinatBat::Death(float _DeltaTime)
{
	if (EffectRenderer->IsCurAnimationEnd() == true)
	{
		Destroy();
	}
}

void ARedGinatBat::ChangeState(MonsterState _Set)
{
	if (Monster_state != _Set)
	{
		switch (_Set)
		{
		case MonsterState::Idle:
			IdleStart();
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

void ARedGinatBat::StateUpdate(float _DeltaTime)
{
	switch (Monster_state)
	{
	case MonsterState::Idle:
		Idle(_DeltaTime);
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

void ARedGinatBat::CollisionCheck_Function()
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
					ChangeState(MonsterState::Death);
					Damageratio = 0;
					Hp_Bar->AttackDamege(0);
					return;
				}
				Hp_Bar->AttackDamege(Damageratio);
			}
		}
	);
}

void ARedGinatBat::Direction()
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

void ARedGinatBat::CreatBullet(FVector _Dir, FVector _Pos)
{
	std::shared_ptr<AMonsterBullet> Bullet = GetWorld()->SpawnActor<AMonsterBullet>("Monster_Bullet");

	Bullet->SetActorLocation(_Pos);
	_Dir.Z = 0;
	_Dir.X *= UEngineMath::DToR;
	_Dir.Y *= UEngineMath::DToR;
	Bullet->SetTarget(-_Dir);
	Bullet->FireSecondBullet();
}

void ARedGinatBat::SetBulletPos()
{
	TargetPos[0] = FVector{ 0.f,150.f,0.f };
	TargetPos[1] = FVector{ 100.f,100.f,0.f };
	TargetPos[2] = FVector{ 150.f,0.f,0.f };
	TargetPos[3] = FVector{ 100.f,-100.f,0.f };
	TargetPos[4] = FVector{ 0.f,-150.f,0.f };
	TargetPos[5] = FVector{ -100.f,-100.f,0.f };
	TargetPos[6] = FVector{ -150.f,0.f,0.f };
	TargetPos[7] = FVector{ -100.f,100.f,0.f };
}

