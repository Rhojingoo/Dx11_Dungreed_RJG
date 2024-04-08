#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class ATitle_Logo : public AActor
{
	GENERATED_BODY(AActor)
public:
	ATitle_Logo();
	~ATitle_Logo();

	// delete Function
	ATitle_Logo(const ATitle_Logo& _Other) = delete;
	ATitle_Logo(ATitle_Logo&& _Other) noexcept = delete;
	ATitle_Logo& operator=(const ATitle_Logo& _Other) = delete;
	ATitle_Logo& operator=(ATitle_Logo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;


};

