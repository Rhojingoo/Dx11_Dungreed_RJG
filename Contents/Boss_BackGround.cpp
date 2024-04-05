#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Boss_BackGround.h"

ABoss_BackGround::ABoss_BackGround()
{
}

ABoss_BackGround::~ABoss_BackGround()
{
}

void ABoss_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("NIflheimRoom.bmp");
	//Renderer->SetSprite("IceFrontBG.bmp");
	//Renderer->SetSprite("IceBackBG.bmp");
	//Renderer->SetSprite("Ice_NIflheim_foothold.bmp");
	//Renderer->SetSprite("Ice_NIflheim.bmp");
}

void ABoss_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
