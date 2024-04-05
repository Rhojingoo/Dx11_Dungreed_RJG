#include "PreCompile.h"
#include "Town_GameMode.h"
#include "Player.h"
#include "Town_BackGround.h"
#include <EngineCore/Camera.h>

ATown_GameMode::ATown_GameMode()
{
}

ATown_GameMode::~ATown_GameMode()
{
}

void ATown_GameMode::BeginPlay()
{
	Super::BeginPlay();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	GetWorld()->SpawnActor<ATown_BackGround>("Title_Bg");
	//GetWorld()->SpawnActor<APlayer>("Player");
}

void ATown_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("BossLevel");
	}
}
