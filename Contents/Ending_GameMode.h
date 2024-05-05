#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform\EngineSound.h>
#include "FadeIn_OUT_Black.h"

// Ό³Έν :
class Title_UI;
class AEnding_GameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	AEnding_GameMode();
	~AEnding_GameMode();

	AEnding_GameMode(const AEnding_GameMode& _Other) = delete;
	AEnding_GameMode(AEnding_GameMode&& _Other) noexcept = delete;
	AEnding_GameMode& operator=(const AEnding_GameMode& _Other) = delete;
	AEnding_GameMode& operator=(AEnding_GameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	UEngineSoundPlayer BGM;	
	float Endingtime = 0.f;
	bool EndWinScreen = false;

	std::shared_ptr<AFadeIn_OUT_Black> Fade = nullptr;
	AFadeIn_OUT_Black* Fadeprt = nullptr;

};

