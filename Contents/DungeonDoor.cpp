#include "PreCompile.h"
#include "DungeonDoor.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteInstancingRender.h>
#include "FadeIn_OUT_Black.h"

ADungeonDoor::ADungeonDoor()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(EColOrder::DungeonDoor);
	Collision->SetCollisionType(ECollisionType::RotRect);

	SetRoot(Root);
}

ADungeonDoor::~ADungeonDoor()
{
}


void ADungeonDoor::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetAutoSize(4.0f, true);
	Renderer->CreateAnimation("Stele_Idle", "Stele_Idle", 0.1f, false);
	Renderer->ChangeAnimation("Stele_Idle");
	Renderer->SetOrder(ERenderOrder::Door);
	
	SetActorRotation({ 0.f, 0.f, 90.f });
}

void ADungeonDoor::Tick(float _DeltaTime)
{
	Collision->SetScale({ Renderer->GetWorldScale().X , Renderer->GetWorldScale().Y / 2,1.f });
	Super::Tick(_DeltaTime);
}


void ADungeonDoor::Dungeon_Enter()
{
	ColCheck = true;
	Renderer->AnimationReset();
	Renderer->ChangeAnimation("DungeonIngurgitate");
}
