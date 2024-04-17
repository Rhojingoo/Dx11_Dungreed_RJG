#include "PreCompile.h"
#include "Monster03_BGPIXEL.h"

AMonster03_BGPIXEL::AMonster03_BGPIXEL()
{
}

AMonster03_BGPIXEL::~AMonster03_BGPIXEL()
{
}

void AMonster03_BGPIXEL::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("Monster_03PX.png");
	Renderer->SetOrder(ERenderOrder::PixelMap);
}

void AMonster03_BGPIXEL::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
