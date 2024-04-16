#include "PreCompile.h"
#include "MapEditorGUI.h"
#include "TileMapLevel.h"
#include <EngineCore/TileRenderer.h>
#include "TileMap.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Camera.h>
#include <fstream>
#include <iostream>
#include <string>
#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineOption.h>


MapEditorGUI::MapEditorGUI() 
{
}

MapEditorGUI::~MapEditorGUI() 
{
}

void MapEditorGUI::Init()
{
	
}

void MapEditorGUI::Tick(ULevel* Level, float _Delta)
{
	Level->GetMainCamera();
	float Speed = 500.0f;

	if (true == UEngineInput::IsPress('A'))
	{
		Level->GetMainCamera()->AddActorLocation(float4::Left * _Delta * Speed);
	}

	if (true == UEngineInput::IsPress('D'))
	{
		Level->GetMainCamera()->AddActorLocation(float4::Right * _Delta * Speed);
	}

	if (true == UEngineInput::IsPress('W'))
	{
		Level->GetMainCamera()->AddActorLocation(float4::Up * _Delta * Speed);
	}

	if (true == UEngineInput::IsPress('S'))
	{
		Level->GetMainCamera()->AddActorLocation(float4::Down * _Delta * Speed);
	}

	std::string LevelName = Level->GetName();

	if ("TestLevel" == Level->GetName())
	{
		On();
	} else 
	{
		Off();
	}

	std::shared_ptr<AGameMode> Mode = Level->GetGameMode();

	ATileMapLevel* Ptr = dynamic_cast<ATileMapLevel*>(Mode.get());

	if (nullptr == Ptr)
	{
		return;
	}

	UTileRenderer* TileRenderer = Ptr->TileMap->TileRenderer;

	if (true == UEngineInput::IsPress(VK_LBUTTON))
	{
		float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
		MousePosWorld = Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

		TileRenderer->SetTile(MousePosWorld, SelectSpriteIndex);
	}


}

void MapEditorGUI::OnGui(ULevel* Level, float _Delta)
{

	float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
	MousePosWorld = Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

	std::shared_ptr<AGameMode> Mode = Level->GetGameMode();

	ATileMapLevel* Ptr = dynamic_cast<ATileMapLevel*>(Mode.get());

	if (nullptr == Ptr)
	{
		return;
	}

	UTileRenderer* TileRenderer = Ptr->TileMap->TileRenderer;
	char spriteFilename[128] = "Map4X(64).png";

	// Ÿ�� ũ�� ����
	// Ÿ�� ���� x
	// Ÿ�� ���� y�� 
	// ��������Ʈ ����.
	// ����.
	ImGui::InputFloat2("TileSize", TileSize);
	ImGui::InputFloat2("TileCount", TileCount);
	ImGui::InputText("Sprite Filename", spriteFilename, IM_ARRAYSIZE(spriteFilename));
	// ImGui::InputFloat2()

	if (true == ImGui::Button("Create"))
	{
		TileRenderer->CreateTileMap(spriteFilename, { TileSize[0], TileSize[1] }, TileCount[0], TileCount[1], 0);
	}

	//dataToSave = {0};
	ImGui::InputTextMultiline("Data Name", dataToSave, IM_ARRAYSIZE(dataToSave));
	
	if (ImGui::Button("Save Data"))
	{
		


		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image");
		Dir.Move("TileMap_Save");
		std::filesystem::path Path = Dir.GetFullPath();	


		{
			UEngineDirectory Dir;
			Dir.MoveToSearchChild("ContentsResources");
			Dir.Move("Image");
			Dir.Move("TileMap_Save");
			FEngineOption EngineOption;
			if (false == Dir.IsFile(dataToSave))
			{
				UEngineFile File = Dir.GetPathFromFile(dataToSave);
				//UEngineSerializer Ser;		
				//EngineOption.Serialize(Ser);

				TileRenderer->GetTileMapData();
				File.Open(EIOOpenMode::Write, EIODataType::Text);
				File.Save(Ser);
			}
		}


		//saveData(dataToSave, Path.string());
	}
	//UEngineString::AnsiToUniCode(
	//std::string Data = dataToSave;

	ImGui::Text(("WorldMouse : " + MousePosWorld.ToString()).c_str());
	float4 Index = TileRenderer->ConvertTileIndex(MousePosWorld);
	ImGui::Text(("TileIndexPos : " + Index.ToString()).c_str());
	ImGui::Text(std::format("Index : {} {}", Index.iX(), Index.iY()).c_str());

	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes("Map4X(64).png");


	// ���̷�Ʈ ����̽���
	// ���̷�Ʈ ���ؽ�
	// imgui�� ���ο��� �ڽ��� ���̴��� ����մϴ�.

	// imgui���� ����ϴ� ���̴��� �� �ؽ�ó�� ����.
	// ImVec2

	// IMgui�� ������ char* Eventüũ�� �մϴ�;
	if (SelectSpriteIndex != -1)
	{
		FSpriteInfo Info = Sprite->GetSpriteInfo(SelectSpriteIndex);

		ImVec2 UV0 = { Info.CuttingPosition.X, Info.CuttingPosition.Y };
		ImVec2 UV1 = { Info.CuttingSize.X, Info.CuttingSize.Y };

		UV1.x = UV1.x + UV0.x;
		UV1.y = UV1.y + UV0.y;

		ImGui::ImageButton("Select", Info.Texture->GetSRV(), { 100, 100 }, UV0, UV1);
	}
	else 
	{
		ImGui::ImageButton("Select", nullptr, { 100, 100 });
	}

	ImGui::BeginChild("TileSelect", { 0, 0 }, false, ImGuiWindowFlags_HorizontalScrollbar);


	for (int i = 0; i < Sprite->GetInfoSize(); i++)
	{
		FSpriteInfo Info = Sprite->GetSpriteInfo(i);

		ImVec2 UV0 = { Info.CuttingPosition.X, Info.CuttingPosition.Y};
		ImVec2 UV1 = { Info.CuttingSize.X, Info.CuttingSize.Y };

		UV1.x = UV1.x + UV0.x;
		UV1.y = UV1.y + UV0.y;

		std::string Text = std::to_string(i);

		// �ٹٲ��� �ڵ����� ���ش�.
		if (true == ImGui::ImageButton(Text.c_str(), Info.Texture->GetSRV(), {64, 64}, UV0, UV1))
		{
			SelectSpriteIndex = i;
		}
		
		if ((i + 1) % 5 )
		{
			ImGui::SameLine();
		}
	}

	// Index ���� ������ ��������Ʈ
	//ImGui::TextUnformatted("child_2");
	//ImGui::GetWindowDrawList()->AddLine({ 0, 0 }, { 500, 500 }, 0xFFFFFFFF);
	//ImGui::SetCursorPos({ 1500, 1500 });
	//ImGui::TextUnformatted("hello");
	ImGui::EndChild();
}

void MapEditorGUI::saveData(const std::string_view _data, const std::string_view _filePath)
{
	//UEngineDirectory Dir;
	//Dir.MoveToSearchChild("ContentsResources");
	//Dir.Move("Image");
	//Dir.Move("TileMap_Save");
	//FEngineOption EngineOption;
	//if (false==Dir.IsFile(_data))
	//{
	//	UEngineFile File = Dir.GetPathFromFile(_data);
	//	//UEngineSerializer Ser;		
	//	//EngineOption.Serialize(Ser);
	//	File.Open(EIOOpenMode::Write, EIODataType::Text);
	//	File.Save(Ser);
	//}

	{
		//UEngineFile File = Dir.GetPathFromFile(_data);
		//UEngineSerializer Ser;
		//File = Dir.GetPathFromFile(_data);
		//File.Open(EIOOpenMode::Read, EIODataType::Text);
		//File.Load(Ser);
		//EngineOption.DeSerialize(Ser);
	}
}
