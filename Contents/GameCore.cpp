#include "PreCompile.h"
#include "GameCore.h"
#include "Title_GameMode.h"
#include "Town_GameMode.h"
#include "Boss_GameMode.h"
#include <EngineCore/EngineSprite.h>

UGameCore::UGameCore()
{
}

UGameCore::~UGameCore()
{
}

void UGameCore::Initialize()
{
	{
		// 파일의 헤더
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png",".bmp"}, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture로도 한장이 로드가 됐고
			// 스프라이트로도 1장짜리로 로드가 된 상황이야.
			UEngineSprite::Load(File.GetFullPath());
		}


		// 로드폴더는 이렇게 한다고 칩시다.
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory(true);
		//std::vector<UEngineDirectory> Directorys = Dir.AllDirectoryRecursive();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}	
		// 특정 스프라이트나 
		// 특정 텍스처를 찾아서
		// 만약 스프라이트가 존재하지 않는다면
		// 이걸 사용하는 순간 만들어내고 자른다.
		// 이미 이 이름을 가진 스프라이트가 존재한다.
		// 그러면 기존의 스프라이트 데이터는 날려버리고
		// 자른 스프라이트 데이터 변경한다.
		//UEngineSprite::CreateCutting("CuttingTest.png", 4, 3);
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
	GEngine->CreateLevel<ABoss_GameMode>("BossLevel");
	GEngine->ChangeLevel("TitleLevel");



}
