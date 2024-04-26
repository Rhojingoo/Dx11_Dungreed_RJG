#include "PreCompile.h"
#include "GameEnd_BackGround.h"
#include <EngineCore/Renderer.h>

AGameEnd_BackGround::AGameEnd_BackGround()
{

}

AGameEnd_BackGround::~AGameEnd_BackGround()
{
}

void AGameEnd_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));//Town
	Renderer->SetSprite("Black.png");  //¿øº»
	Renderer->SetOrder(ERenderOrder::BackGround);
	Renderer->SetAutoSize(3.f, true);
}

void AGameEnd_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

