#include "PreCompile.h"
#include "Town_GameMode.h"
#include "Player.h"
#include "Boss.h"
#include "Town_BackGround.h"
#include "Town_BGPIXEL.h"
#include <EngineCore/Camera.h>
#include "ContentsHelper.h"
#include "Target.h"
#include <EngineCore/Image.h>
#include "Town_DungeonDoor.h"
#include "MiniBat.h"
#include "RedGinatBat.h"

ATown_GameMode::ATown_GameMode()
{
}

ATown_GameMode::~ATown_GameMode()
{
}

void ATown_GameMode::LevelStart(ULevel* _PrevLevel)
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(640.0f, -360.0f, -200.0f));

	Player = GetWorld()->SpawnActor<APlayer>("Player", EOBJ_Order::Player);
	Player->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	Player->SetColTown();
	Cursor = GetWorld()->SpawnActor<ATarget>("Player2");
	Cursor->SetActorLocation({ 640.0f, -360.0f, 200.0f });

	UContentsHelper::MapTex = UEngineTexture::FindRes("TownModelPX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();

	Town_Door = GetWorld()->SpawnActor<ATown_DungeonDoor>("Door", EOBJ_Order::Door);
	Town_Door->SetActorLocation({ 5050.0f, -1450.0f, 200.0f });
}

void ATown_GameMode::LevelEnd(ULevel* _NextLevel)
{
	Player->Destroy();
	Camera->Destroy();
	Cursor->Destroy();
	Town_Door->Destroy();
}

void ATown_GameMode::BeginPlay()
{
	Super::BeginPlay();

	UContentsHelper::MapTex = UEngineTexture::FindRes("TownModelPX.png");//원래 통짜맵 사용할때
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();

	std::shared_ptr<ATown_BackGround> BackGr = GetWorld()->SpawnActor<ATown_BackGround>("TOWNBack", EOBJ_Order::BackGround);
	float TileSize = UContentsHelper::TileSize;
	float4 TexScale = UContentsHelper::MapTexScale;	
	BackGr->SetActorScale3D(TexScale); //통짜맵 사용할때
	BackGr->SetActorLocation({ TexScale.hX(), -TexScale.hY(), 500.0f });//통짜맵 사용할때
	
	std::shared_ptr<ATown_BGPIXEL> Back = GetWorld()->SpawnActor<ATown_BGPIXEL>("TOWNBackPX", EOBJ_Order::PixelGround);
	float4 ImageScale = UContentsHelper::MapTexScale;//통짜맵 사용할때
	Back->SetActorScale3D(ImageScale);
	Back->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f }); 	
}

void ATown_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("Mon01_Level");
	}
	if (Camera != nullptr)
	{
		FVector Playerpos = Player->GetActorTransform().LocalPosition;

		if (Playerpos.X > 650 && Playerpos.X < 8400 && Playerpos.Y < -610 && Playerpos.Y > -1330)
		{
			Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
		}
		else if ((Playerpos.X <= 650 || Playerpos.X >= 8400) && Playerpos.Y < -610 && Playerpos.Y > -1330)
		{
			Camera->SetActorLocation({ Camera->GetActorLocation().X, Player->GetActorLocation().Y });
		}
		else if (Playerpos.X > 650 && Playerpos.X < 8400 && (Playerpos.Y >= -610 || Playerpos.Y <= -1330))
		{
			Camera->SetActorLocation({ Player->GetActorLocation().X, Camera->GetActorLocation().Y });
		}

	}
}
