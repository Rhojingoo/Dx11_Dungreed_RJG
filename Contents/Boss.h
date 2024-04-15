#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class ABoss : public AActor
{
	GENERATED_BODY(AActor)

public:
	ABoss();
	~ABoss();

	ABoss(const ABoss& _Other)					= delete;
	ABoss(ABoss& _Other) noexcept					= delete;
	ABoss& operator =(const 	ABoss& _Other)		= delete;
	ABoss& operator =(ABoss& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


	//void RendererOff();
	//void RendererOn();

private:
	USpriteRenderer* Renderer = nullptr;
};

