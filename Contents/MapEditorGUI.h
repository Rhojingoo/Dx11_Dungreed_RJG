#pragma once
#include <EngineCore/EngineEditorWindow.h>

// Ό³Έν :
class UTileRenderer;
class MapEditorGUI : public UEngineEditorWindow
{
public:
	// constrcuter destructer
	MapEditorGUI();
	~MapEditorGUI();

	// delete Function
	MapEditorGUI(const MapEditorGUI& _Other) = delete;
	MapEditorGUI(MapEditorGUI&& _Other) noexcept = delete;
	MapEditorGUI& operator=(const MapEditorGUI& _Other) = delete;
	MapEditorGUI& operator=(MapEditorGUI&& _Other) noexcept = delete;

protected:
	virtual void Init();

	virtual void Tick(ULevel* Level, float _Delta);

	virtual void OnGui(ULevel* Level, float _Delta);

	void saveData(const std::string_view _data, const std::string_view _filePath);

private:
	float4 MousePosWorld;
	int SelectSpriteIndex = 0;
	float TileSize[2] = {};
	float TileCount[2] = {};
	char dataToSave[128] = "";
	char dataToLoad[128] = "";
	bool Delete = false;
};



