#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Town_BGPIXEL.h"

ATown_BGPIXEL::ATown_BGPIXEL()
{
}

ATown_BGPIXEL::~ATown_BGPIXEL()
{
}

void ATown_BGPIXEL::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("TownModelPX.png"); // 원래
	Renderer->SetOrder(ERenderOrder::Effect_Back);//원래
	Renderer->SetActive(false);
}

void ATown_BGPIXEL::Tick(float _DeltaTime)
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

