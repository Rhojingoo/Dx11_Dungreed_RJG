#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Boss_BGPIXEL.h"

ABoss_BGPIXEL::ABoss_BGPIXEL()
{
}

ABoss_BGPIXEL::~ABoss_BGPIXEL()
{
}

void ABoss_BGPIXEL::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("NIflheimRoom_Pixel.png");
	Renderer->SetOrder(ERenderOrder::PixelMap);
}

void ABoss_BGPIXEL::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
