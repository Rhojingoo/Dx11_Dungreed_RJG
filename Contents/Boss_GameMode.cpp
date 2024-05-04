#include "PreCompile.h"
#include "Boss_GameMode.h"
#include "MapEditorGUI.h"
#include "Player.h"
#include "Boss.h"
#include "Target.h"
#include "Boss_BackGround.h"
#include "Boss_BGPIXEL.h"
#include <EngineCore/Camera.h>
#include <EngineCore/EngineEditorGUI.h>
#include "Boss_TestSkill_GUI.h"

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
	Ambience.On();

	Camera = GetWorld()->GetMainCamera();
	//Camera->SetActorLocation(FVector(640.0f, 360.0f, -200.0f));
	Camera->SetActorLocation(FVector(840.0f, 460.0f, -200.0f));


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
	Ambience.Off();
	Camera->Destroy();
	Player->Destroy();
	Cursor->Destroy();
	Boss->SoundOFF();
	Boss->Destroy();
}

void ABoss_GameMode::BeginPlay()
{
	Tile_MapName = "NIflheimRoom_Tile";
	FixelSize[0] = 64, FixelSize[1] = 64;
	IndexCount[0] = 40, IndexCount[1] = 20;

	Ambience = UEngineSound::SoundPlay("ambience_ice.wav");
	Ambience.Loop();
	Ambience.Off();


	Super::BeginPlay();
	UEngineEditorGUI::CreateEditorWindow<UBoss_TestSkill_GUI>("Boss_TestSkill");
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
		FVector Playerpos = Player->GetActorTransform().LocalPosition;
		FVector Bosspos = Boss->GetActorTransform().LocalPosition;


		if (BossIntro == false)
		{
			Time += _DeltaTime;
			if (Time<2.f)
			{
				if (Playerpos.X > 650 && Playerpos.X < 1900 && Playerpos.Y < 826 && Playerpos.Y > 382)
				{
					Camera->SetActorLocation({ Player->GetActorLocation().X+200, Player->GetActorLocation().Y+200 });
				}
			}
			else
			{
				Camera->SetActorLocation({ Boss->GetActorLocation().X, Boss->GetActorLocation().Y });
				BossIntro = Boss->EndIntro();
				if (BossIntro == true)
				{
					Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y+200 });
		
					return;
				}
			}
		}
		else
		{
			if (Playerpos.X > 650 && Playerpos.X < 1900 && Playerpos.Y < 826 && Playerpos.Y > 382)
			{
				Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
			}
			else if ((Playerpos.X <= 650 || Playerpos.X >= 1900) && Playerpos.Y < 826 && Playerpos.Y > 382)
			{
				Camera->SetActorLocation({ Camera->GetActorLocation().X, Player->GetActorLocation().Y });
			}
			else if (Playerpos.X > 650 && Playerpos.X < 1900 && (Playerpos.Y >= 826 || Playerpos.Y <= 382))
			{
				Camera->SetActorLocation({ Player->GetActorLocation().X, Camera->GetActorLocation().Y });
			}
		}		
	}
}
