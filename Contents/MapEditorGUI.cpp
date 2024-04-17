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


	if ("Mon01_Level" == Level->GetName())
	{
		On();
	}
	else
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
	//char spriteFilename[128] = "Map4X(64).png";
	char spriteFilename[128] = "Map4X(64)_Cut.png";

	
	// 타일 크기 지정
	// 타일 개수 x
	// 타일 개수 y를 
	// 스프라이트 선택.
	// 저장.
	ImGui::InputFloat2("TileSize", TileSize);
	ImGui::InputFloat2("TileCount", TileCount);
	ImGui::InputText("Sprite Filename", spriteFilename, IM_ARRAYSIZE(spriteFilename));

	if (true == ImGui::Button("Create"))
	{
		TileRenderer->CreateTileMap(spriteFilename, { TileSize[0], TileSize[1] }, TileCount[0], TileCount[1], 0);
	}

	//dataToSave = {0};
	ImGui::InputTextMultiline("Save Data Name", dataToSave, IM_ARRAYSIZE(dataToSave));
	if (ImGui::Button("Save Data"))
	{		
		{
			UEngineDirectory Dir;
			Dir.MoveToSearchChild("ContentsResources");
			Dir.Move("Image");
			Dir.Move("TileMap_Save");
			FEngineOption EngineOption;
			std::fstream fs;
			std::string str_buf;

			{
				UEngineFile File = Dir.GetPathFromFile(std::string(dataToSave) + ".csv");
				File.Open(EIOOpenMode::Write, EIODataType::Text);

				UEngineSerializer Ser;
				std::string Text;
				Text = std::format("TileSizeX :, {}, TileSizeY : ,{}\n", TileSize[0], TileSize[1]);

				std::vector<std::vector<int>> TileData = TileRenderer->GetTileMapData();

				Text += std::format("TileCount :, {}, TileCount : ,{}\n", TileCount[0], TileCount[1]);

				for (size_t y = 0; y < TileData.size(); y++)
				{
					for (size_t x = 0; x < TileData[y].size(); x++)
					{
						Text += std::format("{}", TileData[y][x]);

						if (x != TileData[y].size() - 1)
						{
							Text += ",";
						}
					}
					Text += "\n";
				}
				Ser.WriteText(Text);

				File.Save(Ser);
			}

		}
	}	
	

	ImGui::InputTextMultiline("Load Data Name", dataToLoad, IM_ARRAYSIZE(dataToLoad));
	if (ImGui::Button("Load Data")) 
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image");
		Dir.Move("TileMap_Save");
		if (true == Dir.IsFile(std::string(dataToLoad) + ".csv"))
		{
			UEngineFile File = Dir.GetPathFromFile(std::string(dataToLoad) + ".csv");

			File.Open(EIOOpenMode::Read, EIODataType::Text);
			UEngineSerializer Ser;
			File.Load(Ser);

			std::string LSTR = Ser.ToString();
			std::vector<std::vector<int>> Result;

			std::vector<std::string> Values = UEngineString::StringCutting(LSTR, {",", "\n"});

			TileSize[0] = std::stoi(Values[1]);
			TileSize[1] = std::stoi(Values[3]);

			TileCount[0] = std::stoi(Values[5]);
			TileCount[1] = std::stoi(Values[7]);

			Result.resize(TileCount[1]);
			for (size_t y = 0; y < TileCount[1]; y++)
			{
				Result[y].resize(TileCount[0]);
			}
			int StartCount = 8;

			for (size_t y = 0; y < TileCount[1]; y++)
			{
				for (size_t x = 0; x < TileCount[0]; x++)
				{
					Result[y][x] = (std::stoi(Values[StartCount++]));
				}
			}

			TileRenderer->CreateTileMap(spriteFilename, { 64, 64 }, TileCount[0], TileCount[1], 0);
			for (size_t y = 0; y < TileCount[1]; y++)
			{
				for (size_t x = 0; x < TileCount[0]; x++)
				{					
					TileRenderer->SetTile(x,y, Result[y][x]);
				}
			}					
		}
	}			


	ImGui::Text(("WorldMouse : " + MousePosWorld.ToString()).c_str());
	float4 Index = TileRenderer->ConvertTileIndex(MousePosWorld);
	ImGui::Text(("TileIndexPos : " + Index.ToString()).c_str());
	ImGui::Text(std::format("Index : {} {}", Index.iX(), Index.iY()).c_str());


	
	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes("Map4X(64)_Cut.png");
	
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

		if (true == ImGui::ImageButton(Text.c_str(), Info.Texture->GetSRV(), {64, 64}, UV0, UV1))
		{
			SelectSpriteIndex = i;
		}
		
		if ((i + 1) % 5 )
		{
			ImGui::SameLine();
		}
	}
		
	ImGui::EndChild();
}

