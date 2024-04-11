#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>


class ATarget : public AActor
{
	GENERATED_BODY(AActor)
public:
	ATarget();
	~ATarget();

	// delete Function
	ATarget(const ATarget& _Other) = delete;
	ATarget(ATarget&& _Other) noexcept = delete;
	ATarget& operator=(const ATarget& _Other) = delete;
	ATarget& operator=(ATarget&& _Other) noexcept = delete;
	
	FVector GetPos() { return TargetPos; }


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//void RendererOff();
	//void RendererOn();

private:
	USpriteRenderer* Renderer = nullptr;
	FVector TargetPos = {};

};

