#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class AMonster02_BackGround : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	AMonster02_BackGround();
	~AMonster02_BackGround();

	AMonster02_BackGround(const AMonster02_BackGround& _Other)						= delete;
	AMonster02_BackGround(AMonster02_BackGround& _Other) noexcept					= delete;
	AMonster02_BackGround& operator =(const 	AMonster02_BackGround& _Other)		= delete;
	AMonster02_BackGround& operator =(AMonster02_BackGround& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};


