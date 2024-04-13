#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Town_BackGround.h"

ATown_BackGround::ATown_BackGround()
{
}

ATown_BackGround::~ATown_BackGround()
{
}

void ATown_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));//Town
	Renderer->SetSprite("TownModel.png");  //¿øº»
	
	//Renderer->SetSprite("TownBG_Night.bmp");
	//Renderer->SetSprite("TownLayer_Night.bmp");
	Renderer->SetOrder(ERenderOrder::ForeGround);
}

void ATown_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
