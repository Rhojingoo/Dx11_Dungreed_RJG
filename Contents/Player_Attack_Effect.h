#pragma once
#include <EngineCore/Actor.h>

enum class Sword_Type
{
	None,
	Lasli_Sword,
	Fire_Sword,
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
	float AttackDamage() { return Lasli_Sword_Damage; }
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Effect_AttackStart();
	void Effect_Attack(float _DeltaTime);

	void Effect_EndStart();
	void Effect_End(float _DeltaTime);

	void ChangeState(AttackState _Set);
	void StateUpdate(float _DeltaTime);


	void SwordType_Choice();
	void SwordType_Update();
	void ChangeSwordType(Sword_Type _Set);
	void FireSword_Choice();
	void FireSword_ChoiceStart();
	void LasliSword_Choice();
	void LasliSword_ChoiceStart();
	void CollisionCheck_Function();

private:
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	AttackState WapponState = AttackState::None;
	static Sword_Type SwordType;
	bool Attack = false;
	float4 Color;

	float Lasli_Sword_Damage = 100.f;
	float Fire_Sword_Damage = 100.f;
};

