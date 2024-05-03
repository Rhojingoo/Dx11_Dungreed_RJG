#pragma once
#include "TileSet_Mode.h"
#include "Monster.h"


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
	void IS_Die_Monter();

private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<ATarget> Cursor = nullptr;

	std::vector<AMonster> MonsterGroup_First;
	std::vector<AMonster> MonsterGroup_Second;
	std::vector<AMonster> MonsterGroup_Thirth;
	std::vector<AMonster> MonsterGroup_Fourth;

};

