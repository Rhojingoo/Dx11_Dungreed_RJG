#pragma once
#include <EngineCore/Actor.h>

class UImage;
class AHP_Bar : public AActor
{
	GENERATED_BODY(AActor)
public:
	AHP_Bar();
	~AHP_Bar();

	// delete Function
	AHP_Bar(const AHP_Bar& _Other) = delete;
	AHP_Bar(AHP_Bar&& _Other) noexcept = delete;
	AHP_Bar& operator=(const AHP_Bar& _Other) = delete;
	AHP_Bar& operator=(AHP_Bar&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImage* PlayerLifeBase = nullptr;
	UImage* PlayerLifeBack = nullptr;
	UImage* LifeBar = nullptr;
	UImage* LifeBarWave = nullptr;

	const int MaxLife = 200;
	int Life = MaxLife;

	const int Life_POSX = -410;
	int LifePos = MaxLife;
};

