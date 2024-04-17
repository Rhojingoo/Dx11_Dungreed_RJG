#pragma once
#include <EngineCore/GameMode.h>

class MapEditorGUI;
class APlayer;
class UCamera;
class ABoss_GameMode :  public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	ABoss_GameMode();
	~ABoss_GameMode();

	ABoss_GameMode(const ABoss_GameMode& _Other)					= delete;
	ABoss_GameMode(ABoss_GameMode& _Other) noexcept					= delete;
	ABoss_GameMode& operator =(const 	ABoss_GameMode& _Other)		= delete;
	ABoss_GameMode& operator =(ABoss_GameMode& _Other)noexcept		= delete;

	void SetMapEdit();

protected:
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<MapEditorGUI> MapGui = nullptr;
};

