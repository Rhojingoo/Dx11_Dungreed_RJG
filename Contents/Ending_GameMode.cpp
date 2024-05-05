#include "PreCompile.h"
#include "Ending_GameMode.h"
#include <EngineCore/Camera.h>
#include "Player.h"
#include "Ending_BackGROUND.h"
#include "Title_BackGround.h"
#include "Title_Logo.h"
#include "Titlre_Cloud.h"


AEnding_GameMode::AEnding_GameMode()
{
}

AEnding_GameMode::~AEnding_GameMode()
{
}

void AEnding_GameMode::BeginPlay()
{
	Super::BeginPlay();

	BGM = UEngineSound::SoundPlay("credit2.wav");
	BGM.Off();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	GetWorld()->SpawnActor<AEnding_BackGROUND>("Title_Bg", EOBJ_Order::BackGround);
}

void AEnding_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Endingtime += _DeltaTime;
	if (Endingtime >= 5.f)
	{
		if (EndWinScreen == false)
		{
			EndWinScreen = true;
			Fade = GetWorld()->GetLastTarget()->AddEffect<AFadeIn_OUT_Black>();
			Fadeprt = Fade.get();
		}
		else
		{
			if (Endingtime > 8.5f)
			{
				Endingtime = 0.f;
				//Fadeprt->Active(false);
				GEngine->EngineWindow.Off();
			}
		}
	}
}

void AEnding_GameMode::LevelStart(ULevel* _PrevLevel)
{
	BGM.On();
}

void AEnding_GameMode::LevelEnd(ULevel* _NextLevel)
{
	BGM.Off();
}
