#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class UDefaultSceneComponent;
class UImage;
class AMonster_HpBar : public AActor
{
	GENERATED_BODY(AActor)
public:
	AMonster_HpBar();
	~AMonster_HpBar();

	AMonster_HpBar(const AMonster_HpBar& _Other)					= delete;
	AMonster_HpBar(AMonster_HpBar& _Other) noexcept					= delete;
	AMonster_HpBar& operator =(const 	AMonster_HpBar& _Other)		= delete;
	AMonster_HpBar& operator =(AMonster_HpBar& _Other)noexcept		= delete;

	void Regenerate();
	void AttackDamege(float _Attackratio);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* LifeBack = nullptr;
	USpriteRenderer* LifeBar = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	float MaxLife = 0.f;
	float Life = MaxLife;

	float Life_POSX = 0.f;
	float LifePos = Life_POSX;

	bool Attack = false;
	float Attackratio = 0.f;
	float TimeCheck = 0.f;
};


