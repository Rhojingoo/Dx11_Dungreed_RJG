#include "PreCompile.h"
#include "Boss_GameMode.h"
#include "MapEditorGUI.h"
#include "Player.h"
#include "Boss.h"
#include "Target.h"
#include "Boss_BackGround.h"
#include "Boss_BGPIXEL.h"
#include <EngineCore/Camera.h>

ABoss_GameMode::ABoss_GameMode()
{
}

ABoss_GameMode::~ABoss_GameMode()
{
}

void ABoss_GameMode::SetMapEdit()
{
}

void ABoss_GameMode::LevelStart(ULevel* _PrevLevel)
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(640.0f, 360.0f, -200.0f));

	Player = GetWorld()->SpawnActor<APlayer>("Player", EOBJ_Order::Player);
	Player->SetActorLocation({ 640.0f, 360.0f, 200.0f });

	Cursor = GetWorld()->SpawnActor<ATarget>("Player2");
	Cursor->SetActorLocation({ 640.0f, -360.0f, 200.0f });

	Boss = GetWorld()->SpawnActor<ABoss>("Boss", EOBJ_Order::Monster);
	Boss->SetActorLocation({ 1200.0f, 750.0f, 200.0f });
	Boss->SetPlayer(Player);

	UContentsHelper::MapTex = UEngineTexture::FindRes("NIflheimRoom_Pixel.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();
}

void ABoss_GameMode::LevelEnd(ULevel* _NextLevel)
{
	Camera->Destroy();
	Player->Destroy();
	Cursor->Destroy();
	Boss->Destroy();
}

void ABoss_GameMode::BeginPlay()
{
	Tile_MapName = "NIflheimRoom_Tile";
	FixelSize[0] = 64, FixelSize[1] = 64;
	IndexCount[0] = 40, IndexCount[1] = 20;

	Super::BeginPlay();

	UContentsHelper::MapTex = UEngineTexture::FindRes("NIflheimRoom_Pixel.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();
	

	std::shared_ptr<ABoss_BackGround> BackGr = GetWorld()->SpawnActor<ABoss_BackGround>("Boss_Bg", EOBJ_Order::BackGround);
	float TileSize = UContentsHelper::TileSize;
	float4 TexScale = UContentsHelper::MapTexScale;
	float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
	BackGr->SetActorScale3D(ImageScale);
	BackGr->SetActorLocation({ ImageScale.hX(), ImageScale.hY(), 500.0f });


	std::shared_ptr<ABoss_BGPIXEL> Back = GetWorld()->SpawnActor<ABoss_BGPIXEL>("BossBackPX", EOBJ_Order::PixelGround);
	Back->SetActorScale3D(ImageScale);
	Back->SetActorLocation({ ImageScale.hX(), ImageScale.hY(), 500.0f });
}

void ABoss_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		//GEngine->ChangeLevel("BossLevel");
	}
	if (Camera != nullptr)
	{
		Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
	}
}
