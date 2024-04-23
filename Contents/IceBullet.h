#pragma once
#include <EngineCore/Actor.h>

enum class IceBulletState
{
	None,
	Attack,
	Collision,
	End,
};


class UCollision;
class UDefaultSceneComponent;
class USpriteRenderer;
class AIceBullet : public AActor
{
	GENERATED_BODY(AActor)
public:
	AIceBullet();
	~AIceBullet();

	AIceBullet(const AIceBullet& _Other)					= delete;
	AIceBullet(AIceBullet& _Other) noexcept					= delete;
	AIceBullet& operator =(const 	AIceBullet& _Other)		= delete;
	AIceBullet& operator =(AIceBullet& _Other)noexcept		= delete;

	void SetTarget(FVector _Set) { TargetPos = _Set; }
	void SetNomalTarget(FVector _Set) { TargetNomalPos = _Set; }
	void TargetOn() { TargetSwitch = true; }

	bool IsFire() { return Fire; }
	void FireOn() { Fire = true; }
	void FireOff() { Fire = false; }
	void FireSecondBullet() { OtherBulletFire = true, TargetSwitch = true; }
	
	void BombBullet() { ChangeState(IceBulletState::Collision); }


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void AttackStart();
	void Attack(float _DeltaTime);

	void ColEnterStart();
	void ColEnter(float _DeltaTime);

	void ChangeState(IceBulletState _Set);
	void StateUpdate(float _DeltaTime);

private:
	IceBulletState IceState = IceBulletState::Attack;
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	FVector TargetPos = {};
	FVector TargetNomalPos = {};
	bool TargetSwitch = false;
	float Speed = 200.f;

	bool Fire = false;
	bool OtherBulletFire = false;	
	float DestroyTime = 0.f;
};

