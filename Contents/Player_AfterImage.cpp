#include "PreCompile.h"
#include "Player_AfterImage.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsHelper.h"


APlayer_AfterImage::APlayer_AfterImage()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderers");
	SetRoot(Renderer);
}

APlayer_AfterImage::~APlayer_AfterImage()
{

}

void APlayer_AfterImage::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetPivot(EPivot::BOT);
	Renderer->CreateAnimation("Player_AfterImage", "Player_Jump", 0.1f);
	Renderer->CreateAnimation("Player_AfterImageEnd", "Afterimage.png", 0.1f);	
	Renderer->SetAutoSize(3.f, true);
	Renderer->SetOrder(ERenderOrder::AfterImage);
	//Renderer->ChangeAnimation("Player_AfterImage");
}

void APlayer_AfterImage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (Switch == true)
	{		
		//Color.X = .f;
		//Renderer->SetPlusColor(Color);
		//Switch = false;
		if (Color.X < 1.f)
		{
			Color.X += /*10.f * */_DeltaTime*2.f;
			Color.Z += /*10.f * */ _DeltaTime*2.f;
			Color.Y += /*10.f * */ _DeltaTime*2.f;
			Color.W += /*10.f * */ _DeltaTime*2.0f;
			Renderer->SetPlusColor(Color);
		}
		else
		{
			Renderer->ChangeAnimation("Player_AfterImageEnd");		
			Switch = false;
		}
	}
}
