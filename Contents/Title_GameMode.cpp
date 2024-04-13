#include "PreCompile.h"
#include "Title_GameMode.h"
#include "Player.h"
#include "Title_BackGround.h"
#include "Title_Logo.h"
#include "Titlre_Cloud.h"
#include <EngineCore/Camera.h>

ATitle_GameMode::ATitle_GameMode()
{
}

ATitle_GameMode::~ATitle_GameMode()
{
}

void ATitle_GameMode::BeginPlay()
{
	Super::BeginPlay();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	GetWorld()->SpawnActor<ATitle_BackGround>("Title_Bg", EOBJ_Order::BackGround);
	GetWorld()->SpawnActor<ATitle_Logo>("Title_logo", EOBJ_Order::BackGround);
	GetWorld()->SpawnActor<ATitlre_Cloud>("Title_Cloud1", EOBJ_Order::BackGround);
	
	//GetWorld()->SpawnActor<APlayer>("Player");
}

void ATitle_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("TownLevel");
	}
}