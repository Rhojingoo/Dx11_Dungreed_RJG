#pragma once
#include <EngineCore/Actor.h>

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
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Effect_AttackStart();
	void Effect_Attack(float _DeltaTime);

	void Effect_EndStart();
	void Effect_End(float _DeltaTime);

	void ChangeState(AttackState _Set);
	void StateUpdate(float _DeltaTime);

private:
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	AttackState WapponState = AttackState::None;
	bool Attack = false;
	float4 Color;
};

