#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Titlre_Cloud.h"

ATitlre_Cloud::ATitlre_Cloud()
{
	FrontCloud_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	BackCloud_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	BackCloud_Renderer->SetupAttachment(FrontCloud_Renderer);

	SetRoot(FrontCloud_Renderer);
}

ATitlre_Cloud::~ATitlre_Cloud()
{
}

void ATitlre_Cloud::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(750.0f, 250.0f, 99.0f));
	SetActorLocation(FVector(0.0f, 0.0f, .0f));
	FrontCloud_Renderer->SetSprite("Cloud1.png");
	FrontCloud_Renderer->SetAutoSize(0.8f, true);
	FrontCloud_Renderer->SetOrder(ERenderOrder::MidGround);

	BackCloud_Renderer->SetSprite("BackCloud.png");
	BackCloud_Renderer->SetAutoSize(5.f, true);
	BackCloud_Renderer->SetOrder(ERenderOrder::ForeGround);


	
}

void ATitlre_Cloud::Tick(float _DeltaTime)
{
	Vertexplus.X += _DeltaTime*0.05f;

	FrontCloud_Renderer->SetVertexUVPlus(Vertexplus);

	BackCloud_Renderer->SetVertexUVPlus(Vertexplus);

	Super::Tick(_DeltaTime);
}

