#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class ALegendSowrd : public AActor
{
	GENERATED_BODY(AActor)
public:
	ALegendSowrd();
	~ALegendSowrd();

	ALegendSowrd(const ALegendSowrd& _Other)					= delete;
	ALegendSowrd(ALegendSowrd& _Other) noexcept					= delete;
	ALegendSowrd& operator =(const 	ALegendSowrd& _Other)		= delete;
	ALegendSowrd& operator =(ALegendSowrd& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* Renderer = nullptr;
	float4 Color;
};

