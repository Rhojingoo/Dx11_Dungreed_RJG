#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class ATitle_Bird : public AActor
{
	GENERATED_BODY(AActor)

public:
	ATitle_Bird();
	~ATitle_Bird();

	// delete Function
	ATitle_Bird(const ATitle_Bird& _Other) = delete;
	ATitle_Bird(ATitle_Bird&& _Other) noexcept = delete;
	ATitle_Bird& operator=(const ATitle_Bird& _Other) = delete;
	ATitle_Bird& operator=(ATitle_Bird&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* Renderer = nullptr;

};

