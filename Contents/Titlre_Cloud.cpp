#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Titlre_Cloud.h"

ATitlre_Cloud::ATitlre_Cloud()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

ATitlre_Cloud::~ATitlre_Cloud()
{
}

void ATitlre_Cloud::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(750.0f, 250.0f, 99.0f));
	SetActorLocation(FVector(0.0f, 0.0f, .0f));
	Renderer->SetSprite("Cloud1.png");
	Renderer->SetAutoSize(0.8f, true);
	Renderer->SetOrder(1);
}

void ATitlre_Cloud::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

