#include "PreCompile.h"
#include "Boss.h"
#include "Boss_IcePillar.h"
#include "Player.h"
#include <EngineCore/Renderer.h>


ABoss::ABoss()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
	Renderer->SetPivot(EPivot::BOT);
}

ABoss::~ABoss()
{
}

void ABoss::SetPlayer(std::shared_ptr<APlayer> _Set)
{
	Player = _Set;
	for (int Num = 0; Num < 4; Num++)
	{
		IcePillar[Num]->SetPlayer(_Set);
	}
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
	//SetActorScale3D(FVector(320.0f, 320.0f, 100.0f));

	for (int Num = 0; Num < 4; Num++)
	{
		IcePillar[Num] = GetWorld()->SpawnActor<ABoss_IcePillar>("IcePillar_01");
		IcePillar[Num]->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	}
	IcePillar[0]->SetPos({ -200.f,200.f });
	IcePillar[1]->SetPos({ 200.f,200.f });
	IcePillar[2]->SetPos({ -200.f,-200.f });
	IcePillar[3]->SetPos({ 200.f,-200.f });


	Renderer->CreateAnimation("Boss_Attack", "Boss_Attack", 0.1f);
	Renderer->CreateAnimation("Boss_Die", "Boss_Die", 0.1f);
	Renderer->CreateAnimation("Boss_Enter", "Boss_Enter", 0.1f);
	Renderer->CreateAnimation("Boss_Exit", "Boss_Exit", 0.1f);
	Renderer->CreateAnimation("Boss_Idle", "Boss_Idle", 0.1f);

	Renderer->SetAutoSize(3.f, true);
	Renderer->ChangeAnimation("Boss_Idle");
	Renderer->SetOrder(ERenderOrder::Boss);
}

void ABoss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FVector BossPos = GetActorLocation();
	for (int Num = 0; Num < 4; Num++)
	{
		IcePillar[Num]->SetActorLocation({BossPos});
	}
}
