#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class AMonster01_BGPIXEL : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	AMonster01_BGPIXEL();
	~AMonster01_BGPIXEL();

	AMonster01_BGPIXEL(const AMonster01_BGPIXEL& _Other)					= delete;
	AMonster01_BGPIXEL(AMonster01_BGPIXEL& _Other) noexcept					= delete;
	AMonster01_BGPIXEL& operator =(const 	AMonster01_BGPIXEL& _Other)		= delete;
	AMonster01_BGPIXEL& operator =(AMonster01_BGPIXEL& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};

