#include "PreCompile.h"
#include "IceBullet.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

AIceBullet::AIceBullet()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
	Renderer->SetPivot(EPivot::BOT);
}

AIceBullet::~AIceBullet()
{
}

void AIceBullet::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetAutoSize(4.0f, true);

	Renderer->CreateAnimation("IceBullet", "IceBullet", 0.1f, false);
	Renderer->CreateAnimation("IceBulletEfferct", "IceBulletEfferct", 0.1f);
	Renderer->ChangeAnimation("IceBullet");
	Renderer->SetOrder(ERenderOrder::Boss_Bullet);
}

void AIceBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (TargetSwitch == true)
	{
		FVector Target = -TargetPos * Speed /** _DeltaTime*/;
		//SetActorLocation(Target);
		AddActorLocation(Target);
		float CursorAngleRad = std::atan2(TargetPos.Y, TargetPos.X);
		CursorAngleRad = CursorAngleRad *UEngineMath::RToD;
		SetActorRotation(FVector(0.0f, 0.0f, CursorAngleRad+90));
	}
}
