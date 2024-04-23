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

	AMonster_HpBar(const AMonster_HpBar& _Other)						= delete;
	AMonster_HpBar(AMonster_HpBar& _Other) noexcept					= delete;
	AMonster_HpBar& operator =(const 	AMonster_HpBar& _Other)		= delete;
	AMonster_HpBar& operator =(AMonster_HpBar& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* LifeBack = nullptr;
	USpriteRenderer* LifeBar = nullptr;
	UDefaultSceneComponent* Root = nullptr;

	const float MaxLife = 200.f;
	float Life = MaxLife;

	const float Life_POSX = -410.f;
	float LifePos = Life_POSX;
};


