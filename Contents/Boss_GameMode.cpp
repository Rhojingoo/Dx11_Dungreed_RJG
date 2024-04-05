#include "PreCompile.h"
#include "Boss_GameMode.h"
#include "Player.h"
#include "Boss_BackGround.h"
#include <EngineCore/Camera.h>

ABoss_GameMode::ABoss_GameMode()
{
}

ABoss_GameMode::~ABoss_GameMode()
{
}

void ABoss_GameMode::BeginPlay()
{
	Super::BeginPlay();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	GetWorld()->SpawnActor<ABoss_BackGround>("Boss_Bg");
	//GetWorld()->SpawnActor<APlayer>("Player");
}

void ABoss_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
