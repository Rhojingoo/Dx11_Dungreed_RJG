#include "PreCompile.h"
#include "TitleMode.h"
#include "Player.h"
#include "BackGround.h"
#include <EngineCore/Camera.h>

ATitleMode::ATitleMode()
{
}

ATitleMode::~ATitleMode()
{
}

void ATitleMode::BeginPlay()
{
	Super::BeginPlay();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	GetWorld()->SpawnActor<ABackGround>("Title_Logo");
	//GetWorld()->SpawnActor<APlayer>("Player");
}

void ATitleMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}