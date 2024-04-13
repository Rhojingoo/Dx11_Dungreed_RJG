#pragma once
#include <EngineCore/GameMode.h>

class APlayer;
class UCamera;
class AMonster02_GameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	AMonster02_GameMode();
	~AMonster02_GameMode();

	AMonster02_GameMode(const AMonster02_GameMode& _Other)					= delete;
	AMonster02_GameMode(AMonster02_GameMode& _Other) noexcept					= delete;
	AMonster02_GameMode& operator =(const 	AMonster02_GameMode& _Other)		= delete;
	AMonster02_GameMode& operator =(AMonster02_GameMode& _Other)noexcept		= delete;

protected:
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
};