#include "PreCompile.h"
#include "TileSet_Mode.h"
#include "Player.h"
#include "Target.h"
#include "Boss_BackGround.h"
#include "Boss_BGPIXEL.h"
#include <EngineCore/Camera.h>
#include "Player.h"
#include <EngineCore/TileRenderer.h>
#include "TileMap.h"
#include <EngineCore/TileRenderer.h>


ATileSet_Mode::ATileSet_Mode()
{
}

ATileSet_Mode::~ATileSet_Mode()
{
}

void ATileSet_Mode::LevelStart(ULevel* _PrevLevel)
{
}

void ATileSet_Mode::LevelEnd(ULevel* _NextLevel)
{
}

void ATileSet_Mode::BeginPlay()
{
	Super::BeginPlay();
	Camera = GetWorld()->GetMainCamera();
	// È­¸éÀÇ Áß¾ÓÀ¸·Î º¸³Â´Ù.
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -200.0f));

}

void ATileSet_Mode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("TownLevel");
	}

	//Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
}
