#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class ATitle_BackGround : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	ATitle_BackGround();
	~ATitle_BackGround();

	ATitle_BackGround(const ATitle_BackGround& _Other)					= delete;
	ATitle_BackGround(ATitle_BackGround& _Other) noexcept					= delete;
	ATitle_BackGround& operator =(const 	ATitle_BackGround& _Other)		= delete;
	ATitle_BackGround& operator =(ATitle_BackGround& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

