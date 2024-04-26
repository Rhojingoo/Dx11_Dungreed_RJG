#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include "Title_Bird.h"

ATitle_Bird::ATitle_Bird()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

ATitle_Bird::~ATitle_Bird()
{
}

void ATitle_Bird::BeginPlay()
{
	Super::BeginPlay();
	Renderer->CreateAnimation("run", "Title_Bird.png", 0.1f);
	Renderer->ChangeAnimation("run");
	Renderer->SetOrder(ERenderOrder::Effect_Front);
	Renderer->SetAutoSize(4.f, true);
}

void ATitle_Bird::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	{
		std::string Msg = std::format("TitleBirdPos : {}\n", Renderer->GetWorldPosition().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	AddActorLocation({ 150.f * _DeltaTime,0.f,0.f });

	if (Renderer->GetWorldPosition().X > 2550.f)
	{
		float SetY = UContentsHelper::Random(-175.f, 250.f);
		SetActorLocation({ -700.f,SetY , 201.f });
	}
}

