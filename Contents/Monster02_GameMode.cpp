#include "PreCompile.h"
#include "Monster02_GameMode.h"
#include "Player.h"
#include "Target.h"
#include "Monster02_BackGround.h"
#include "Monster02_BGPIXEL.h"
#include <EngineCore/Camera.h>

AMonster02_GameMode::AMonster02_GameMode()
{
}

AMonster02_GameMode::~AMonster02_GameMode()
{
}

void AMonster02_GameMode::LevelStart(ULevel* _PrevLevel)
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(640.0f, 360.0f, -200.0f));

	UContentsHelper::MapTex = UEngineTexture::FindRes("Monster_02PX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();
}

void AMonster02_GameMode::LevelEnd(ULevel* _NextLevel)
{
}

void AMonster02_GameMode::BeginPlay()
{
	Tile_MapName = "Monster_02_Tile";
	FixelSize[0] = 64, FixelSize[1] = 64;
	IndexCount[0] = 54, IndexCount[1] = 25;

	Super::BeginPlay();

	UContentsHelper::MapTex = UEngineTexture::FindRes("Monster_02PX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();


	Player = GetWorld()->SpawnActor<APlayer>("Player", EOBJ_Order::Player);
	Player->SetActorLocation({ 640.0f, 360.0f, 200.0f });
	FVector assad = Player->GetActorLocation();

	std::shared_ptr<ATarget> Cursor = GetWorld()->SpawnActor<ATarget>("Player2");
	Cursor->SetActorLocation({ 640.0f, 360.0f, 200.0f });

	//std::shared_ptr<AMonster02_BackGround> BackGr = GetWorld()->SpawnActor<AMonster02_BackGround>("Monster02_Bg", EOBJ_Order::BackGround);
	float TileSize = UContentsHelper::TileSize;
	float4 TexScale = UContentsHelper::MapTexScale;
	float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
	//BackGr->SetActorScale3D(ImageScale);
	//BackGr->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });


	std::shared_ptr<AMonster02_BGPIXEL> Back = GetWorld()->SpawnActor<AMonster02_BGPIXEL>("Monster02_PXBg", EOBJ_Order::PixelGround);
	Back->SetActorScale3D(ImageScale);
	Back->SetActorLocation({ ImageScale.hX(), ImageScale.hY(), 500.0f });
}

void AMonster02_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("Mon03_Level");
		//BossLevel
	}
	Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
}
