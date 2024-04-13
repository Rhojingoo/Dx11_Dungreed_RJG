#pragma once
#include <EngineCore/Actor.h>

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

	void AttackOn() { Attack = true; }
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* Renderer = nullptr;

	bool Attack = false;
	float4 Color;
};

