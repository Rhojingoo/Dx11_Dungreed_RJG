#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Titlre_Cloud.h"

Titlre_Cloud::Titlre_Cloud()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

Titlre_Cloud::~Titlre_Cloud()
{
}

void Titlre_Cloud::BeginPlay()
{
	Super::BeginPlay();
}

void Titlre_Cloud::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

