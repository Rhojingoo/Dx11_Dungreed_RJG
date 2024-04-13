#include "PreCompile.h"
#include "Boss.h"
#include <EngineCore/Renderer.h>


Boss::Boss()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

Boss::~Boss()
{
}

void Boss::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(320.0f, 320.0f, 100.0f));

	//Renderer->CreateAnimation("Boss_Attack", "Boss_Attack", 0.1f);
	//Renderer->CreateAnimation("Boss_Die", "Boss_Die", 0.1f);
	//Renderer->CreateAnimation("Boss_Enter", "Boss_Enter", 0.1f);
	//Renderer->CreateAnimation("Boss_Exit", "Boss_Exit", 0.1f);
	//Renderer->CreateAnimation("Boss_Idle", "Boss_Idle", 0.1f);

	//Renderer->ChangeAnimation("Boss_Idle");
	Renderer->SetOrder(ERenderOrder::Boss);
}

void Boss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	float Speed = 100.0f;
}
