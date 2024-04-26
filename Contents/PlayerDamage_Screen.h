#pragma once
#include <EngineCore/Actor.h>

class UImage;
class APlayerDamage_Screen : public AActor
{
	GENERATED_BODY(AActor)
public:
	APlayerDamage_Screen();
	~APlayerDamage_Screen();

	// delete Function
	APlayerDamage_Screen(const APlayerDamage_Screen& _Other) = delete;
	APlayerDamage_Screen(APlayerDamage_Screen&& _Other) noexcept = delete;
	APlayerDamage_Screen& operator=(const APlayerDamage_Screen& _Other) = delete;
	APlayerDamage_Screen& operator=(APlayerDamage_Screen&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UImage* Renderer = nullptr;
	float RedColor = 255.f;

};

