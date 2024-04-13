#include "PreCompile.h"
#include "Monster03_BackGround.h"

AMonster03_BackGround::AMonster03_BackGround()
{
}

AMonster03_BackGround::~AMonster03_BackGround()
{
}

void AMonster03_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("Monster_03.png");
}

void AMonster03_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
