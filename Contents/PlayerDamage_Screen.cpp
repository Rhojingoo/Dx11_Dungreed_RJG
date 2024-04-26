#include "PreCompile.h"
#include "PlayerDamage_Screen.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsHelper.h"
#include <EngineCore/Image.h>
#include "Player_Smoke_Effect.h"

APlayerDamage_Screen::APlayerDamage_Screen()
{	
}

APlayerDamage_Screen::~APlayerDamage_Screen()
{
}

void APlayerDamage_Screen::BeginPlay()
{
	Super::BeginPlay();


	/*PlayerLifeBase = CreateWidget<UImage>(GetWorld(), "PlayerLifeBase");
	PlayerLifeBase->AddToViewPort(3);
	PlayerLifeBase->SetSprite("PlayerLifeBase.png");
	PlayerLifeBase->SetAutoSize(4.f, true);
	PlayerLifeBase->SetPosition({ -450, 300 });
	PlayerLifeBase->SetOrder(3);*/


	Renderer = CreateWidget<UImage>(GetWorld(), "PlayerDamage_SCREEN");
	Renderer->AddToViewPort(1);
	Renderer->SetSprite("RedWarningOnHit.png");
	Renderer->SetAutoSize(1.f, true);
	Renderer->SetPosition({ 0, 0 });
	//Renderer->SetPlusColor()
	Renderer->SetPlusColor({ RedColor,0.f,0.f });
	Renderer->SetOrder(1);
}

void APlayerDamage_Screen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (RedColor <= 0.f)
	{
		Renderer->SetActive(false);
		Destroy();
	}
	else
	{
		RedColor -= 1000.f*_DeltaTime;
		Renderer->SetPlusColor({ RedColor,0.f,0.f });
	}
}

