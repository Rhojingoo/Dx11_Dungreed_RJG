#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Title_Bird.h"

ATitle_Bird::ATitle_Bird()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

ATitle_Bird::~ATitle_Bird()
{
}

void ATitle_Bird::BeginPlay()
{
	Super::BeginPlay();
	Renderer->CreateAnimation("run", "Title_Bird.png", 0.1f);
	Renderer->ChangeAnimation("run");
}

void ATitle_Bird::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

