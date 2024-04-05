#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class Boss : public AActor
{
	GENERATED_BODY(AActor)

public:
	Boss();
	~Boss();

	Boss(const Boss& _Other)					= delete;
	Boss(Boss& _Other) noexcept					= delete;
	Boss& operator =(const 	Boss& _Other)		= delete;
	Boss& operator =(Boss& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


	//void RendererOff();
	//void RendererOn();

private:
	USpriteRenderer* Renderer = nullptr;
};

