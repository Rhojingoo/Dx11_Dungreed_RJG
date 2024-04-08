#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Title_BackGround.h"

ATitle_BackGround::ATitle_BackGround()
{
}

ATitle_BackGround::~ATitle_BackGround()
{
}

void ATitle_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1280.0f, 860.0f, 100.0f));
	Renderer->SetSprite("TitleSky.png");
}

void ATitle_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
