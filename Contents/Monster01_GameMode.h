#pragma once
#include <EngineCore/GameMode.h>
#include "Test_GameMode.h"

class APlayer;
class UCamera;
class AMonster01_GameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	AMonster01_GameMode();
	~AMonster01_GameMode();

	AMonster01_GameMode(const AMonster01_GameMode& _Other)					= delete;
	AMonster01_GameMode(AMonster01_GameMode& _Other) noexcept					= delete;
	AMonster01_GameMode& operator =(const 	AMonster01_GameMode& _Other)		= delete;
	AMonster01_GameMode& operator =(AMonster01_GameMode& _Other)noexcept		= delete;

protected:
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
};

