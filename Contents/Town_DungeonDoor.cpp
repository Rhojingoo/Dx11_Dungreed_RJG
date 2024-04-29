#include "PreCompile.h"
#include "Town_DungeonDoor.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteInstancingRender.h>
#include "FadeIn_OUT_Black.h"


ATown_DungeonDoor::ATown_DungeonDoor()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(EColOrder::Door);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

ATown_DungeonDoor::~ATown_DungeonDoor()
{
}

void ATown_DungeonDoor::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetAutoSize(4.0f, true);
	Renderer->CreateAnimation("DungeonIngurgitate", "DungeonIngurgitate", 0.1f, false);
	Renderer->CreateAnimation("DungeonIngurgitate50", "DungeonIngurgitate50.png", 0.1f, false);
	Renderer->CreateAnimation("DungeonIngurgitate18", "DungeonIngurgitate18.png", 0.1f, false);
	Renderer->ChangeAnimation("DungeonIngurgitate");
	Renderer->SetOrder(ERenderOrder::Door);	
}

void ATown_DungeonDoor::Tick(float _DeltaTime)
{
	Collision->SetScale({ Renderer->GetLocalScale() });
	{

		std::string Msg = std::format("DoorCollisionPos : {}\n", Collision->GetWorldPosition().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);

		std::string Msg2 = std::format("DoorCollisionScale : {}\n", Collision->GetWorldScale().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg2);

		std::string Msg3 = std::format("DoorRendererPos : {}\n", Renderer->GetWorldPosition().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg3);

		std::string Msg4 = std::format("DoorRendererScale : {}\n", Renderer->GetWorldScale().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg4);
	}


	Super::Tick(_DeltaTime);
	if (ColCheck == true)
	{
		if (Renderer->IsCurAnimationEnd() == true)
		{
			Time += _DeltaTime*30;
			if (FadeStart == false)
			{
				Fade = GetWorld()->GetLastTarget()->AddEffect<AFadeIn_OUT_Black>();
				Fadeprt = Fade.get();
				FadeStart = true;
			}
			if (Time > 1.0)
			{
				Fadeprt->Active(false);
				Time = 0.f;
				GEngine->ChangeLevel("Mon01_Level");
			}
		}
	}
}

void ATown_DungeonDoor::Dungeon_Enter()
{
	ColCheck = true;
	Renderer->AnimationReset();
	Renderer->ChangeAnimation("DungeonIngurgitate");
}
