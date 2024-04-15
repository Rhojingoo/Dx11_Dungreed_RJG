#include "PreCompile.h"
#include "Test_GameMode.h"
#include "Player.h"
#include "Target.h"
#include "Boss_BackGround.h"
#include "Boss_BGPIXEL.h"
#include <EngineCore/Camera.h>


ATest_GameMode::ATest_GameMode()
{
}

ATest_GameMode::~ATest_GameMode()
{
}

void ATest_GameMode::LevelStart(ULevel* _PrevLevel)
{
}

void ATest_GameMode::LevelEnd(ULevel* _NextLevel)
{
}

void ATest_GameMode::BeginPlay()
{
	Super::BeginPlay();
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(640.0f, -360.0f, -200.0f));


}

void ATest_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("TownLevel");
	}
	//Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
}
