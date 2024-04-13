#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class AMonster01_BackGround : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	AMonster01_BackGround();
	~AMonster01_BackGround();

	AMonster01_BackGround(const AMonster01_BackGround& _Other)					= delete;
	AMonster01_BackGround(AMonster01_BackGround& _Other) noexcept					= delete;
	AMonster01_BackGround& operator =(const 	AMonster01_BackGround& _Other)		= delete;
	AMonster01_BackGround& operator =(AMonster01_BackGround& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

