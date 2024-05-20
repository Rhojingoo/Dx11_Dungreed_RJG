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
	Renderer->SetOrder(ERenderOrder::PixelMap);
}

void AMonster02_BGPIXEL::Tick(float _DeltaTime)
{
	if (true == UEngineInput::IsDown('P'))
	{
		Renderer->SetActive(false);
	}
	if (true == UEngineInput::IsDown('O'))
	{
		Renderer->SetActive(true);
	}
	Super::Tick(_DeltaTime);
}
