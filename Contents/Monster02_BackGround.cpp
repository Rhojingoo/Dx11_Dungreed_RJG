#include "PreCompile.h"
#include "Monster02_BackGround.h"

AMonster02_BackGround::AMonster02_BackGround()
{
	Mid_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Mid_Renderer->SetupAttachment(Renderer);

	Back_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Back_Renderer->SetupAttachment(Renderer);
}

AMonster02_BackGround::~AMonster02_BackGround()
{
}

void AMonster02_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	Renderer->SetSprite("Monster_02MID.png");
	Renderer->SetOrder(ERenderOrder::ForeGround);

	Mid_Renderer->SetSprite("IceFrontBG.png");
	Mid_Renderer->SetOrder(ERenderOrder::MidGround);

	Back_Renderer->SetSprite("IceBackBG.png");
	Back_Renderer->SetOrder(ERenderOrder::BackGround);
}

void AMonster02_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
