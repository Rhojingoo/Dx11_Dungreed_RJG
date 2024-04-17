#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATileMapLevel : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ATileMapLevel();
	~ATileMapLevel();

	// delete Function
	ATileMapLevel(const ATileMapLevel& _Other) = delete;
	ATileMapLevel(ATileMapLevel&& _Other) noexcept = delete;
	ATileMapLevel& operator=(const ATileMapLevel& _Other) = delete;
	ATileMapLevel& operator=(ATileMapLevel&& _Other) noexcept = delete;

	std::shared_ptr<class ATileMap> TileMap = nullptr;
	std::string GetName() { return Tile_MapName; }
	int FixelSize[2] = {};
	int IndexCount[2] = {};

	bool GetSetting() {	return TileSetting;}
	void TileSet_True() { TileSetting = true; }
	bool GetActive() {return Active_TileEdit;}
	void SetActive(bool _Set) { Active_TileEdit = _Set; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	std::string Tile_MapName = "";
private:
	bool TileSetting = false;
	bool Active_TileEdit = true;
};

