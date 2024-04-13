#include "PreCompile.h"
#include "Monster02_BGPIXEL.h"

AMonster02_BGPIXEL::AMonster02_BGPIXEL()
{
}

AMonster02_BGPIXEL::~AMonster02_BGPIXEL()
{
}

void AMonster02_BGPIXEL::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("Monster_02PX.png");
}

void AMonster02_BGPIXEL::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
