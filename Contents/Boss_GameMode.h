#pragma once
//#include <EngineCore/GameMode.h>
#include "TileSet_Mode.h"

class ABoss;
class MapEditorGUI;
class APlayer;
class UCamera;
class ABoss_GameMode : public ATileMapLevel /* public AGameMode*/
{
	GENERATED_BODY(ATileMapLevel)

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
	std::shared_ptr<ABoss> Boss = nullptr;

	const float MaxX_Map_Pos = 2080.f;
	const float MaxX_Min_Pos = 400.f;
	const float MaxY_Map_Pos = 750.f;
	const float MaxY_Min_Pos = 450.f;
};

