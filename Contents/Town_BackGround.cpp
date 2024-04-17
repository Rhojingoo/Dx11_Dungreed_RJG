#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Town_BackGround.h"

ATown_BackGround::ATown_BackGround()
{
	Front_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Front_Renderer->SetupAttachment(Renderer);

	Mid_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Mid_Renderer->SetupAttachment(Renderer);

	Back_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Back_Renderer->SetupAttachment(Renderer);
}

ATown_BackGround::~ATown_BackGround()
{
}

void ATown_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));//Town
	Renderer->SetSprite("TownModel.png");  //¿øº»
	Renderer->SetOrder(ERenderOrder::PixelMap);
	
	Back_Renderer->SetSprite("Sky_Night.png");
	Back_Renderer->SetOrder(ERenderOrder::BackGround);

	Mid_Renderer->SetSprite("TownBG_Night.png");
	Mid_Renderer->SetOrder(ERenderOrder::MidGround);

	Front_Renderer->SetSprite("TownLayer_Night.png");
	Front_Renderer->SetOrder(ERenderOrder::ForeGround);
}

void ATown_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
