#pragma once
#include <EngineCore/Actor.h>

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
	void TargetOn() { TargetSwitch = true; }

	bool IsFire() { return Fire; }
	void FireOn() { Fire = true; }
	void FireOff() { Fire = false; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;
	FVector TargetPos = {};
	bool TargetSwitch = false;
	float Speed = 150.f;

	bool Fire = false;
};

