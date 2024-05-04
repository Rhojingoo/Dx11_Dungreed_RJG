#pragma once
#include <EngineCore/Actor.h>
#include "Monster.h"

class ASkeleton_ATKCOL;
class UCollision;
class AMonster_HpBar;
class ASkeleton : public AMonster
{
	GENERATED_BODY(AMonster)
public:
	// constrcuter destructer
	ASkeleton();
	~ASkeleton();

	// delete Function
	ASkeleton(const ASkeleton& _Other) = delete;
	ASkeleton(ASkeleton&& _Other) noexcept = delete;
	ASkeleton& operator=(const ASkeleton& _Other) = delete;
	ASkeleton& operator=(ASkeleton&& _Other) noexcept = delete;
	

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime)override;
	void IdleStart()override;

	void Move(float _DeltaTime)override;
	void MoveStart()override;

	void Attack(float _DeltaTime)override;
	void AttackStart()override;

	void Death(float _DeltaTime) override;
	void DeathStart() override;

	void ChangeState(MonsterState _Set)override;
	void StateUpdate(float _DeltaTime)override;

	void CollisionCheck_Function(float _DeltaTime);

	void Direction();
	void SideWallCheck();
private :
	std::shared_ptr<AMonster_HpBar> Hp_Bar = nullptr;
	std::shared_ptr<ASkeleton_ATKCOL> MonAt_COL = nullptr;
	

	UCollision* PlayerCheckCollision = nullptr;

	FVector Pos = {};
	FVector RenderPos = {};
	FVector PlayerPos = {};
	FVector BulletDir = {};
	FVector TargetNomalPos = {};

	const float RumSpeed = 150.0f;
	FVector MoveVector = FVector::Zero;
	float PlayerNotCatchTime = 0.0f;
	float RunTime = 0.0f;
	bool AttackOn = false;

	Color8Bit SideColor;
	const float MaxHp = 1200.f;
	float Hp = MaxHp;
};

