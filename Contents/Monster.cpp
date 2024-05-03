#include "PreCompile.h"
#include "Monster.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}



float AMonster::Getdamage()
{
    return 0.0f;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}



void AMonster::ChangeState(MonsterState _Set)
{
	switch (_Set)
	{
	case MonsterState::Idle:
		IdleStart();
		break;
	case MonsterState::Left:
		LeftStart();
		break;
	case MonsterState::Right:
		RightStart();
		break;
	case MonsterState::Move:
		MoveStart();
		break;
	case MonsterState::Attack:
		AttackStart();
		break;
	default:
		break;
	}
}

void AMonster::StateUpdate(float _DeltaTime)
{
	switch (Monster_state)
	{
	case MonsterState::Idle:
		Idle(_DeltaTime);
		break;
	case MonsterState::Left:
		Left(_DeltaTime);
		break;
	case MonsterState::Right:
		Right(_DeltaTime);
		break;
	case MonsterState::Move:
		Move(_DeltaTime);
		break;
	case MonsterState::Attack:
		Attack(_DeltaTime);
		break;
	default:
		break;
	}
}

void AMonster::CollisionCheck_Function()
{

}
