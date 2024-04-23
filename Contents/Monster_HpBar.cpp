#include "PreCompile.h"
#include <EngineCore/Image.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Monster_HpBar.h"

AMonster_HpBar::AMonster_HpBar()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	LifeBack = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	LifeBack->SetupAttachment(Root);
	LifeBack->SetPivot(EPivot::BOT);
	LifeBack->SetScale(FVector(74.0f, 16.0f, 100.0f));
	LifeBack->AddPosition({ 0.0f, 0.0f, 0.0f });

	LifeBar = CreateDefaultSubObject<USpriteRenderer>("LifeBar");
	LifeBar->SetupAttachment(LifeBack);
	LifeBar->SetPivot(EPivot::BOT);
	LifeBar->SetScale(FVector(1.0f, 10.0f, 100.0f));
	LifeBar->AddPosition({ 0.0f, 0.0f, 0.0f });

	SetRoot(Root);
}

AMonster_HpBar::~AMonster_HpBar()
{
}

void AMonster_HpBar::BeginPlay()
{
	Super::BeginPlay();

	LifeBack->SetSprite("PlayerLifeBack.png");
	LifeBack->SetOrder(ERenderOrder::Monster_HpBack);
	LifeBack->SetAutoSize(1.0f, true);

	LifeBar->SetSprite("LifeBar.png");
	LifeBar->SetOrder(ERenderOrder::Monster_Hp);
	LifeBar->AddPosition({ 0.f,0.5f });
	LifeBar->SetAutoSize(0.1f, true);
	LifeBar->AddScale({ 1.f,0.f });

	MaxLife = LifeBar->GetLocalScale().X;
}

void AMonster_HpBar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Life = LifeBar->GetLocalScale().X;

	if (UEngineInput::IsDown('N'))
	{
		Life -= Life/10;
		float Setratio = (Life / MaxLife);  // 체력 비율을 계산
		float fullWidth = LifeBar->GetWorldScale().X;  // 이미지 전체 길이		
		LifePos =  ((MaxLife / 2) * (1 - Setratio));  // 깎인 만큼 왼쪽으로 이동
		LifeBar->SetScale({ Life, 1.f });
		LifeBar->SetPosition({ -LifePos, LifeBar->GetLocalPosition().Y });
	}
}
