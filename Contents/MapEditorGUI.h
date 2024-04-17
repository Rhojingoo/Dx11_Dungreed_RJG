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

	//void SetLoad(char* _Set) 
	//{ 
	//	dataToLoad;
	//	std::string(dataToLoad) = _Set; 
	//	dataToLoad;
	//	int a = 0;
	//}

protected:
	virtual void Init();

	virtual void Tick(ULevel* Level, float _Delta);

	virtual void OnGui(ULevel* Level, float _Delta);


private:
	float4 MousePosWorld;
	int SelectSpriteIndex = 12;
	int TileSize[2] = {};
	int TileCount[2] = {};
	char dataToSave[128] = "";
	char dataToLoad[128] = "";
	bool active = true;
	bool FirstSetting = false;
};



