#include "PreCompile.h"
#include <EngineCore/Image.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Monster_HpBar.h"

AMonster_HpBar::AMonster_HpBar()
{
	//Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	LifeBack = CreateDefaultSubObject<USpriteRenderer>("PlayerLifeBack");
	SetRoot(LifeBack);
	//LifeBack->SetupAttachment(Root);

	LifeBar = CreateDefaultSubObject<USpriteRenderer>("LifeBar");
	LifeBar->SetupAttachment(LifeBack);

	//SetRoot(Root);
}

AMonster_HpBar::~AMonster_HpBar()
{
}

void AMonster_HpBar::BeginPlay()
{
	Super::BeginPlay();

	LifeBack->SetOrder(0);	
	LifeBack->SetSprite("PlayerLifeBack.png");
	LifeBar->SetScale({ 300.f,300.f });
	//LifeBack->SetAutoSize(200.f, true);
	LifeBack->AddPosition({ 0, -100 });

	LifeBar->SetOrder(1);
	LifeBar->SetSprite("LifeBar.png");
	//LifeBar->SetParent({ LifeBack });
	LifeBar->SetScale({ 300.f,350.f });
}

void AMonster_HpBar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
