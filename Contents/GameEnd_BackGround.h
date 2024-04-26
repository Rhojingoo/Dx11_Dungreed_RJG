#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class AGameEnd_BackGround : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	AGameEnd_BackGround();
	~AGameEnd_BackGround();

	// delete Function
	AGameEnd_BackGround(const AGameEnd_BackGround& _Other) = delete;
	AGameEnd_BackGround(AGameEnd_BackGround&& _Other) noexcept = delete;
	AGameEnd_BackGround& operator=(const AGameEnd_BackGround& _Other) = delete;
	AGameEnd_BackGround& operator=(AGameEnd_BackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:


};
