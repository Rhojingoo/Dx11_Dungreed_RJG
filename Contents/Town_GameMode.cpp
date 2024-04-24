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

	UContentsHelper::MapTex = UEngineTexture::FindRes("TownModelPX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();
	Player->SetColTown();
}

void ATown_GameMode::LevelEnd(ULevel* _NextLevel)
{
}

void ATown_GameMode::BeginPlay()
{
	Super::BeginPlay();

	UContentsHelper::MapTex = UEngineTexture::FindRes("TownModelPX.png");//원래 통짜맵 사용할때
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();

	Player = GetWorld()->SpawnActor<APlayer>("Player", EOBJ_Order::Player);
	Player->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	Player->SetColTown();

	Boss = GetWorld()->SpawnActor<ABoss>("Boss", EOBJ_Order::Monster);
	Boss->SetActorLocation({ 1040.0f, -750.0f, 200.0f });
	Boss->SetPlayer(Player);
	Boss->SetTOWN();


	std::shared_ptr<ATarget> Cursor = GetWorld()->SpawnActor<ATarget>("Player2");
	Cursor->SetActorLocation({ 640.0f, -360.0f, 200.0f });	

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
	Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
}
