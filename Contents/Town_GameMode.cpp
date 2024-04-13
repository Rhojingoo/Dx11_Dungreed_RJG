#include "PreCompile.h"
#include "Town_GameMode.h"
#include "Player.h"
#include "Town_BackGround.h"
#include "Town_BGPIXEL.h"
#include <EngineCore/Camera.h>
#include "ContentsHelper.h"
#include "Target.h"



ATown_GameMode::ATown_GameMode()
{
}

ATown_GameMode::~ATown_GameMode()
{
}

void ATown_GameMode::BeginPlay()
{
	Super::BeginPlay();

	UContentsHelper::MapTex = UEngineTexture::FindRes("TownModelPX.png");//원래
	//UContentsHelper::MapTex = UEngineTexture::FindRes("Monster3_PX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(640.0f, -360.0f, -200.0f));

	std::shared_ptr<APlayer> Actor = GetWorld()->SpawnActor<APlayer>("Player", EOBJ_Order::Player);
	Actors = Actor;
	Actor->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	FVector assad = Actor->GetActorLocation();


	std::shared_ptr<ATarget> Cursor = GetWorld()->SpawnActor<ATarget>("Player2");
	Cursor->SetActorLocation({ 640.0f, -360.0f, 200.0f });	

	std::shared_ptr<ATown_BackGround> BackGr = GetWorld()->SpawnActor<ATown_BackGround>("TOWNBack", EOBJ_Order::BackGround);
	float TileSize = UContentsHelper::TileSize;
	float4 TexScale = UContentsHelper::MapTexScale;	
	//float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
	//BackGr->SetActorScale3D(ImageScale);
	//BackGr->SetActorLocation({ ImageScale.hX(), -ImageScale.hY(), 500.0f });
	BackGr->SetActorScale3D(TexScale); //원래
	BackGr->SetActorLocation({ TexScale.hX(), -TexScale.hY(), 500.0f });//원래
	
	std::shared_ptr<ATown_BGPIXEL> Back = GetWorld()->SpawnActor<ATown_BGPIXEL>("TOWNBackPX", EOBJ_Order::PixelGround);
	float4 ImageScale = UContentsHelper::MapTexScale;//원래
	Back->SetActorScale3D(ImageScale);
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
