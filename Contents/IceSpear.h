#pragma once
#include <EngineCore/Actor.h>


enum class Spearstate
{
	Effect,
	Spear,
	Attack,
};

class UCollision;
class APlayer;
class UDefaultSceneComponent;
class USpriteRenderer;
class AIceSpear : public AActor
{
	GENERATED_BODY(AActor)

public:
	AIceSpear();
	~AIceSpear();

	AIceSpear(const AIceSpear& _Other)					= delete;
	AIceSpear(AIceSpear& _Other) noexcept					= delete;
	AIceSpear& operator =(const 	AIceSpear& _Other)		= delete;
	AIceSpear& operator =(AIceSpear& _Other)noexcept		= delete;

	void SetPlayer(std::shared_ptr<APlayer> _Set) { Player = _Set; };
	void AttackOn();
	void Attack_Right() 
	{ 
		RightAttack = true; 
		EffectRenderer->SetDir(EEngineDir::Right);
		Renderer->SetDir(EEngineDir::Right);
		Renderer->AddPosition({ -500.f,0.f });
	}
	void Attack_Left()
	{
		LeftAttack = true;
		EffectRenderer ->SetDir(EEngineDir::Left);
		Renderer->SetDir(EEngineDir::Left);
		Renderer->AddPosition({ 500.f,0.f });
	}

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

	void ChangeState(Spearstate _Set);
	void StateUpdate(float _DeltaTime);

private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* EffectRenderer = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	UCollision* Collision = nullptr;
	Spearstate Spear_state = Spearstate::Effect;

	bool Attack_Start = false;
	bool EffectEnd = false;
	float Speed = 50.f;
	FVector AttPos = {};
	bool RightAttack = false;
	bool LeftAttack = false;
	float Destroy_Time = 0.f;

	float Damage = 0.f;
	const float MaxDamage = 30.f;
	const float MinDamage = 20.f;
};

