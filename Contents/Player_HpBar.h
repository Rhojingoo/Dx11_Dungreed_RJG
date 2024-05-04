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

	void SetRatio(float _Set) { EnergyDown = true, ratio = _Set; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImage* PlayerPicture = nullptr;
	UImage* PlayerLifeBase = nullptr;
	UImage* PlayerLifeBack = nullptr;
	UImage* LifeBar = nullptr;
	UImage* LifeBarWave = nullptr;

	bool EnergyDown = false;
	static bool WaveHp;
	float ratio = 0.f;
	const float MaxLife = 200.f;
	static float Life;
	const float Life_POSX = -410.f;
	static float LifePos;


};

