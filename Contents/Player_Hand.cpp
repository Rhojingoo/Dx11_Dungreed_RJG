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
	Sword_Renderer->CreateAnimation("Demon_Sword", "Demon_Sword.png", 0.1f);
	Sword_Renderer->CreateAnimation("Fire_Sword", "Fire_Sword.png", 0.1f); // 별개의 검 (손이랑 좌표 안맞음)
	Sword_Renderer->ChangeAnimation("Demon_Sword");
	Sword_Renderer->SetScale(FVector(6.0f, 20.0f, 100.0f));
	Sword_Renderer->AddPosition({ 1.0f, 10.0f, -1.0f });
	//Sword_Renderer->SetPivot(EPivot::BOT);//Sword.png
	//Sword_Renderer->SetSprite("DemonSword.png");
	//Sword_Renderer->SetScale(FVector(6.0f, 20.0f, 100.0f));
	//Sword_Renderer->AddPosition({ 1.0f, 10.0f, -1.0f });
	Sword_Renderer->SetupAttachment(Hand_Renderer);


	


	//공격이펙트
	{
		//AttatEffect_Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer3");
		//AttatEffect_Renderer->SetupAttachment(Root);
		//AttatEffect_Renderer->CreateAnimation("Sword_Swing_Normal", "Sword_Swing_Normal", 0.1f /*,false*/);
		//AttatEffect_Renderer->CreateAnimation("Sword_Swing_Legend", "Sword_Swing_Legend", 0.1f ,false);
		//AttatEffect_Renderer->SetScale(FVector(180.0f, 141.0f, 100.0f));
		//AttatEffect_Renderer->AddPosition({ 100.0f, 0.0f, 0.0f });
		////Renderer->SetAutoSize(3.f, true);
		////Renderer->SetOrder(9);
		//AttatEffect_Renderer->ChangeAnimation("Sword_Swing_Legend");
	}
	SetRoot(Root);
}


APlayer_Hand::~APlayer_Hand()
{
}



void APlayer_Hand::BeginPlay()
{
	Super::BeginPlay();

	Swing_EF = GetWorld()->SpawnActor<APlayer_Attack_Effect>("R_Hand");

	Renderer->CreateAnimation("Player_Hand", "Player_Hand", 0.1f);
	Renderer->ChangeAnimation("Player_Hand");
	Renderer->SetOrder(8);
	InputOn();
}

void APlayer_Hand::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);	

	PlayerPos = GetActorLocation();
	CursorPos = Cursor->GetPos();

	Hand_Dir();


	 
	Attack_Effect_Dir();
	
	
	

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
		//Attack_Degree = CursorAngleRad * UEngineMath::RToD;
		const float Degrees = 10.0f;
		const float AdditionalAngleRad = Degrees * UEngineMath::DToR;
		float FinalAngleRad = CursorAngleRad + AdditionalAngleRad;
		SwordRotation = FVector(0.0f, 0.0f, FinalAngleRad * UEngineMath::RToD);
	}
	else
	{
		float CursorAngleRad = std::atan2(-Dir.Y, -Dir.X);
		//Attack_Degree = CursorAngleRad * UEngineMath::RToD;
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
			//AttatEffect_Renderer->ChangeAnimation("Sword_Swing_Legend");
			Renderer->SetDir(EEngineDir::Right);
			Hand_Renderer->SetDir(EEngineDir::Right);
			FVector HandRender_Local = Hand_Renderer->GetLocalPosition();
			FVector MainRender_World = Renderer->GetLocalPosition();
			Hand_Renderer->Transform.LocalPosition = { MainRender_World.X + 20.0f, 0.f,0.f };


			Attack_EffectDir = Attack_EffectDir * UEngineMath::DToR;
			Swing_EF->SetActorLocation({ GetActorLocation().X - (15.0f* Attack_EffectDir.X), GetActorLocation().Y - (15.0f * Attack_EffectDir.Y),190.f});
			Swing_EF->SetActorRotation({0.f,0.f,Attack_Degree + 90.f });
			Swing_EF->AttackOn();
		}
		else
		{
			//AttatEffect_Renderer->ChangeAnimation("Sword_Swing_Legend");
			Renderer->SetDir(EEngineDir::Left);
			Hand_Renderer->SetDir(EEngineDir::Left);
			FVector HandRender_Local = Hand_Renderer->GetLocalPosition();
			FVector MainRender_World = Renderer->GetLocalPosition();
			Hand_Renderer->Transform.LocalPosition = { MainRender_World.X-20.f, MainRender_World.Y - 15.f,0.f };

			Attack_EffectDir = Attack_EffectDir * UEngineMath::DToR;
			Swing_EF->SetActorLocation( { GetActorLocation().X - 15.0f * Attack_EffectDir.X,  GetActorLocation().Y - (15.0f * Attack_EffectDir.Y),190.f });
			Swing_EF->SetActorRotation({ 0.f,0.f,Attack_Degree + 90.f });
			Swing_EF->AttackOn();
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
			FVector HandRender_Local = Hand_Renderer->GetLocalPosition();
			FVector MainRender_World = Renderer->GetLocalPosition();
			Hand_Renderer->Transform.LocalPosition = { MainRender_World.X - 20.0f, 0.f,0.f };


			Attack_EffectDir = Attack_EffectDir * UEngineMath::DToR;
			Swing_EF->SetActorLocation({ GetActorLocation().X - (15.0f * Attack_EffectDir.X), GetActorLocation().Y - (15.0f * Attack_EffectDir.Y),190.f });
			Swing_EF->SetActorRotation({ 0.f,0.f,Attack_Degree + 90.f });
			Swing_EF->AttackOn();
		}
		else
		{
			Renderer->SetDir(EEngineDir::Right);
			Hand_Renderer->SetDir(EEngineDir::Right);
			FVector HandRender_Local = Hand_Renderer->GetLocalPosition();
			FVector MainRender_World = Renderer->GetLocalPosition();
			Hand_Renderer->Transform.LocalPosition = { MainRender_World.X + 20.f, MainRender_World.Y - 15.f,0.f };


			Attack_EffectDir = Attack_EffectDir * UEngineMath::DToR;
			Swing_EF->SetActorLocation({ GetActorLocation().X - (15.0f * Attack_EffectDir.X), GetActorLocation().Y - (15.0f * Attack_EffectDir.Y),190.f });
			Swing_EF->SetActorRotation({ 0.f,0.f,Attack_Degree + 90.f });
			Swing_EF->AttackOn();
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

void APlayer_Hand::Attack_Effect_Dir()
{
	//팔, 소드 회전시 사용되는 Dir
	{
		Dir = CursorPos - PlayerPos;
		Dir.Z = 0; // Z 축 값은 회전 계산에 사용되지 않으므로 0으로 설정
		Dir.Normalize2DReturn();
	}
	// 소드 이펙트 Dir설정
	{
		Attack_EffectDir = PlayerPos - CursorPos;
		float Dir1 = CursorPos.X - PlayerPos.X;
		if (Dir1 >= 0.f)
		{
			if (Attack_EffectDir.X < -290.f)
			{
				Attack_EffectDir.X = -290.f;
			}
			if (Attack_EffectDir.Y < -290.f)
			{
				Attack_EffectDir.Y = -290.f;
			}
		}
		else
		{
			if (Attack_EffectDir.X > 290.f)
			{
				Attack_EffectDir.X = 290.f;
			}
			if (Attack_EffectDir.Y > 290.f)
			{
				Attack_EffectDir.Y = 290.f;
			}
		}
		Attack_EffectDir.Z = 0; // Z 축 값은 회전 계산에 사용되지 않으므로 0으로 설정
		Attack_EffectDir.Normalize2DReturn();
		Attack_Degree = (std::atan2(Attack_EffectDir.Y, Attack_EffectDir.X)) * UEngineMath::RToD;
	}
}
