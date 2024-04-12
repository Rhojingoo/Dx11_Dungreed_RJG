#include "PreCompile.h"
#include "Player_Hand.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

APlayer_Hand::APlayer_Hand()
{
	//SetRoot(Renderer);
	//Renderer->SetPivot(EPivot::BOT);

	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	//Renderer->SetScale(FVector(300.0f, 300.0f, 300.0f));

	Hand_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer1");
	Hand_Renderer->SetupAttachment(Root);
	Hand_Renderer->SetPivot(EPivot::BOT);
	Hand_Renderer->CreateAnimation("Player_Hand", "Player_Hand", 0.1f);
	Hand_Renderer->ChangeAnimation("Player_Hand");
	Hand_Renderer->SetScale(FVector(9.0f, 9.0f, 100.0f));
	Hand_Renderer->AddPosition({ 20.0f, 0.0f, 0.0f });



	Sword_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer2");
	Sword_Renderer->SetupAttachment(Hand_Renderer);
	Sword_Renderer->SetPivot(EPivot::BOT);
	Sword_Renderer->SetSprite("DemonSword.png");
	Sword_Renderer->SetScale(FVector(6.0f, 20.0f, 100.0f));
	Sword_Renderer->AddPosition({ 1.0f, 10.0f, -1.0f });

	SetRoot(Root);

}


APlayer_Hand::~APlayer_Hand()
{
}



void APlayer_Hand::BeginPlay()
{
	Super::BeginPlay();

	//SetActorScale3D(FVector(320.0f, 320.0f, 100.0f));
	//Renderer->SetSprite("CuttingTest.png", 11);

	Renderer->CreateAnimation("Player_Hand", "Player_Hand", 0.1f);
	Renderer->ChangeAnimation("Player_Hand");

	//Renderer->SetAutoSize(3.f, true);
	Renderer->SetOrder(8);
	InputOn();
}

void APlayer_Hand::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);	

	PlayerPos = GetActorLocation();
	CursorPos = Cursor->GetPos();

	Hand_Dir();

	Dir = CursorPos - PlayerPos;
	Dir.Z = 0; // Z 축 값은 회전 계산에 사용되지 않으므로 0으로 설정
	Dir.Normalize2DReturn();
	 
	switch (Hand_RL)
	{
	case Hand_LeftRight::Right:
		Right();
	 break;
	case Hand_LeftRight::Left:
		Left();
	case Hand_LeftRight::End:
	 break;
	default:
	 break;
	}
	SetActorRotation(SwordRotation);
}



void APlayer_Hand::Right()
{
	if (UpSetting == true) 
	{
		float CursorAngleRad = std::atan2(Dir.Y, Dir.X);
		const float Degrees = 10.0f;
		const float AdditionalAngleRad = Degrees * UEngineMath::DToR;
		float FinalAngleRad = CursorAngleRad + AdditionalAngleRad;
		SwordRotation = FVector(0.0f, 0.0f, FinalAngleRad * UEngineMath::RToD);
	}
	else
	{
		float CursorAngleRad = std::atan2(-Dir.Y, -Dir.X);
		const float Degrees = -10.0f;
		const float AdditionalAngleRad = Degrees * UEngineMath::DToR;
		float FinalAngleRad = CursorAngleRad + AdditionalAngleRad;
		SwordRotation = FVector(0.0f, 0.0f, FinalAngleRad * UEngineMath::RToD);
	}

	if (true == IsDown(VK_LBUTTON))
	{
		UpSetting = !UpSetting;
		if (UpSetting == true)
		{
			Renderer->SetDir(EEngineDir::Right);
			Hand_Renderer->SetDir(EEngineDir::Right);
			FVector SetLocal = Hand_Renderer->GetLocalPosition();
			FVector SetWorld = Renderer->GetLocalPosition();
			Hand_Renderer->Transform.LocalPosition = { SetWorld.X + 20.0f, 0.f,0.f };
		}
		else
		{
			Renderer->SetDir(EEngineDir::Left);
			Hand_Renderer->SetDir(EEngineDir::Left);
			FVector SetLocal = Hand_Renderer->GetLocalPosition();
			FVector SetWorld = Renderer->GetLocalPosition();
			Hand_Renderer->Transform.LocalPosition = { SetWorld.X-20.f, SetWorld.Y - 15.f,0.f };
		}
		return;
	}
}


void APlayer_Hand::Left()
{

	if (UpSetting == true)
	{
		float CursorAngleRad = std::atan2(-Dir.Y, -Dir.X);
		const float Degrees = -10.0f;
		const float AdditionalAngleRad = Degrees * UEngineMath::DToR;
		float FinalAngleRad = CursorAngleRad + AdditionalAngleRad;
		SwordRotation = FVector(0.0f, 0.0f, FinalAngleRad * UEngineMath::RToD);
	}
	else
	{
		float CursorAngleRad = std::atan2(Dir.Y, Dir.X);
		const float Degrees = 10.0f;
		const float AdditionalAngleRad = Degrees * UEngineMath::DToR;
		float FinalAngleRad = CursorAngleRad + AdditionalAngleRad;
		SwordRotation = FVector(0.0f, 0.0f, FinalAngleRad * UEngineMath::RToD);
	}

	if (true == IsDown(VK_LBUTTON))
	{
		UpSetting = !UpSetting;
		if (UpSetting == true)
		{
			Renderer->SetDir(EEngineDir::Left);
			Hand_Renderer->SetDir(EEngineDir::Left);
			FVector SetLocal = Hand_Renderer->GetLocalPosition();
			FVector SetWorld = Renderer->GetLocalPosition();
			Hand_Renderer->Transform.LocalPosition = { SetWorld.X - 20.0f, 0.f,0.f };
		}
		else
		{
			Renderer->SetDir(EEngineDir::Right);
			Hand_Renderer->SetDir(EEngineDir::Right);
			FVector SetLocal = Hand_Renderer->GetLocalPosition();
			FVector SetWorld = Renderer->GetLocalPosition();
			Hand_Renderer->Transform.LocalPosition = { SetWorld.X + 20.f, SetWorld.Y - 15.f,0.f };
		}
		return;
	}
}




void APlayer_Hand::Hand_Dir()
{
	float Dir1 = CursorPos.X - PlayerPos.X;

	if (Dir1 >= 0.f)
	{
		LeftSetting = false;
		if (RightSetting != true && UpSetting == true)
		{
			Hand_Renderer->Transform.LocalPosition = -Hand_Renderer->GetLocalPosition();
			Renderer->SetDir(EEngineDir::Right);
			Hand_Renderer->SetDir(EEngineDir::Right);
			Hand_RL = Hand_LeftRight::Right;
			RightSetting = true;
			return;
		}
		else if (RightSetting != true && UpSetting != true)
		{
			Hand_Renderer->Transform.LocalPosition = -Hand_Renderer->GetLocalPosition();
			Renderer->SetDir(EEngineDir::Left);
			Hand_Renderer->SetDir(EEngineDir::Left);
			Hand_RL = Hand_LeftRight::Right;
			RightSetting = true;
			return;
		}
	}
	else
	{
		RightSetting = false;
		if (LeftSetting != true && UpSetting == true)
		{
			Hand_Renderer->Transform.LocalPosition = -Hand_Renderer->GetLocalPosition();
			Renderer->SetDir(EEngineDir::Left);
			Hand_Renderer->SetDir(EEngineDir::Left);
			Hand_RL = Hand_LeftRight::Left;
			LeftSetting = true;
			return;
		}
		else if (LeftSetting != true && UpSetting != true)
		{
			Hand_Renderer->Transform.LocalPosition = -Hand_Renderer->GetLocalPosition();
			Renderer->SetDir(EEngineDir::Right);
			Hand_Renderer->SetDir(EEngineDir::Right);
			Hand_RL = Hand_LeftRight::Left;
			LeftSetting = true;
			return;
		}
	}
}
