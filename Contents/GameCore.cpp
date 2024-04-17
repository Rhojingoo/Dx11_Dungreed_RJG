#include "PreCompile.h"
#include "GameCore.h"
#include "Title_GameMode.h"
#include "Town_GameMode.h"
#include "Monster01_GameMode.h"
#include "Monster02_GameMode.h"
#include "Monster03_GameMode.h"
#include "Boss_GameMode.h"
#include "TileSet_Mode.h"

#include <EngineCore/EngineSprite.h>

#include <EngineCore/EngineEditorGUI.h>
#include "ContentsGUI.h"
#include "MapEditorGUI.h"

UGameCore::UGameCore()
{
}

UGameCore::~UGameCore()
{
}

void UGameCore::Initialize()
{
	{
		UEngineEditorGUI::CreateEditorWindow<ContentsGUI>("Contents");
		UEngineEditorGUI::CreateEditorWindow<MapEditorGUI>("MapEditor");
	}

	{
		// ������ ���
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png",".bmp"}, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture�ε� ������ �ε尡 �ư�
			// ��������Ʈ�ε� 1��¥���� �ε尡 �� ��Ȳ�̾�.
			UEngineSprite::Load(File.GetFullPath());
		}


		// �ε������� �̷��� �Ѵٰ� Ĩ�ô�.
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory(true);
		//std::vector<UEngineDirectory> Directorys = Dir.AllDirectoryRecursive();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}	
		// Ư�� ��������Ʈ�� 
		// Ư�� �ؽ�ó�� ã�Ƽ�
		// ���� ��������Ʈ�� �������� �ʴ´ٸ�
		// �̰� ����ϴ� ���� ������ �ڸ���.
		// �̹� �� �̸��� ���� ��������Ʈ�� �����Ѵ�.
		// �׷��� ������ ��������Ʈ �����ʹ� ����������
		// �ڸ� ��������Ʈ ������ �����Ѵ�.
		UEngineSprite::CreateCutting("Title_Bird.png", 8, 1);
		UEngineSprite::CreateCutting("Demon_Sword.png", 9, 1);
		UEngineSprite::CreateCutting("Fire_Sword.png", 13, 1);
		UEngineSprite::CreateCutting("Dash_Smoke.png", 5, 1);
		UEngineSprite::CreateCutting("Run_Smoke.png", 6, 1);
		UEngineSprite::CreateCutting("CuttingTest.png", 4, 3);
		UEngineSprite::CreateCutting("Map4X(64).png", 12, 4);
		UEngineSprite::CreateCutting("Map4X(64)_Cut.png", 13, 4);
	
	}
	//UEngineDirectory Dir;
	//Dir.MoveToSearchChild("ContentsResources");
	//Dir.Move("Sound");

	//std::list<UEngineFile> Files = Dir.AllFile({ ".wav" });
	//for (UEngineFile& File : Files)
	//{
	//	UEngineSound::Load(File.GetFullPath());
	//}

	//UEngineSound::SoundPlay("anipang_ingame_wav.wav");

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Sound");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav" });
		for (UEngineFile& File : Files)
		{
			//File.Open(EIOOpenMode::Read, EIODataType::Binary);

			//char Arr[100];
			//File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());
		}
		// UEngineSound::SoundPlay("anipang_ingame_wav.wav");
	}

	GEngine->CreateLevel<ATitle_GameMode>("TitleLevel");
	GEngine->CreateLevel<ATown_GameMode>("TownLevel");
	GEngine->CreateLevel<AMonster01_GameMode>("Mon01_Level");
	GEngine->CreateLevel<AMonster02_GameMode>("Mon02_Level");
	GEngine->CreateLevel<AMonster03_GameMode>("Mon03_Level");
	GEngine->CreateLevel<ABoss_GameMode>("BossLevel");

	GEngine->ChangeLevel("Mon01_Level");



}
