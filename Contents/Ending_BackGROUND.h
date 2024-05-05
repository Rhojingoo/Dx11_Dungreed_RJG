#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class UTextWidget;
class AEnding_BackGROUND : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	AEnding_BackGROUND();
	~AEnding_BackGROUND();

	AEnding_BackGROUND(const AEnding_BackGROUND& _Other) = delete;
	AEnding_BackGROUND(AEnding_BackGROUND& _Other) noexcept = delete;
	AEnding_BackGROUND& operator =(const 	AEnding_BackGROUND& _Other) = delete;
	AEnding_BackGROUND& operator =(AEnding_BackGROUND& _Other)noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UTextWidget* TextImage = nullptr;
};


