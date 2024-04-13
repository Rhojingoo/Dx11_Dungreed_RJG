#include "PreCompile.h"
#include "Player_Attack_Effect.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsHelper.h"

APlayer_Attack_Effect::APlayer_Attack_Effect()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderers");
	SetRoot(Renderer);
	//Renderer->SetPivot(EPivot::BOT);
}

APlayer_Attack_Effect::~APlayer_Attack_Effect()
{
}

void APlayer_Attack_Effect::BeginPlay()
{
	Super::BeginPlay();
	//Sword_Swing_Legend
	//Renderer->SetSprite("DemonSword.png");
	Renderer->CreateAnimation("Sword_Swing_Normal", "Sword_Swing_Normal", 0.1f, false);
	Renderer->CreateAnimation("Sword_Swing_Legend", "Sword_Swing_Legend", 0.1f, false);
	Renderer->SetAutoSize(5.f, true);
	Renderer->SetOrder(ERenderOrder::Attack_Effect);
	//Renderer->ChangeAnimation("Sword_Swing_Legend");
}

void APlayer_Attack_Effect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (Attack == true)
	{
		Renderer->ChangeAnimation("Sword_Swing_Legend");
		Attack = false;
	}

}
