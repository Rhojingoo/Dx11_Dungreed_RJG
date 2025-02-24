#pragma once
#include <EngineCore/GameMode.h>
#include <EnginePlatform\EngineSound.h>

class ATown_DungeonDoor;
class ATarget;
class ABoss;
class APlayer;
class UCamera;
class ATown_GameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	ATown_GameMode();
	~ATown_GameMode();

	ATown_GameMode(const ATown_GameMode& _Other)					= delete;
	ATown_GameMode(ATown_GameMode& _Other) noexcept					= delete;
	ATown_GameMode& operator =(const 	ATown_GameMode& _Other)		= delete;
	ATown_GameMode& operator =(ATown_GameMode& _Other)noexcept		= delete;

protected:
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<ABoss> Boss = nullptr;
	std::shared_ptr<ATarget> Cursor = nullptr;
	std::shared_ptr<ATown_DungeonDoor> Town_Door = nullptr;
	UEngineSoundPlayer BGM;


};

