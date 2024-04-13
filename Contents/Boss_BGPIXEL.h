#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class ABoss_BGPIXEL : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	ABoss_BGPIXEL();
	~ABoss_BGPIXEL();

	ABoss_BGPIXEL(const ABoss_BGPIXEL& _Other)					= delete;
	ABoss_BGPIXEL(ABoss_BGPIXEL& _Other) noexcept					= delete;
	ABoss_BGPIXEL& operator =(const 	ABoss_BGPIXEL& _Other)		= delete;
	ABoss_BGPIXEL& operator =(ABoss_BGPIXEL& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};




