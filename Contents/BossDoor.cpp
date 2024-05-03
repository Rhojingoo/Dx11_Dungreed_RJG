#include "PreCompile.h"
#include "BossDoor.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteInstancingRender.h>
#include "FadeIn_OUT_Black.h"

ABossDoor::ABossDoor()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(EColOrder::BossDoor);
	Collision->SetCollisionType(ECollisionType::Rect);

	SetRoot(Root);
}

ABossDoor::~ABossDoor()
{
}


void ABossDoor::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetAutoSize(4.0f, true);
	Renderer->CreateAnimation("BossDoorOpen", "BossDoorOpen", 0.1f, false);
	Renderer->CreateAnimation("BossDoorClose", "BossDoorClose", 0.1f, false);
	Renderer->ChangeAnimation("BossDoorClose");
	
	Renderer->SetOrder(ERenderOrder::Door);
}

void ABossDoor::Tick(float _DeltaTime)
{
	Collision->SetScale({ Renderer->GetWorldScale().X , Renderer->GetWorldScale().Y });
	Super::Tick(_DeltaTime);

	//Collision->SetScale({ Renderer->GetLocalScale() });

	if (BossRoomOPENStart == true)
	{
		if (Renderer->IsCurAnimationEnd() == true)
		{

			Collision->CollisionStay(EColOrder::Player, [=](std::shared_ptr<UCollision> _Collison)
				{
					AActor* Actors = _Collison->GetActor();
					APlayer* player = dynamic_cast<APlayer*>(Actors);
					if (player != nullptr)
					{
						Time += _DeltaTime * 30;
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
							GEngine->ChangeLevel("BossLevel");
						}
					}
				}
			);

		
		}
	}
}


void ABossDoor::Dungeon_Enter()
{
	//ColCheck = true;
	//Renderer->AnimationReset();
	//Renderer->ChangeAnimation("DungeonIngurgitate");
}
