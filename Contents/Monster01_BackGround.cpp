#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Monster01_BackGround.h"

AMonster01_BackGround::AMonster01_BackGround()
{
}

AMonster01_BackGround::~AMonster01_BackGround()
{

}

void AMonster01_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("Monster_01.png");
}

void AMonster01_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
