#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform\EngineSound.h>

enum class Sword_Type
{
	None,
	Demon_Sword,
	Demon_Blade,
	AttackEnd,
};


enum class AttackState
{
	None,
	Attack,
	AttackEnd,
};

class UCollision;
class USpriteRenderer;
class APlayer_Attack_Effect : public AActor
{
	GENERATED_BODY(AActor)
public:
	APlayer_Attack_Effect();
	~APlayer_Attack_Effect();

	APlayer_Attack_Effect(const APlayer_Attack_Effect& _Other)					= delete;
	APlayer_Attack_Effect(APlayer_Attack_Effect& _Other) noexcept					= delete;
	APlayer_Attack_Effect& operator =(const 	APlayer_Attack_Effect& _Other)		= delete;
	APlayer_Attack_Effect& operator =(APlayer_Attack_Effect& _Other)noexcept		= delete;

	void AttackOn() 
	{ 
		Attack = true;	
	}
	float AttackDamage() { return Sword_Damage; }
	static void SwordEffectType_Choice(Sword_Type _Set);


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Effect_AttackStart();
	void Effect_Attack(float _DeltaTime);

	void Effect_EndStart();
	void Effect_End(float _DeltaTime);

	void ChangeState(AttackState _Set);
	void StateUpdate(float _DeltaTime);
	void CollisionCheck_Function();

private:
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	AttackState WapponState = AttackState::None;
	static Sword_Type SwordType;
	bool Attack = false;
	float4 Color;

	const float DemonSword_MaxDamage = 140.f;
	const float DemonSword_MinDamage = 125.f;

	const float DemonBlade_MaxDamage = 220.f;
	const float DemonBlade_MinDamage = 150.f;

	float Sword_Damage = 50.f;

};

