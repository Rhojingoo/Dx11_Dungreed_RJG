#include "PreCompile.h"
#include "BackGround.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

ABackGround::ABackGround()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

ABackGround::~ABackGround()
{
}

void ABackGround::BeginPlay()
{
	Super::BeginPlay();
}

void ABackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
