#pragma once
#include <EngineCore/Actor.h>

class UCollision;
class ASkeleton_ATKCOL : public AActor
{
	GENERATED_BODY(AActor)
public:
	ASkeleton_ATKCOL();
	~ASkeleton_ATKCOL();

	ASkeleton_ATKCOL(const ASkeleton_ATKCOL& _Other)					= delete;
	ASkeleton_ATKCOL(ASkeleton_ATKCOL& _Other) noexcept					= delete;
	ASkeleton_ATKCOL& operator =(const 	ASkeleton_ATKCOL& _Other)		= delete;
	ASkeleton_ATKCOL& operator =(ASkeleton_ATKCOL& _Other)noexcept		= delete;

	float Getdamage();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UCollision* Collision = nullptr;

	float Damage = 0.f;
	const float MaxDamage = 15.f;
	const float MinDamage = 10.f;
};

