#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineSound.h>

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");
	UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
	UEngineSerializer Ser;
	EngineOption.Serialize(Ser);
	File.Open(EIOOpenMode::Write, EIODataType::Text);
	File.Save(Ser);
}

UEngineCore* GEngine = nullptr;

void UEngineCore::EngineOptionInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");

	FEngineOption Option;
	if (false == Dir.IsFile("EngineOption.EData"))
	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		Option.Serialize(Ser);

		File.Open(EIOOpenMode::Write, EIODataType::Text);
		File.Save(Ser);
	}

	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		File = Dir.GetPathFromFile("EngineOption.EData");
		File.Open(EIOOpenMode::Read, EIODataType::Text);
		File.Load(Ser);
		Option.DeSerialize(Ser);
	}

	EngineWindow.Open(Option.WindowTitle);
	EngineWindow.SetWindowScale(Option.WindowScale);

	UserCorePtr->Initialize();

	UEngineWindow::WindowMessageLoop(
		nullptr,
		nullptr
		//std::bind(&UEngineCore::Update, &Core),
		//std::bind(&UEngineCore::End, &Core)
	);
}

void UEngineCore::EngineStart(HINSTANCE _Inst)
{
	EngineOptionInit();

	EngineWindow.Open(EngineOption.WindowTitle);
	EngineWindow.SetWindowScale(EngineOption.WindowScale);

	{
		UserCorePtr->Initialize();
		MainTimer.TimeCheckStart();
	}

	UEngineWindow::WindowMessageLoop(
		std::bind(&UEngineCore::EngineUpdate, this),
		nullptr
	);	
}

void UEngineCore::EngineUpdate()
{
	float DeltaTime = MainTimer.TimeCheck();
	UEngineInput::KeyCheckTick(DeltaTime);
}
