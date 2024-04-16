#pragma once
#include "TileMapLevel.h"


class APlayer;
class UCamera;
class ATest_GameMode : public ATileMapLevel
{
	GENERATED_BODY(ATileMapLevel)

public:
	ATest_GameMode();
	~ATest_GameMode();

	// delete Function
	ATest_GameMode(const ATest_GameMode& _Other) = delete;
	ATest_GameMode(ATest_GameMode&& _Other) noexcept = delete;
	ATest_GameMode& operator=(const ATest_GameMode& _Other) = delete;
	ATest_GameMode& operator=(ATest_GameMode&& _Other) noexcept = delete;

protected:
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;

};

