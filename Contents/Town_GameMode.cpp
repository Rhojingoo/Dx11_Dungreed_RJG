#include "PreCompile.h"
#include "Town_GameMode.h"
#include "Player.h"
#include "Town_BackGround.h"
#include "Town_BGPIXEL.h"
#include <EngineCore/Camera.h>
#include "ContentsHelper.h"



ATown_GameMode::ATown_GameMode()
{
}

ATown_GameMode::~ATown_GameMode()
{
}

void ATown_GameMode::BeginPlay()
{
	Super::BeginPlay();

	UContentsHelper::MapTex = UEngineTexture::FindRes("TownModelPX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(640.0f, -360.0f, -200.0f));


	std::shared_ptr<APlayer> Actor = GetWorld()->SpawnActor<APlayer>("Player");
	Actors = Actor;
	Actor->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	FVector assad = Actor->GetActorLocation();

	{
		std::shared_ptr<ATown_BackGround> BackGr = GetWorld()->SpawnActor<ATown_BackGround>("TOWNBack");
		float TileSize = UContentsHelper::TileSize;
		float4 TexScale = UContentsHelper::MapTexScale;
		//float4 ImageScale = { TexScale.X /** TileSize*/, TexScale.Y /** TileSize*/, 0.0f };
		BackGr->SetActorScale3D(TexScale);
		BackGr->SetActorLocation({ TexScale.hX(), -TexScale.hY(), 500.0f });
	}



	std::shared_ptr<ATown_BGPIXEL> Back = GetWorld()->SpawnActor<ATown_BGPIXEL>("TOWNBackPX");
	float4 ImageScale = UContentsHelper::MapTexScale;
	Back->SetActorScale3D(ImageScale);
	//float TileSize = UContentsHelper::TileSize;
	//float4 ImageScale = { TexScale.X /** TileSize*/, TexScale.Y /** TileSize*/, 0.0f };
	Back->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	int a = 0;
}

void ATown_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("BossLevel");
	}


	Camera->SetActorLocation({ Actors->GetActorLocation().X, Actors->GetActorLocation().Y });
}
