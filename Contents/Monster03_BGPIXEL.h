#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class AMonster03_BGPIXEL : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	AMonster03_BGPIXEL();
	~AMonster03_BGPIXEL();

	AMonster03_BGPIXEL(const AMonster03_BGPIXEL& _Other)					= delete;
	AMonster03_BGPIXEL(AMonster03_BGPIXEL& _Other) noexcept					= delete;
	AMonster03_BGPIXEL& operator =(const 	AMonster03_BGPIXEL& _Other)		= delete;
	AMonster03_BGPIXEL& operator =(AMonster03_BGPIXEL& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};


