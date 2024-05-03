#pragma once
#include "Monster.h"

class AMonster_HpBar;
class ARedGinatBat : public AMonster
{
	GENERATED_BODY(AMonster)
public:
	ARedGinatBat();
	~ARedGinatBat();

	// delete Function
	ARedGinatBat(const ARedGinatBat& _Other) = delete;
	ARedGinatBat(ARedGinatBat&& _Other) noexcept = delete;
	ARedGinatBat& operator=(const ARedGinatBat& _Other) = delete;
	ARedGinatBat& operator=(ARedGinatBat&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Idle(float _DeltaTime)override;
	void IdleStart()override;

	//void Left(float _DeltaTime)override;
	//void LeftStart()override;

	//void Right(float _DeltaTime)override;
	//void RightStart()override;

	//void Move(float _DeltaTime)override;
	//void MoveStart()override;

	void Attack(float _DeltaTime)override;
	void AttackStart()override;

	void Death(float _DeltaTime) override;
	void DeathStart() override;
	
	void ChangeState(MonsterState _Set)override;
	void StateUpdate(float _DeltaTime)override;



	void CollisionCheck_Function()override;

	void Direction();
	void CreatBullet(FVector _Dir, FVector _Pos);
	void SetBulletPos();

private:
	float Time = 0.f;
	std::shared_ptr<AMonster_HpBar> Hp_Bar = nullptr;

	FVector Pos = {};
	FVector RenderPos = {};
	FVector PlayerPos = {};
	FVector BulletDir = {};
	FVector TargetPos[8] = {};

	bool AttackDirSet = false;

	const float MaxHp = 1000.f;
	float Hp = MaxHp;

};

