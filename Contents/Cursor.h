#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class ACursor : public AActor
{
	GENERATED_BODY(AActor)
	
public:
	ACursor();
	~ACursor();

	// delete Function
	ACursor(const ACursor& _Other) = delete;
	ACursor(ACursor&& _Other) noexcept = delete;
	ACursor& operator=(const ACursor& _Other) = delete;
	ACursor& operator=(ACursor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	FVector TargetPos = {};
	USpriteRenderer* Renderer = nullptr;
private:

};

