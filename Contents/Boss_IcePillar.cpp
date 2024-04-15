#include "PreCompile.h"
#include "Boss_IcePillar.h"
#include "IceBullet.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ABoss_IcePillar::ABoss_IcePillar()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetPivot(EPivot::BOT);
	Renderer->SetScale(FVector(62.0f, 33.0f, 100.0f));
	Renderer->AddPosition({ 0.0f, 0.0f, 0.0f });

	//Hand_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer1");
	//Hand_Renderer->SetupAttachment(Root);
	//Hand_Renderer->SetPivot(EPivot::BOT);
	//Hand_Renderer->CreateAnimation("Player_Hand", "Player_Hand", 0.1f);
	//Hand_Renderer->ChangeAnimation("Player_Hand");
	//Hand_Renderer->SetScale(FVector(9.0f, 9.0f, 100.0f));
	//Hand_Renderer->AddPosition({ 20.0f, 0.0f, 0.0f });

	SetRoot(Root);
}

ABoss_IcePillar::~ABoss_IcePillar()
{
}

void ABoss_IcePillar::BeginPlay()
{
	Super::BeginPlay();

	IceBullet = GetWorld()->SpawnActor<AIceBullet>("IceBullet");
	IceBullet->SetActorLocation({ 640.0f, -360.0f, 200.0f });

	Renderer->SetAutoSize(4.0f, true);
	Renderer->CreateAnimation("IcePillar", "IcePillar", 0.1f, false);
	Renderer->CreateAnimation("IcePillarDestroy", "IcePillarDestroy", 0.1f);
	Renderer->ChangeAnimation("IcePillar");
	Renderer->SetOrder(ERenderOrder::Boss_Bullet);
}

void ABoss_IcePillar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Pos = GetActorLocation();
	if (Player != nullptr)
	{
		PlayerPos = Player->GetActorLocation();
	}	
	if (UEngineInput::IsPress('1'))//VK_NUMPAD1
	{
		IceBullet->SetActorLocation(Pos);
		BulletDir = Pos - PlayerPos;
		BulletDir.Normalize2D();
		BulletDir.Z = 0;
		BulletDir.X = BulletDir.X * UEngineMath::DToR;
		BulletDir.Y = BulletDir.Y * UEngineMath::DToR;
		IceBullet->SetTarget(BulletDir);
		IceBullet->TargetOn();
	}

	AddActorRotation(float4{ 0.0f, 0.0f, 1.0f } *180.0f * _DeltaTime);
	Renderer->AddRotationDeg(float4{ 0.0f, 0.0f, 1.0f } *360.0f * _DeltaTime);
}
