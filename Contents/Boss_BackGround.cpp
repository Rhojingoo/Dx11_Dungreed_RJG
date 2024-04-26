#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Boss_BackGround.h"

ABoss_BackGround::ABoss_BackGround()
{
	Mid_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Mid_Renderer->SetupAttachment(Renderer);

	Back_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Back_Renderer->SetupAttachment(Renderer);

	Front_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Front_Renderer->SetupAttachment(Renderer);
}

ABoss_BackGround::~ABoss_BackGround()
{
}

void ABoss_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	//Renderer->SetSprite("NIflheimRoom_00.png"); 
	Renderer->SetSprite("BossMap_MID.png");
	Renderer->SetOrder(ERenderOrder::ForeGround);

	Mid_Renderer->SetSprite("IceFrontBG.png");
	Mid_Renderer->SetOrder(ERenderOrder::MidGround);

	Back_Renderer->SetSprite("IceBackBG.png");
	Back_Renderer->SetOrder(ERenderOrder::BackGround);

	Front_Renderer->SetSprite("Snow.Png");
	Front_Renderer->SetOrder(ERenderOrder::Effect_Back);

	//Renderer->SetSprite("Ice_NIflheim_foothold.bmp");
	//Renderer->SetSprite("Ice_NIflheim.bmp");
}

void ABoss_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FrontVertexplus.X -= _DeltaTime * 1.f;
	FrontVertexplus.Y -= _DeltaTime * 1.f;
	Front_Renderer->SetVertexUVPlus(FrontVertexplus);	
}
