#include "PreCompile.h"
#include "Monster01_GameMode.h"
#include "MapEditorGUI.h"
#include "Player.h"
#include "Target.h"
#include "Monster01_BackGround.h"
#include "Monster01_BGPIXEL.h"
#include <EngineCore/Camera.h>
#include "MiniBat.h"
#include "RedGinatBat.h"
#include "Skeleton.h"
#include "Monster.h"
#include "DungeonDoor.h"
#include "BossDoor.h"



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

	Player = GetWorld()->SpawnActor<APlayer>("Player", EOBJ_Order::Player);
	Player->SetActorLocation({ 640.0f, 360.0f, 200.0f });

	Cursor = GetWorld()->SpawnActor<ATarget>("Target");
	Cursor->SetActorLocation({ 640.0f, 360.0f, 200.0f });

	Door = GetWorld()->SpawnActor<ADungeonDoor>("Door");
	Door->SetActorLocation({ 1565.0f, 770.0f, 200.0f });
	
	BossDoor = GetWorld()->SpawnActor<ABossDoor>("BossDoor");
	BossDoor->SetActorLocation({ 640.0f, 320.0f, 200.0f });

	CreateMonster();
	
	//std::shared_ptr<ASkeleton> IceBat1 = GetWorld()->SpawnActor<ASkeleton>("Ice_Bat", EOBJ_Order::Monster);
	//IceBat1->SetActorLocation({ 640.f, 190.0f, 200.0f });
	//IceBat1->SetPlayer(Player);

	//std::shared_ptr<Aminibat> icebat1 = getworld()->spawnactor<Aminibat>("ice_bat", eobj_order::monster);
	//icebat1->setactorlocation({ 640.0f, 360.0f, 200.0f });
	//icebat1->setplayer(player);

	//std::shared_ptr<ARedGinatBat> IceBat = GetWorld()->SpawnActor<ARedGinatBat>("Ice_Bat", EOBJ_Order::Monster);
	//IceBat->SetActorLocation({ 640.0f, -760.0f, 200.0f });
	//IceBat->SetPlayer(Player);
}

void AMonster01_GameMode::LevelEnd(ULevel* _NextLevel)
{
	Player->Destroy();
	Camera->Destroy();
	Cursor->Destroy();
	Door->Destroy();
	BossDoor->Destroy();
	DoorCreate = false;
	DoorOpen = false;

	MonTerCreate_First = false;
	MonTerCreate_Second = false;
	MonTerCreate_Thirth = false;	
	MonTerEnd_First = false;
	MonTerEnd_Second = false;
	MonTerEnd_Thirth = false;	
	MonTerEnter_Second = false;
}

void AMonster01_GameMode::BeginPlay()
{
	Tile_MapName = "Monster_01_Tile";
	FixelSize[0] = 64, FixelSize[1] = 64;
	IndexCount[0] = 25, IndexCount[1] = 24;

	Super::BeginPlay();

	UContentsHelper::MapTex = UEngineTexture::FindRes("Monster_01PX.png");
	UContentsHelper::MapTexScale = UContentsHelper::MapTex->GetScale();


	std::shared_ptr<AMonster01_BackGround> BackGr = GetWorld()->SpawnActor<AMonster01_BackGround>("Monster01_Bg", EOBJ_Order::BackGround);
	float TileSize = UContentsHelper::TileSize;
	float4 TexScale = UContentsHelper::MapTexScale;
	float4 ImageScale = { TexScale.X * TileSize, TexScale.Y * TileSize, 0.0f };
	BackGr->SetActorScale3D(ImageScale);
	BackGr->SetActorLocation({ ImageScale.hX(), ImageScale.hY(), 500.0f });


	std::shared_ptr<AMonster01_BGPIXEL> Back = GetWorld()->SpawnActor<AMonster01_BGPIXEL>("Monster_01PX", EOBJ_Order::PixelGround);
	Back->SetActorScale3D(ImageScale);
	Back->SetActorLocation({ ImageScale.hX(), ImageScale.hY(), 500.0f});


}

void AMonster01_GameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("Mon02_Level");
	}

	if (Camera != nullptr)
	{
		FVector Playerpos = Player->GetActorTransform().LocalPosition;

		if (Playerpos.X > 650 && Playerpos.X < 950 && Playerpos.Y < 1100 && Playerpos.Y > 330)
		{
			Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y });
		}
		else if ((Playerpos.X <= 650 || Playerpos.X >= 950) && Playerpos.Y < 1100 && Playerpos.Y > 330)
		{
			Camera->SetActorLocation({ Camera->GetActorLocation().X, Player->GetActorLocation().Y });
		}
		else if (Playerpos.X > 650 && Playerpos.X < 950 && (Playerpos.Y >= 1100 || Playerpos.Y <= 330))
		{
			Camera->SetActorLocation({ Player->GetActorLocation().X, Camera->GetActorLocation().Y });
		}
	}

	if (DoorCreate == true)
	{
		if (DoorOpen == false)
		{
			DoorOpen = true;
		}
	}

	MonsterGroup1_Enter();
}

void AMonster01_GameMode::CreateMonster()
{
	for (int Num = 0; Num < 3; Num++)
	{
		std::shared_ptr<AMonster> Mon = GetWorld()->SpawnActor<AMiniBat>("Ice_Bat", EOBJ_Order::Monster);
		Mon->SetActorLocation({ 0.f, 0.0f, 200.0f });
		Mon->SetActive(false);
		MonsterGroup_First.push_back(Mon);
	}
}

void AMonster01_GameMode::IS_Die_Monter(std::vector<std::shared_ptr<AMonster>> _MonsterGroup, bool& _CheckGroup)
{
	for (std::shared_ptr<AMonster> Mon : _MonsterGroup)
	{
		if (Mon->IsDieMonster() == false)
		{
			return;
		}		
	}	
	_CheckGroup = true;
}

void AMonster01_GameMode::MonsterGroup1_Enter()
{
	if (MonTerCreate_First == false)
	{
		int Num = 0;
		for (std::shared_ptr<AMonster> Mon : MonsterGroup_First)
		{			
			Num++;
			Mon->SetActorLocation({ 640.0f + 200.f * Num - 200.f, 360.0f, 200.0f });
			Mon->SetPlayer(Player);
			Mon->SetActive(true);			
		}
		MonTerCreate_First = true;
	}
	else
	{
		IS_Die_Monter(MonsterGroup_First, MonTerEnd_First);
		if (MonTerEnd_First == true)
		{
			MonsterGroup_First.clear();
			MonsterGroup2_Enter();
		}
	}
}

void AMonster01_GameMode::MonsterGroup2_Enter()
{
	if (MonTerCreate_Second == false)
	{
		for (int Num = 0; Num < 2; Num++)
		{
			std::shared_ptr<AMonster> Mon = GetWorld()->SpawnActor<ARedGinatBat>("Giant_Bat", EOBJ_Order::Monster);
			Mon->SetActorLocation({ 700.0f + (300.f * Num) - 300.f, 560.0f, 200.0f });
			Mon->SetActive(true);
			MonsterGroup_Second.push_back(Mon);
		}		
		MonTerCreate_Second = true;
	}
	else
	{
		IS_Die_Monter(MonsterGroup_Second, MonTerEnd_Second);
		if (MonTerEnd_Second == true)
		{		
			if (MonTerEnd_First == true)
			{
				MonsterGroup_Second.clear();
				MonsterGroup_First.clear();
				MonsterGroup3_Enter();
			}
		}
	}
}

void AMonster01_GameMode::MonsterGroup3_Enter()
{
	if (MonTerCreate_Thirth == false)
	{
		for (int Num = 0; Num < 2; Num++)
		{
			std::shared_ptr<AMonster> Mon = GetWorld()->SpawnActor<ASkeleton>("Skelleton", EOBJ_Order::Monster);
			Mon->SetActorLocation({ 700.0f + (300.f * Num) - 300.f, 190.0f, 200.0f });
			Mon->SetActive(true);
			MonsterGroup_Thirth.push_back(Mon);
		}
		MonTerCreate_Thirth = true;
	}
	else
	{
		IS_Die_Monter(MonsterGroup_Thirth, MonTerEnd_Thirth);
		if (MonTerEnd_Thirth == true)
		{
			MonsterGroup_Thirth.clear();
			DoorCreate = true;
			BossDoor->BossOpne();
		}
	}
}
