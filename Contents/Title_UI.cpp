#include "PreCompile.h"
#include "Title_UI.h"
#include <EngineCore/SpriteRenderer.h>


ATitle_UI::ATitle_UI()
{
	GameStart_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");	

	GameEnd_Renderer =  CreateDefaultSubObject<USpriteRenderer>("Renderer");


	SetRoot(GameStart_Renderer);
}

ATitle_UI::~ATitle_UI()
{
}

void ATitle_UI::BeginPlay()
{
	Super::BeginPlay();

	GameStart_Renderer->SetSprite("PlayOn_Kor.png");
	//GameStart_Renderer->SetSprite("PlayOff_Kor.png");
	GameStart_Renderer->SetAutoSize(4.5f, true);
	GameStart_Renderer->SetOrder(ERenderOrder::ForeGround);

	GameEnd_Renderer->SetSprite("ExitOn_Kor.png");
	//GameEnd_Renderer->SetSprite("ExitOff_Kor.png");
	GameEnd_Renderer->SetAutoSize(4.5f, true);
	GameEnd_Renderer->SetOrder(ERenderOrder::ForeGround);
}

void ATitle_UI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
