#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Monster01_BGPIXEL.h"

AMonster01_BGPIXEL::AMonster01_BGPIXEL()
{
}

AMonster01_BGPIXEL::~AMonster01_BGPIXEL()
{
}

void AMonster01_BGPIXEL::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("Monster_01PX.png");
	Renderer->SetOrder(ERenderOrder::PixelMap);
}

void AMonster01_BGPIXEL::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
