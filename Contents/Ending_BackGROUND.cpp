#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Ending_BackGROUND.h"
#include <EngineCore/TextWidget.h>
#include <EngineCore/EngineEditorGUI.h>


AEnding_BackGROUND::AEnding_BackGROUND()
{
}

AEnding_BackGROUND::~AEnding_BackGROUND()
{
}

void AEnding_BackGROUND::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));//Town
	Renderer->SetSprite("Ending_Exit.png");  //원본
	Renderer->SetOrder(ERenderOrder::BackGround);
	Renderer->SetAutoSize(4.0f, true);

	{
		TextImage = CreateWidget<UTextWidget>(GetWorld(), "Test");
		TextImage->SetFont("HY견고딕");
		TextImage->AddToViewPort(5);
		TextImage->SetScale(50.0f);
		TextImage->SetColor(Color8Bit::White);
		//TextImage->SetPosition({ -535, -185 });
		TextImage->SetText("시청해 주셔서 감사합니다.");
	}
}

void AEnding_BackGROUND::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
