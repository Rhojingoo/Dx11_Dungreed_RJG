#include "PreCompile.h"
#include "Monster03_GameMode.h"
#include "Player.h"
#include "Target.h"
#include "Monster03_BackGround.h"
#include "Monster03_BGPIXEL.h"
#include <EngineCore/Camera.h>

AMonster03_GameMode::AMonster03_GameMode()
{
}

AMonster03_GameMode::~AMonster03_GameMode()
{
}

void AMonster03_GameMode::LevelStart(ULevel* _PrevLevel)
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(640.0f, 360.0f, -200.0f));

	UContentsHelper::MapTex = UEngineTexture::FindRes("Monster_03PX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();
}

void AMonster03_GameMode::LevelEnd(ULevel* _NextLevel)
{
}

void AMonster03_GameMode::BeginPlay()
{
	Super::BeginPlay();

	UContentsHelper::MapTex = UEngineTexture::FindRes("Monster_03PX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();


	Player = GetWorld()->SpawnActor<APlayer>("Player", EOBJ_Order::Player);
	Player->SetActorLocation({ 640.0f, 360.0f, 200.0f });
	FVector assad = Player->GetActorLocation();

	std::shared_ptr<ATarget> Cursor = GetWorld()->SpawnActor<ATarget>("Player2");
	Cursor->SetActorLocation({ 640.0f, 360.0f, 200.0f });

	//std::shared_ptr<AMonster03_BackGround> BackGr = GetWorld()->SpawnActor<AMonster03_BackGround>("Monster03_Bg", EOBJ_Order::BackGround);
	float TileSize = UContentsHelper::TileSize;
	float4 TexScale = UContentsHelper::MapTexScale;
	float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
	//BackGr->SetActorScale3D(ImageScale);
	//BackGr->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });


	std::shared_ptr<AMonster03_BGPIXEL> Back = GetWorld()->SpawnActor<AMonster03_BGPIXEL>("Monster03_PXBg", EOBJ_Order::PixelGround);
	Back->SetActorScale3D(ImageScale);
	Back->SetActorLocation({ ImageScale.hX(), ImageScale.hY() - TexScale.Y, 500.0f });
}

void AMonster03_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("BossLevel");
	}
	Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
}
