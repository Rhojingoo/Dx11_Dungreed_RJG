#pragma once
#include <EngineCore/Actor.h>


class UImage;
class ABoss_HpBar : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABoss_HpBar();
	~ABoss_HpBar();

	ABoss_HpBar(const ABoss_HpBar& _Other)					= delete;
	ABoss_HpBar(ABoss_HpBar& _Other) noexcept					= delete;
	ABoss_HpBar& operator =(const 	ABoss_HpBar& _Other)		= delete;
	ABoss_HpBar& operator =(ABoss_HpBar& _Other)noexcept		= delete;

	void AttackDamege(float _Set) { Ratio = _Set, Attack = true; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImage* BossLifeBase = nullptr;
	UImage* BossLifeBack = nullptr;
	UImage* LifeBar = nullptr;
	UImage* BossHpImage = nullptr;

	float MaxLife = 0.f;
	float Life = MaxLife;

	float Life_POSX = 0.f;
	float LifePos = Life_POSX;
	float Ratio = 0.f;
	bool Attack = false;
};

