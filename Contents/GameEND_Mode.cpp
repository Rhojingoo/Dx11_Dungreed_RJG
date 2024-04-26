#include "PreCompile.h"
#include "GameEND_Mode.h"
#include <EngineCore/Camera.h>
#include "TitleCusor.h"
#include "GameEnd_BackGround.h"
#include "EndLevel_UI.h"


bool AGameEND_Mode::EndLevel = false;
bool AGameEND_Mode::Boss_Clear = false;
bool AGameEND_Mode::Player_Die = false;

AGameEND_Mode::AGameEND_Mode()
{
}

AGameEND_Mode::~AGameEND_Mode()
{
}

void AGameEND_Mode::BeginPlay()
{
	Super::BeginPlay();
}

void AGameEND_Mode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);



	if (EndLevel == true)
	{
		Time += _DeltaTime;
		if (5.f <= Time)
		{
			GEngine->ChangeLevel("TitleLevel");
			Time = 0.f;
		}
	}
}

void AGameEND_Mode::LevelStart(ULevel* _PrevLevel)
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	BackGR = GetWorld()->SpawnActor<AGameEnd_BackGround>("End_Bg", EOBJ_Order::BackGround);

	EndUI = GetWorld()->SpawnActor<AEndLevel_UI>("EnidLevel_UI", EOBJ_Order::Damage_Screen);
	EndUI->SetActorLocation({ 0.0f, 0.0f, 200.0f });
	if (Player_Die == true)
	{
		EndUI->Fail();
	}
	else if (Boss_Clear == true)
	{
		EndUI->Success();
	}
	
}

void AGameEND_Mode::LevelEnd(ULevel* _NextLevel)
{
	Camera->Destroy();
	BackGR->Destroy();
	EndUI->Destroy();
}

