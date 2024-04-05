#include "PreCompile.h"
#include "BackGround.h"
#include <EngineCore/Renderer.h>

ABackGround::ABackGround()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ABackGround::~ABackGround()
{
}

void ABackGround::BeginPlay()
{
	Super::BeginPlay();
	//SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	//Renderer->SetSprite("MainLogo.png");

	//Renderer->SetSprite("NIflheimRoom.bmp");

}

void ABackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
