#include "PreCompile.h"
#include "Player_Hand.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/Image.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

SwordHand_Type APlayer_Hand::SwordType = SwordHand_Type::Demon_Sword;

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
	Sword_Renderer->CreateAnimation("Demon_Blade", "Demon_Blade.png", 0.1f); // 별개의 검 (손이랑 좌표 안맞음)
	Sword_Renderer->ChangeAnimation("Demon_Sword"); 
	Sword_Renderer->SetScale(FVector(6.0f, 20.0f, 100.0f));
	Sword_Renderer->AddPosition({ 1.0f, 10.0f, -1.0f });
	//Sword_Renderer->SetPivot(EPivot::BOT);//Sword.png
	//Sword_Renderer->SetSprite("DemonSword.png");
	//Sword_Renderer->SetScale(FVector(6.0f, 20.0f, 100.0f));
	//Sword_Renderer->AddPosition({ 1.0f, 10.0f, -1.0f });
	Sword_Renderer->SetupAttachment(Hand_Renderer);	

	SetRoot(Root);
}


APlayer_Hand::~APlayer_Hand()
{
}



void APlayer_Hand::BeginPlay()
{
	Super::BeginPlay();


	Weapon_Front_UI = CreateWidget<UImage>(GetWorld(), "Weapon_Front_UI");
	Weapon_Front_UI->AddToViewPort(1);
	Weapon_Front_UI->SetSprite("Wapone_UI_First.png");
	//Weapon_Front_UI->SetSprite("Wapone_UI_Second.png");
	Weapon_Front_UI->SetAutoSize(4.f, true);
	Weapon_Front_UI->SetPosition({ 540, -280 });
	Weapon_Front_UI->SetOrder(1);

	Weapon_Back_UI = CreateWidget<UImage>(GetWorld(), "Weapon_Back_UI");
	Weapon_Back_UI->AddToViewPort(0);
	Weapon_Back_UI->SetSprite("Wapone_UI_Second.png");
	Weapon_Back_UI->SetAutoSize(4.f, true);
	Weapon_Back_UI->SetPosition({ 550, -270 });
	Weapon_Back_UI->SetOrder(0);


	WeaponType = CreateWidget<UImage>(GetWorld(), "WeaponType");
	WeaponType->AddToViewPort(1);
	WeaponType->SetSprite("DemonSword_UI.png");
	//WeaponType->SetSprite("DemonBlade_UI.png");
	WeaponType->SetAutoSize(2.5f, true);
	WeaponType->SetPosition({ 540, -280 });
	WeaponType->SetOrder(1);
	



	Renderer->CreateAnimation("Player_Hand", "Player_Hand", 0.1f);
	Renderer->ChangeAnimation("Player_Hand");
	Renderer->SetOrder(ERenderOrder::Wapon);
	Sword_Renderer->SetOrder(ERenderOrder::Wapon);
	Hand_Renderer->SetOrder(ERenderOrder::Wapon);
	InputOn();

	if (SwordType == SwordHand_Type::Demon_Sword)
	{
		Sword_Renderer->ChangeAnimation("Demon_Sword");
		Weapon_Front_UI->SetSprite("Wapone_UI_First.png");
		WeaponType->SetSprite("DemonSword_UI.png");
	}
	else if (SwordType == SwordHand_Type::Demon_Blade)
	{
		Sword_Renderer->ChangeAnimation("Demon_Blade");
		Weapon_Front_UI->SetSprite("Wapone_UI_Second.png");
		WeaponType->SetSprite("DemonBlade_UI.png");
	}
}

void APlayer_Hand::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);	

	PlayerPos = GetActorLocation();
	CursorPos = Cursor->GetPos();

	Hand_Dir();
	HandStateUpdate();
	 
	SwordType_Choice();
	Attack_Effect_Dir();		
	
	SetActorRotation(SwordRotation);
}

void APlayer_Hand::HandStateUpdate()
{
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
			Swing_EF = GetWorld()->SpawnActor<APlayer_Attack_Effect>("R_Hand");	
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
			Swing_EF = GetWorld()->SpawnActor<APlayer_Attack_Effect>("R_Hand");
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
			Swing_EF = GetWorld()->SpawnActor<APlayer_Attack_Effect>("R_Hand");
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
			Swing_EF = GetWorld()->SpawnActor<APlayer_Attack_Effect>("R_Hand");
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


void APlayer_Hand::SwordType_Choice()
{
	if (UEngineInput::IsPress('1'))
	{
		ChangeSwordType(SwordHand_Type::Demon_Sword);
		Swing_EF->SwordEffectType_Choice(Sword_Type::Demon_Sword);
		Weapon_Front_UI->SetSprite("Wapone_UI_First.png");
		WeaponType->SetSprite("DemonSword_UI.png");
	}
	if (UEngineInput::IsPress('2'))
	{
		ChangeSwordType(SwordHand_Type::Demon_Blade);
		Swing_EF->SwordEffectType_Choice(Sword_Type::Demon_Blade);
		Weapon_Front_UI->SetSprite("Wapone_UI_Second.png");
		WeaponType->SetSprite("DemonBlade_UI.png");
	}

}
void APlayer_Hand::ChangeSwordType(SwordHand_Type _Set)
{
	if (SwordType != _Set)
	{
		switch (_Set)
		{
		case SwordHand_Type::Demon_Sword:
			LasliSword_Choice();
			break;
		case SwordHand_Type::Demon_Blade:
			DemonBlade_Choice();
			break;

		default:
			break;
		}
	}
	SwordType = _Set;
}
void APlayer_Hand::DemonBlade_Choice()
{
	Sword_Renderer->ChangeAnimation("Demon_Blade"); 
}
void APlayer_Hand::LasliSword_Choice()
{
	Sword_Renderer->ChangeAnimation("Demon_Sword"); 
}