#include "PreCompile.h"
#include "Monster02_BackGround.h"

AMonster02_BackGround::AMonster02_BackGround()
{
}

AMonster02_BackGround::~AMonster02_BackGround()
{
}

void AMonster02_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("Monster_02.png");
}

void AMonster02_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
