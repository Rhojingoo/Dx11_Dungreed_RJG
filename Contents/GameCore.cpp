#include "PreCompile.h"
#include "GameCore.h"

UGameCore::UGameCore()
{
}

UGameCore::~UGameCore()
{
}

void UGameCore::Initialize()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Sound");

	std::list<UEngineFile> Files = Dir.AllFile({ ".wav" });
	for (UEngineFile& File : Files)
	{
		UEngineSound::Load(File.GetFullPath());
	}

	UEngineSound::SoundPlay("anipang_ingame_wav.wav");
}
