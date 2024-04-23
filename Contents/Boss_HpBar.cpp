#include "PreCompile.h"
#include "Boss_HpBar.h"
#include <EngineCore/Image.h>

ABoss_HpBar::ABoss_HpBar()
{
}

ABoss_HpBar::~ABoss_HpBar()
{
}

void ABoss_HpBar::BeginPlay()
{
	Super::BeginPlay();

	BossLifeBase = CreateWidget<UImage>(GetWorld(), "BossLifeBase");
	BossLifeBase->AddToViewPort(3);
	BossLifeBase->SetSprite("BossLifeBase.png");
	BossLifeBase->SetAutoSize(4.f, true);

	BossLifeBase->SetOrder(3);

	BossLifeBack = CreateWidget<UImage>(GetWorld(), "BossLifeBack");
	BossLifeBack->AddToViewPort(0);
	BossLifeBack->SetSprite("BossLifeBack.png");
	BossLifeBack->SetAutoSize(4.f, true);
	//BossLifeBack->SetPosition({ 0, -280 });
	BossLifeBack->SetOrder(0);

	LifeBar = CreateWidget<UImage>(GetWorld(), "LifeBar2");
	LifeBar->AddToViewPort(1);
	LifeBar->SetSprite("LifeBar.png");
	LifeBar->SetParent({ BossLifeBase });
	LifeBar->SetScale({ 0.82f,0.9f });
	LifeBar->AddPosition({ 0.09f,0.f });
	LifeBar->SetOrder(1);
	BossLifeBase->SetPosition({ 0, -280 });

	BossHpImage = CreateWidget<UImage>(GetWorld(), "Skull");
	BossHpImage->AddToViewPort(2);
	BossHpImage->SetSprite("BossSkellPortrait.png");
	BossHpImage->SetParent({ BossLifeBack });
	BossHpImage->SetScale({ 0.15f,1.f });
	BossHpImage->AddPosition({ -0.41f,0.f });
	BossHpImage->SetOrder(2);
	BossLifeBack->SetPosition({ 0, -280 });

	MaxLife = LifeBar->GetLocalScale().X;
	Life_POSX = LifeBar->GetLocalPosition().X;
}

void ABoss_HpBar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Life = LifeBar->GetLocalScale().X;
	if (UEngineInput::IsDown('L'))
	{	
		Life -= Life / 10;
		float Setratio = (Life / MaxLife);  // 체력 비율을 계산
		float fullWidth = LifeBar->GetWorldScale().X;  // 이미지 전체 길이	
		float basePos = LifeBar->GetLocalPosition().X/2;

		LifePos = ((MaxLife / 2) * (1 - Setratio))- Life_POSX;  // 깎인 만큼 왼쪽으로 이동
		LifeBar->SetScale({ Life, 0.9f });
		LifeBar->SetPosition({ -LifePos, LifeBar->GetLocalPosition().Y });
	}
}
