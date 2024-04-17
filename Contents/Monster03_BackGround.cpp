#include "PreCompile.h"
#include "Monster03_BackGround.h"

AMonster03_BackGround::AMonster03_BackGround()
{
	Back_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Back_Renderer->SetupAttachment(Renderer);
}

AMonster03_BackGround::~AMonster03_BackGround()
{
}

void AMonster03_BackGround::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));
	//Renderer->SetSprite("Monster_03.png");
	Renderer->SetSprite("IceFrontBG.png");
	Renderer->SetOrder(ERenderOrder::ForeGround);


	Back_Renderer->SetSprite("IceBackBG.png");
	Back_Renderer->SetOrder(ERenderOrder::BackGround);
}

void AMonster03_BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
