#include "PreCompile.h"
#include "Cursor.h"
#include "ContentsHelper.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/Camera.h>

ACursor::ACursor()
{
}

ACursor::~ACursor()
{
}

void ACursor::BeginPlay()
{
	Super::BeginPlay();
}

void ACursor::Tick(float _DeltaTime)
{
	//float4 Pos = GEngine->EngineWindow.GetScreenMousePos();
	Super::Tick(_DeltaTime);
	FVector MousePos = GEngine->EngineWindow.GetScreenMousePos();
	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	FVector PlayerPos = GetActorLocation();

	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();
	TargetPos =
		FVector(CameraPos.X, CameraPos.Y, 0.f) +
		FVector(MousePos.X - WindowScale.hX(), -(MousePos.Y - WindowScale.hY()), 199.f);

	SetActorLocation({ TargetPos });
}

