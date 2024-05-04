#pragma once
#include "TileSet_Mode.h"
#include "Monster.h"
#include <EnginePlatform\EngineSound.h>

class ABossDoor;
class ADungeonDoor;
class Monster;
class ATarget;
class APlayer;
class UCamera;
class AMonster01_GameMode :  public ATileMapLevel 
{
	GENERATED_BODY(ATileMapLevel)
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

	void CreateMonster();
	void IS_Die_Monter(std::vector<std::shared_ptr<AMonster>> _MonsterGroup, bool& _CheckGroup);
	void MonsterGroup1_Enter();
	void MonsterGroup2_Enter();
	void MonsterGroup3_Enter();


private:
	UEngineSoundPlayer BGM;
	UEngineSoundPlayer Ambience;

	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<ATarget> Cursor = nullptr;
	std::shared_ptr<ADungeonDoor> Door = nullptr;
	std::shared_ptr<ABossDoor> BossDoor = nullptr;
	

	std::vector<std::shared_ptr<AMonster>> MonsterGroup_First;
	std::vector<std::shared_ptr<AMonster>> MonsterGroup_Second;
	std::vector<std::shared_ptr<AMonster>> MonsterGroup_Thirth;


	bool MonTerCreate_First = false;
	bool MonTerCreate_Second = false;
	bool MonTerCreate_Thirth = false;

	bool MonTerEnd_First = false;
	bool MonTerEnd_Second = false;
	bool MonTerEnd_Thirth = false;

	bool MonTerEnter_Second = false;


	bool DoorCreate = false;
	bool DoorOpen = false;
};

