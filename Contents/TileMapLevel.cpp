#include "PreCompile.h"
#include "TileMapLevel.h"
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


ATileMapLevel::ATileMapLevel() 
{
}

ATileMapLevel::~ATileMapLevel() 
{
}

void ATileMapLevel::BeginPlay()
{
	Super::BeginPlay();
	TileMap = GetWorld()->SpawnActor<ATileMap>("TileMap", ERenderOrder::TileMap);
}

void ATileMapLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
