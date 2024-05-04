#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform\EngineSound.h>

// Ό³Έν :
class Title_UI;
class ATitle_GameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ATitle_GameMode();
	~ATitle_GameMode();

	// delete Function
	ATitle_GameMode(const ATitle_GameMode& _Other) = delete;
	ATitle_GameMode(ATitle_GameMode&& _Other) noexcept = delete;
	ATitle_GameMode& operator=(const ATitle_GameMode& _Other) = delete;
	ATitle_GameMode& operator=(ATitle_GameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	UEngineSoundPlayer BGM;

};

