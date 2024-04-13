#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class AMonster02_BGPIXEL : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	AMonster02_BGPIXEL();
	~AMonster02_BGPIXEL();

	AMonster02_BGPIXEL(const AMonster02_BGPIXEL& _Other)					= delete;
	AMonster02_BGPIXEL(AMonster02_BGPIXEL& _Other) noexcept					= delete;
	AMonster02_BGPIXEL& operator =(const 	AMonster02_BGPIXEL& _Other)		= delete;
	AMonster02_BGPIXEL& operator =(AMonster02_BGPIXEL& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};


