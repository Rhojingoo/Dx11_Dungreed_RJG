#pragma once
#include <EngineCore/Actor.h>

enum class Iciclestate
{
	Effect,
	Icicle,
	Collision,
	Attack,
};

class UCollision;
class APlayer;
class UDefaultSceneComponent;
class USpriteRenderer;
class AIcicle_Bullet : public AActor
{
	GENERATED_BODY(AActor)
public:
	AIcicle_Bullet();
	~AIcicle_Bullet();

	AIcicle_Bullet(const AIcicle_Bullet& _Other)					= delete;
	AIcicle_Bullet(AIcicle_Bullet& _Other) noexcept					= delete;
	AIcicle_Bullet& operator =(const 	AIcicle_Bullet& _Other)		= delete;
	AIcicle_Bullet& operator =(AIcicle_Bullet& _Other)noexcept		= delete;

	void SetPlayer(std::shared_ptr<APlayer> _Set) { Player = _Set; };
	void AttackOn();

	void BombBullet() { ChangeState(Iciclestate::Collision); }
	float Getdamage();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Effect(float _DeltaTime);
	void EffectStart();

	void Spear(float _DeltaTime);
	void SpearStart();

	void Attack(float _DeltaTime);
	void AttackStart();

	void ColEnterStart();
	void ColEnter(float _DeltaTime);


	void ChangeState(Iciclestate _Set);
	void StateUpdate(float _DeltaTime);

private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* EffectRenderer = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	UCollision* Collision = nullptr;
	Iciclestate Icicle_state = Iciclestate::Effect;


	bool Attack_Start = false;
	bool EffectEnd = false;
	float Speed = 5.f;
	FVector AttPos = {};
	float Destroy_Time = 0.f;

	float Damage = 0.f;
	const float MaxDamage = 15.f;
	const float MinDamage = 10.f;
};

