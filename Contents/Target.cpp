#include "PreCompile.h"
#include "Player.h"
#include "Target.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/Camera.h>

ATarget::ATarget()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ATarget::~ATarget()
{
}

void ATarget::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(32.0f, 32.0f, 100.0f));
	Renderer->SetSprite("Target.png");
	Renderer->SetOrder(8);

}

void ATarget::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	//float4 Pos = GEngine->EngineWindow.GetScreenMousePos();

	FVector MousePos = GEngine->EngineWindow.GetScreenMousePos();
	FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	FVector PlayerPos = GetActorLocation();

	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();
	TargetPos =
		FVector(CameraPos.X, CameraPos.Y, 0.f) +
		FVector(MousePos.X - WindowScale.hX(), -(MousePos.Y - WindowScale.hY()), 199.f);

	SetActorLocation({ TargetPos });
}

