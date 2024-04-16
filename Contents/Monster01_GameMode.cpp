#include "PreCompile.h"
#include "Monster01_GameMode.h"
#include "Player.h"
#include "Target.h"
#include "Monster01_BackGround.h"
#include "Monster01_BGPIXEL.h"
#include <EngineCore/Camera.h>

AMonster01_GameMode::AMonster01_GameMode()
{
}

AMonster01_GameMode::~AMonster01_GameMode()
{
}

void AMonster01_GameMode::LevelStart(ULevel* _PrevLevel)
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(640.0f, 360.0f, -200.0f));

	UContentsHelper::MapTex = UEngineTexture::FindRes("Monster_01PX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();
}

void AMonster01_GameMode::LevelEnd(ULevel* _NextLevel)
{
	
}

void AMonster01_GameMode::BeginPlay()
{
	Super::BeginPlay();

	UContentsHelper::MapTex = UEngineTexture::FindRes("Monster_01PX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();


	Player = GetWorld()->SpawnActor<APlayer>("Player", EOBJ_Order::Player);
	Player->SetActorLocation({ 640.0f, 360.0f, 200.0f });
	FVector assad = Player->GetActorLocation();

	std::shared_ptr<ATarget> Cursor = GetWorld()->SpawnActor<ATarget>("Player2");
	Cursor->SetActorLocation({ 640.0f, 360.0f, 200.0f });

	//std::shared_ptr<AMonster01_BackGround> BackGr = GetWorld()->SpawnActor<AMonster01_BackGround>("Monster01_Bg", EOBJ_Order::BackGround);
	float TileSize = UContentsHelper::TileSize;
	float4 TexScale = UContentsHelper::MapTexScale;
	float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
	//BackGr->SetActorScale3D(ImageScale);
	//BackGr->SetActorLocation({ ImageScale.hX(), ImageScale.hY(), 500.0f });


	std::shared_ptr<AMonster01_BGPIXEL> Back = GetWorld()->SpawnActor<AMonster01_BGPIXEL>("Monster_01PX", EOBJ_Order::PixelGround);
	Back->SetActorScale3D(ImageScale);
	Back->SetActorLocation({ ImageScale.hX(), ImageScale.hY()- TexScale.Y , 500.0f});
}

void AMonster01_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("Mon02_Level");
	}
	Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
}
