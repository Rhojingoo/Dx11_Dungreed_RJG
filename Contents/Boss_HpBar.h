#pragma once
#include <EngineCore/Actor.h>


class UImage;
class Boss_HpBar : public AActor
{
	GENERATED_BODY(AActor)
public:
	Boss_HpBar();
	~Boss_HpBar();

	Boss_HpBar(const Boss_HpBar& _Other)					= delete;
	Boss_HpBar(Boss_HpBar& _Other) noexcept					= delete;
	Boss_HpBar& operator =(const 	Boss_HpBar& _Other)		= delete;
	Boss_HpBar& operator =(Boss_HpBar& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImage* BossLifeBase = nullptr;
	UImage* BossLifeBack = nullptr;
	UImage* LifeBar = nullptr;

	const float MaxLife = 200.f;
	float Life = MaxLife;

	const float Life_POSX = -410.f;
	float LifePos = Life_POSX;
};

