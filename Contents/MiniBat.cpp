#include "PreCompile.h"
#include "MiniBat.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>
#include "Player.h"
#include "MonsterBullet.h"
#include "Monster_HpBar.h"
#include "Player_Attack_Effect.h"


AMiniBat::AMiniBat()
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


	SetRoot(Root);
}

AMiniBat::~AMiniBat()
{
}

void AMiniBat::BeginPlay()
{
	Super::BeginPlay();
	Renderer->CreateAnimation("IceBat_Idle", "IceBat_Idle", 0.1f);
	Renderer->CreateAnimation("IceBat_Attack", "IceBat_Attack", 0.1f, false);
	Renderer->SetAutoSize(3.f, true);
	Renderer->ChangeAnimation("IceBat_Idle");
	Renderer->SetOrder(ERenderOrder::Monster);

	EffectRenderer->CreateAnimation("Die_Effect", "Die_Effect", 0.1f, false);
	EffectRenderer->SetOrder(ERenderOrder::Boss_IceBullet_Effect);
	EffectRenderer->SetAutoSize(4.f, true);

	Hp_Bar = GetWorld()->SpawnActor<AMonster_HpBar>("IcePillar_HP");
	Hp_Bar->SetActorLocation({ 1040.0f, -850.0f, 201.f });
}

void AMiniBat::Tick(float _DeltaTime)
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
	//Collision->SetPosition({ Renderer->GetWorldPosition() * 0.0001f });
}

void AMiniBat::IdleStart()
{
	Renderer->ChangeAnimation("IceBat_Idle");
}
void AMiniBat::Left(float _DeltaTime)
{
}
void AMiniBat::LeftStart()
{
}
void AMiniBat::Right(float _DeltaTime)
{
}
void AMiniBat::RightStart()
{
}
void AMiniBat::Idle(float _DeltaTime)
{
	Time += _DeltaTime;
	if (Time > 3.0f)
	{
		ChangeState(MonsterState::Attack);
		Time = 0.f;
		AttackDirSet = false;
	}
}

void AMiniBat::AttackStart()
{
	Renderer->ChangeAnimation("IceBat_Attack");
	if (AttackDirSet == false)
	{
		BulletDir = RenderPos - PlayerPos;
		AttackDirSet = true;
	}
	CreatBullet(BulletDir, Renderer->GetWorldPosition());
}

void AMiniBat::Attack(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd() == true)
	{
		ChangeState(MonsterState::Idle);
		AttackDirSet = false;
	}
}

void AMiniBat::DeathStart()
{
	EffectRenderer->ChangeAnimation("Die_Effect");
	Renderer->SetActive(false);
	MonsterDie = true;
}
void AMiniBat::Death(float _DeltaTime)
{
	if (EffectRenderer->IsCurAnimationEnd() == true)
	{
		Destroy();
	}
}

void AMiniBat::ChangeState(MonsterState _Set)
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

void AMiniBat::StateUpdate(float _DeltaTime)
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

void AMiniBat::CollisionCheck_Function()
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

void AMiniBat::Direction()
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

void AMiniBat::CreatBullet(FVector _Dir, FVector _Pos)
{
	std::shared_ptr<AMonsterBullet> Bullet = GetWorld()->SpawnActor<AMonsterBullet>("Monster_Bullet");
	Bullet->IceBullet();
	Bullet->SetActorLocation(_Pos);
	_Dir.Z = 0;
	_Dir.X *= UEngineMath::DToR;
	_Dir.Y *= UEngineMath::DToR;
	Bullet->SetTarget(-_Dir);
	Bullet->FireSecondBullet();	
}

