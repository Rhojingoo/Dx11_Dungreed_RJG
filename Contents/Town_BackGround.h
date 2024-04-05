#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class ATown_BackGround : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	ATown_BackGround();
	~ATown_BackGround();

	ATown_BackGround(const ATown_BackGround& _Other)					= delete;
	ATown_BackGround(ATown_BackGround& _Other) noexcept					= delete;
	ATown_BackGround& operator =(const 	ATown_BackGround& _Other)		= delete;
	ATown_BackGround& operator =(ATown_BackGround& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
};

