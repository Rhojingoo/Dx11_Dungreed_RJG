#pragma once
#include <EngineCore/EngineEditorWindow.h>

// ���� :
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


private:
	float4 MousePosWorld;
	int SelectSpriteIndex = 0;
	float TileSize[2] = {};
	float TileCount[2] = {};
	char dataToSave[128] = "";
	char dataToLoad[128] = "";
};



