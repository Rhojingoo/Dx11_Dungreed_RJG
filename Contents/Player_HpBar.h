#pragma once
#include <EngineCore/Actor.h>

class UImage;
class USpriteRenderer;
class APlayer_HpBar : public AActor
{
	GENERATED_BODY(AActor)
public:
	APlayer_HpBar();
	~APlayer_HpBar();

	// delete Function
	APlayer_HpBar(const APlayer_HpBar& _Other) = delete;
	APlayer_HpBar(APlayer_HpBar&& _Other) noexcept = delete;
	APlayer_HpBar& operator=(const APlayer_HpBar& _Other) = delete;
	APlayer_HpBar& operator=(APlayer_HpBar&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImage* PlayerLifeBase = nullptr;
	UImage* PlayerLifeBack = nullptr;
	UImage* LifeBar = nullptr;
	UImage* LifeBarWave = nullptr;

	const float MaxLife = 200.f;
	float Life = MaxLife;

	const float Life_POSX = -410.f;
	float LifePos = Life_POSX;

	bool EnergyDown = false;
};

