#include "PreCompile.h"
#include "Player_Hand.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>


APlayer_Hand::APlayer_Hand()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

}


APlayer_Hand::~APlayer_Hand()
{
}

void APlayer_Hand::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(320.0f, 320.0f, 100.0f));
	//Renderer->SetSprite("CuttingTest.png", 11);

	Renderer->CreateAnimation("Player_Hand", "Player_Hand", 0.1f);
	Renderer->ChangeAnimation("Player_Hand");

	Renderer->SetAutoSize(3.f, true);

	Renderer->SetOrder(8);

}

void APlayer_Hand::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

