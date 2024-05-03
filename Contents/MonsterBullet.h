#pragma once
#include <EngineCore/Actor.h>

enum class BulletState
{
	None,
	Attack,
	Collision,
	End,
};


class UCollision;
class UDefaultSceneComponent;
class USpriteRenderer;
class AMonsterBullet : public AActor
{
	GENERATED_BODY(AActor)
public:
	AMonsterBullet();
	~AMonsterBullet();

	AMonsterBullet(const AMonsterBullet& _Other) = delete;
	AMonsterBullet(AMonsterBullet& _Other) noexcept = delete;
	AMonsterBullet& operator =(const 	AMonsterBullet& _Other) = delete;
	AMonsterBullet& operator =(AMonsterBullet& _Other)noexcept = delete;

	void SetTarget(FVector _Set) { TargetPos = _Set; }
	void SetNomalTarget(FVector _Set) { TargetNomalPos = _Set; }
	void TargetOn() { TargetSwitch = true; }

	bool IsFire() { return Fire; }
	void FireOn() { Fire = true; }
	void FireOff() { Fire = false; }
	void FireSecondBullet() { OtherBulletFire = true, TargetSwitch = true; }

	void BombBullet() { ChangeState(BulletState::Collision); }
	float Getdamage();
	void IceBullet() { Renderer->ChangeAnimation("IceBat_Bullet"); }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void AttackStart();
	void Attack(float _DeltaTime);

	void ColEnterStart();
	void ColEnter(float _DeltaTime);

	void ChangeState(BulletState _Set);
	void StateUpdate(float _DeltaTime);

private:
	BulletState Bullet_State = BulletState::Attack;
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* EffectRenderer = nullptr;
	UCollision* Collision = nullptr;
	FVector TargetPos = {};
	FVector TargetNomalPos = {};
	bool TargetSwitch = false;
	float Speed = 35.f;

	bool Fire = false;
	bool OtherBulletFire = false;
	float DestroyTime = 0.f;

	float Damage = 0.f;
	const float MaxDamage = 10.f;
	const float MinDamage = 5.f;
};


