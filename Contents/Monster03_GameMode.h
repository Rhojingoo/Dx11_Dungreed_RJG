#pragma once
#include <EngineCore/GameMode.h>


class APlayer;
class UCamera;
class AMonster03_GameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	AMonster03_GameMode();
	~AMonster03_GameMode();

	AMonster03_GameMode(const AMonster03_GameMode& _Other)					= delete;
	AMonster03_GameMode(AMonster03_GameMode& _Other) noexcept					= delete;
	AMonster03_GameMode& operator =(const 	AMonster03_GameMode& _Other)		= delete;
	AMonster03_GameMode& operator =(AMonster03_GameMode& _Other)noexcept		= delete;

protected:
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
};


