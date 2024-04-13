#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class AMonster03_BackGround : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	AMonster03_BackGround();
	~AMonster03_BackGround();

	AMonster03_BackGround(const AMonster03_BackGround& _Other)					= delete;
	AMonster03_BackGround(AMonster03_BackGround& _Other) noexcept					= delete;
	AMonster03_BackGround& operator =(const 	AMonster03_BackGround& _Other)		= delete;
	AMonster03_BackGround& operator =(AMonster03_BackGround& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

