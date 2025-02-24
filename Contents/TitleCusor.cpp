#include "PreCompile.h"
#include <EnginePlatform/EngineWindow.h>
#include "TitleCusor.h"
#include "Target.h"
#include "Title_UI.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/Camera.h>

TitleCusor::TitleCusor()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Renderer);
	Collision->SetCollisionGroup(EColOrder::Cursor);
	Collision->SetCollisionType(ECollisionType::CirCle);
}

TitleCusor::~TitleCusor()
{
}

void TitleCusor::BeginPlay()
{
	Super::BeginPlay();
	//SetActorScale3D(FVector(32.0f, 32.0f, 100.0f));
	Renderer->SetSprite("BasicCursor.png");
	Renderer->SetAutoSize(4.f, true);
	Renderer->SetOrder(ERenderOrder::Cursor);
}

void TitleCusor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	{
		std::string Msg = std::format("TitleCursorPos : {}\n", Renderer->GetWorldPosition().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}



	Collision->CollisionStay(EColOrder::GameStart_UI, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			ATitle_UI* UI_OBJ = dynamic_cast<ATitle_UI*>(Actors);
			if (UI_OBJ != nullptr)
			{
				UI_OBJ->StartUIOn();

				if (true == UEngineInput::IsDown(VK_LBUTTON))
				{
					GEngine->ChangeLevel("TownLevel");
				}
				return;
			}
		}
	);

	Collision->CollisionStay(EColOrder::GameEnd_UI, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			ATitle_UI* UI_OBJ = dynamic_cast<ATitle_UI*>(Actors);
			if (UI_OBJ != nullptr)
			{
				UI_OBJ->EndUIOn();
				if (true == UEngineInput::IsDown(VK_LBUTTON))
				{
					GEngine->ChangeLevel("GameExit");
				}

				return;
			}
		}
	);

	Collision->CollisionExit(EColOrder::GameStart_UI, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			ATitle_UI* UI_OBJ = dynamic_cast<ATitle_UI*>(Actors);
			if (UI_OBJ != nullptr)
			{
				UI_OBJ->StartUIOff();
				return;
			}
		}
	);

	Collision->CollisionExit(EColOrder::GameEnd_UI, [=](std::shared_ptr<UCollision> _Collison)
		{
			AActor* Actors = _Collison->GetActor();
			ATitle_UI* UI_OBJ = dynamic_cast<ATitle_UI*>(Actors);
			if (UI_OBJ != nullptr)
			{
				UI_OBJ->EndUIOff();
				return;
			}
		}
	);
}

