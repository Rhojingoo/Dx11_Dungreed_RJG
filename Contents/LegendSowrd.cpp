#include "PreCompile.h"
#include "LegendSowrd.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsHelper.h"

ALegendSowrd::ALegendSowrd()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ALegendSowrd::~ALegendSowrd()
{
}

void ALegendSowrd::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("DemonSword.png");
	Renderer->SetAutoSize(3.f, true);
	Renderer->SetOrder(9);

}

void ALegendSowrd::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
