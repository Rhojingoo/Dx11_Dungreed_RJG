#include "PreCompile.h"
#include "Title_GameMode.h"
#include "Player.h"
#include "Title_BackGround.h"
#include "Title_Logo.h"
#include "Titlre_Cloud.h"
#include <EngineCore/Camera.h>
#include "Title_UI.h"
#include "TitleCusor.h"
#include "Title_Bird.h"
#include "EndLevel_UI.h"

ATitle_GameMode::ATitle_GameMode()
{
}

ATitle_GameMode::~ATitle_GameMode()
{
	
}

void ATitle_GameMode::BeginPlay()
{
	Super::BeginPlay();

	BGM = UEngineSound::SoundPlay("title.wav");
	BGM.Off();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));


	GetWorld()->SpawnActor<ATitle_BackGround>("Title_Bg", EOBJ_Order::BackGround);
	GetWorld()->SpawnActor<ATitle_Logo>("Title_logo", EOBJ_Order::BackGround);
	GetWorld()->SpawnActor<ATitlre_Cloud>("Title_Cloud1", EOBJ_Order::BackGround);
	
	std::shared_ptr<ATitle_UI> TitleUI = GetWorld()->SpawnActor<ATitle_UI>("ATitle_UI", EOBJ_Order::BackGround);
	TitleUI->SetActorLocation({ 0.f, -50.0f, 200.0f });

	std::shared_ptr<TitleCusor> TitleCursorUI = GetWorld()->SpawnActor<TitleCusor>("ATitle_CursorUI", EOBJ_Order::Cursor);
	TitleCursorUI->SetActorLocation({ 0.0f, 0.0f, 200.0f });
	
	std::shared_ptr<ATitle_Bird> TitleBird1 = GetWorld()->SpawnActor<ATitle_Bird>("ATitle_CursorUI", EOBJ_Order::Bullet);
	TitleBird1->SetActorLocation({ -850.0f, 250.0f, 201.0f });

	std::shared_ptr<ATitle_Bird> TitleBird2 = GetWorld()->SpawnActor<ATitle_Bird>("ATitle_CursorUI", EOBJ_Order::Bullet);
	TitleBird2->SetActorLocation({ -1050.0f, -50.0f, 201.0f });

	std::shared_ptr<ATitle_Bird> TitleBird3 = GetWorld()->SpawnActor<ATitle_Bird>("ATitle_CursorUI", EOBJ_Order::Bullet);
	TitleBird3->SetActorLocation({ -650.0f, -150.0f, 201.0f });

	std::shared_ptr<ATitle_Bird> TitleBird4 = GetWorld()->SpawnActor<ATitle_Bird>("ATitle_CursorUI", EOBJ_Order::Bullet);
	TitleBird4->SetActorLocation({ -1550.0f, -50.0f, 201.0f });

	std::shared_ptr<ATitle_Bird> TitleBird5 = GetWorld()->SpawnActor<ATitle_Bird>("ATitle_CursorUI", EOBJ_Order::Bullet);
	TitleBird5->SetActorLocation({ -1850.0f, -150.0f, 201.0f });

}

void ATitle_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ATitle_GameMode::LevelStart(ULevel* _PrevLevel)
{
	BGM.On();
}

void ATitle_GameMode::LevelEnd(ULevel* _NextLevel)
{
	BGM.Off();
}
