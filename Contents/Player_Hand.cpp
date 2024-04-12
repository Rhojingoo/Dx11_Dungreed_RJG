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

}

void APlayer_Hand::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);	

	PlayerPos = GetActorLocation();
	CursorPos = Cursor->GetPos();



	float Dir1 = CursorPos.X - PlayerPos.X;

	if (Dir1 >= 0.f)
	{
		LeftSetting = false;
		Left = false;
		Right = true;
		if (RightSetting != true)
		{
			Hand_Renderer->Transform.LocalPosition = -Hand_Renderer->GetLocalPosition();
		}
		RightSetting = true;
	}
	else
	{
		RightSetting = false;
		Left = true;
		Right = false;
		if (LeftSetting != true)
		{
			Hand_Renderer->Transform.LocalPosition = -Hand_Renderer->GetLocalPosition();
		}
		LeftSetting = true;
	}

	FVector Dir = CursorPos - PlayerPos;
	Dir.Z = 0; // Z 축 값은 회전 계산에 사용되지 않으므로 0으로 설정
	Dir.Normalize2DReturn();
	FVector SwordRotation;
	if (Left ==true)
	{
		Right = false;
		//Hand_Renderer->SetPosition({ -Hand_Renderer->GetWorldPosition()});
		Renderer->SetDir(EEngineDir::Left);
		Hand_Renderer-> SetDir(EEngineDir::Left);
		//Sword_Renderer->SetDir(EEngineDir::Left);
		float CursorAngleRad = std::atan2(-Dir.Y, -Dir.X);
		const float Degrees = -10.0f;
		const float AdditionalAngleRad = Degrees * UEngineMath::DToR;
		float FinalAngleRad = CursorAngleRad + AdditionalAngleRad;
		SwordRotation = FVector(0.0f, 0.0f, FinalAngleRad * UEngineMath::RToD);
	}
	if (Right ==true )
	{
		Left = false;
		//Hand_Renderer->SetPosition({ -Hand_Renderer->GetWorldPosition() });
		// Hand_Renderer-> 로컬로 변경 해봐라
		Renderer->SetDir(EEngineDir::Right);
		Hand_Renderer-> SetDir(EEngineDir::Right);
	//	Sword_Renderer->SetDir(EEngineDir::Right);
		float CursorAngleRad = std::atan2(Dir.Y, Dir.X);
		const float Degrees = 10.0f;
		const float AdditionalAngleRad = Degrees * UEngineMath::DToR;
		float FinalAngleRad = CursorAngleRad + AdditionalAngleRad;
		SwordRotation = FVector(0.0f, 0.0f, FinalAngleRad * UEngineMath::RToD);
	}

	// 커서 방향으로의 2D 벡터 계산

;
	// atan2를 사용하여 커서 방향에 대한 각도 계산 (라디안)

	SetActorRotation(SwordRotation);
}

void APlayer_Hand::InverseArmAxis(Axis axis)
{
	FVector ownerRot = GetActorTransform().GetRotation();
	
	switch (axis)
	{
	case Axis::X:
	{
		ownerRot.X = ownerRot.X + UEngineMath::PI;
		if (ownerRot.X >= 2 * UEngineMath::PI && ownerRot.X < 0.f)
		{
			ownerRot.X = 0.f;
		}

		Revurse_X = !Revurse_X;
		float pos = GetActorLocation().Z;
		if (Revurse_X) pos *= -1.f;
		else pos *= -1.f;
		SetActorLocation({ GetActorLocation().X,GetActorLocation().Y, pos });
		//GetActorTransform().SetRotationDeg()
		if (Revurse_X)
		{
			Offset_Angle = 45.f;
		}
		else
		{
			Offset_Angle = 20.f;
		}
		break;
	}
	case Axis::Y:
		ownerRot.Y = ownerRot.Y + UEngineMath::PI;
		break;
	case Axis::Z:
		ownerRot.Z = ownerRot.Z + UEngineMath::PI;
		break;
	case Axis::End:
	default:
		return;
	}
	GetActorTransform().SetRotationDeg(ownerRot);
}

