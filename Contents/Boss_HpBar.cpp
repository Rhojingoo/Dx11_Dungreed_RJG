#include "PreCompile.h"
#include "Boss_HpBar.h"
#include <EngineCore/Image.h>

Boss_HpBar::Boss_HpBar()
{
}

Boss_HpBar::~Boss_HpBar()
{
}

void Boss_HpBar::BeginPlay()
{
	Super::BeginPlay();

	//PlayerLifeBase = CreateWidget<UImage>(GetWorld(), "PlayerLifeBase  ");
	//PlayerLifeBase->AddToViewPort(3);
	//PlayerLifeBase->SetSprite("PlayerLifeBase.png");
	//PlayerLifeBase->SetAutoSize(4.f, true);
	//PlayerLifeBase->SetPosition({ -450, 300 });
	//PlayerLifeBase->SetOrder(3);



	//PlayerLifeBack = CreateWidget<UImage>(GetWorld(), "PlayerLifeBack ");
	//PlayerLifeBack->AddToViewPort(0);
	//PlayerLifeBack->SetSprite("PlayerLifeBack.png");
	//PlayerLifeBack->SetAutoSize(4.f, true);
	//PlayerLifeBack->SetPosition({ -450, 300 });
	//PlayerLifeBack->SetOrder(0);


	//LifeBar = CreateWidget<UImage>(GetWorld(), "LifeBar ");
	//LifeBar->AddToViewPort(1);
	//LifeBar->SetSprite("LifeBar.png");
	////LifeBar->SetAutoSize(4.f, true);
	//LifeBar->SetParent({ PlayerLifeBase });
	//LifeBar->SetScale({ 200.f,50.f });
	////LifeBar->SetPosition({ 0, 300 });
	//LifeBar->SetOrder(1);


	//LifeBarWave = CreateWidget<UImage>(GetWorld(), "Player_LifeWave ");
	//LifeBarWave->AddToViewPort(2);
	//LifeBarWave->CreateAnimation("Player_LifeWave", "Player_LifeWave", 0.1f);
	//LifeBarWave->SetParent(LifeBar);
	//LifeBarWave->SetScale({ 0.15f,1.f });
	//LifeBarWave->AddPosition({ 0.55f,0.f });
	//LifeBarWave->SetOrder(2);
}

void Boss_HpBar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
