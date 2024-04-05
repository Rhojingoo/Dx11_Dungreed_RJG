#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class URenderer;
class ABackGround : public AActor
{
	GENERATED_BODY(AActor)

public : 
	ABackGround();
	~ABackGround();

	ABackGround(const ABackGround& _Other)				 = delete;
	ABackGround(ABackGround& _Other) noexcept				 = delete;
	ABackGround& operator =(const ABackGround& _Other)	 = delete;
	ABackGround& operator =(ABackGround& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	URenderer* Renderer;
	float4 Color;
};

