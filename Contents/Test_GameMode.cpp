#include "PreCompile.h"
#include "Test_GameMode.h"
#include "Player.h"
#include "Target.h"
#include "Boss_BackGround.h"
#include "Boss_BGPIXEL.h"
#include <EngineCore/Camera.h>
#include "Player.h"
#include <EngineCore/TileRenderer.h>
#include "TileMap.h"
#include <EngineCore/TileRenderer.h>


ATest_GameMode::ATest_GameMode()
{
}

ATest_GameMode::~ATest_GameMode()
{
}

void ATest_GameMode::LevelStart(ULevel* _PrevLevel)
{
}

void ATest_GameMode::LevelEnd(ULevel* _NextLevel)
{
}

void ATest_GameMode::BeginPlay()
{
	Super::BeginPlay();
	Camera = GetWorld()->GetMainCamera();
	// È­¸éÀÇ Áß¾ÓÀ¸·Î º¸³Â´Ù.
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -200.0f));

}

void ATest_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("TownLevel");
	}

	//Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
}
