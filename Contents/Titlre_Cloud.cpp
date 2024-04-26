#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Titlre_Cloud.h"

ATitlre_Cloud::ATitlre_Cloud()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	FrontCloud_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	FrontCloud_Renderer->SetupAttachment(Root);

	BackCloud_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	BackCloud_Renderer->SetupAttachment(Root);

	Clouds_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Clouds_Renderer->SetupAttachment(Root);

	SetRoot(Root);
}

ATitlre_Cloud::~ATitlre_Cloud()
{
}

void ATitlre_Cloud::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(750.0f, 250.0f, 99.0f));
	SetActorLocation(FVector(0.0f, 0.0f, .0f));
	FrontCloud_Renderer->SetSprite("FrontCloud.png");
	FrontCloud_Renderer->SetAutoSize(0.0159f, true);
	FrontCloud_Renderer->SetOrder(ERenderOrder::MidGround);

	BackCloud_Renderer->SetSprite("BackCloud.png");
	BackCloud_Renderer->SetAutoSize(0.0159f,true);
	BackCloud_Renderer->SetOrder(ERenderOrder::MidGround);

	Clouds_Renderer->SetSprite("Clouds.png");
	Clouds_Renderer->SetAutoSize(0.0159f, true);
	Clouds_Renderer->SetOrder(ERenderOrder::MidGround);
}

void ATitlre_Cloud::Tick(float _DeltaTime)
{
	FrontVertexplus.X -= _DeltaTime*0.005f;
	FrontCloud_Renderer->SetVertexUVPlus(FrontVertexplus);

	BackVertexplus.X -= _DeltaTime *0.015f;
	BackCloud_Renderer->SetVertexUVPlus(BackVertexplus);

	MidVertexplus.X -= _DeltaTime * 0.025f;
	Clouds_Renderer->SetVertexUVPlus(MidVertexplus);

	Super::Tick(_DeltaTime);
}

