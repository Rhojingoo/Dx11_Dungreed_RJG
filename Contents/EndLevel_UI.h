#pragma once
#include <EngineCore/Actor.h>

class UCollision;
class USpriteRenderer;
class AEndLevel_UI : public AActor
{
	GENERATED_BODY(AActor)
public:
	AEndLevel_UI();
	~AEndLevel_UI();

	// delete Function
	AEndLevel_UI(const AEndLevel_UI& _Other) = delete;
	AEndLevel_UI(AEndLevel_UI&& _Other) noexcept = delete;
	AEndLevel_UI& operator=(const AEndLevel_UI& _Other) = delete;
	AEndLevel_UI& operator=(AEndLevel_UI&& _Other) noexcept = delete;

	void StartUIOn();
	void StartUIOff();
	void EndUIOn();
	void EndUIOff();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* LogoRenderer = nullptr;

	USpriteRenderer* GameEnd_Renderer = nullptr;
	UCollision* GameEnd_Collision = nullptr;

};


