#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class ABoss_BackGround : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	ABoss_BackGround();
	~ABoss_BackGround();

	ABoss_BackGround(const ABoss_BackGround& _Other)					= delete;
	ABoss_BackGround(ABoss_BackGround& _Other) noexcept					= delete;
	ABoss_BackGround& operator =(const 	ABoss_BackGround& _Other)		= delete;
	ABoss_BackGround& operator =(ABoss_BackGround& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	FVector FrontVertexplus = {};
};

