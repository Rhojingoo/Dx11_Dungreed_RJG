#include "PreCompile.h"
#include "Title_Logo.h"
#include <EngineCore/Renderer.h>


ATitle_Logo::ATitle_Logo()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ATitle_Logo::~ATitle_Logo()
{
}

void ATitle_Logo::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(750.0f, 250.0f, 99.0f));
	SetActorLocation(FVector(0.0f, 150.0f, .0f));
	Renderer->SetSprite("MainLogo.png");
	Renderer->SetAutoSize(4.5f, true);
	Renderer->SetOrder(1);
}

void ATitle_Logo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

