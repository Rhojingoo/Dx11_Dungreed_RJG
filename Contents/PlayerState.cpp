#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsHelper.h"
#include <EngineCore/EngineDebugMsgWindow.h>
#include "Player_Hand.h"
#include "Target.h"
#include "Player_Smoke_Effect.h"
#include "Player_AfterImage.h"

//void Function(URenderer* Renderer)
//{
//	Renderer->ChangeAnimation("Idle");
//}

void APlayer::StateInit()
{
	// 스테이트 만들고
	State.CreateState("Player_Die");
	State.CreateState("Player_Idle");
	State.CreateState("Player_Jump");
	State.CreateState("Player_Run");
	State.CreateState("Player_Dash");
	State.CreateState("Player_SecondDash");
	State.CreateState("Player_Debug");


	InputOn();

	State.SetUpdateFunction("Player_Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));

	
	USpriteRenderer* MyRender = Renderer;

	State.SetStartFunction("Player_Idle", [=] 		
		{
			MyRender->ChangeAnimation("Player_Idle");
		}
	);

	State.SetUpdateFunction("Player_Run", std::bind(&APlayer::Run, this, std::placeholders::_1));

	State.SetStartFunction("Player_Run", std::bind(&APlayer::RunStart, this));


	State.SetUpdateFunction("Player_Jump", std::bind(&APlayer::Jump, this, std::placeholders::_1));

	State.SetStartFunction("Player_Jump", std::bind(&APlayer::JumpStart, this));

	State.SetUpdateFunction("Player_Dash", std::bind(&APlayer::Dash, this, std::placeholders::_1));

	State.SetStartFunction("Player_Dash", std::bind(&APlayer::DashStart, this));

	State.SetUpdateFunction("Player_SecondDash", std::bind(&APlayer::SecondDash, this, std::placeholders::_1));

	State.SetStartFunction("Player_SecondDash", std::bind(&APlayer::SecondDashStart, this));


	State.SetUpdateFunction("Player_Debug", [=](float _Delta)
		{

			float Speed = 500.0f;
			if (UEngineInput::IsPress('A'))
			{
				AddActorLocation(FVector::Left * _Delta * Speed);
			}

			if (UEngineInput::IsPress('D'))
			{
				AddActorLocation(FVector::Right * _Delta * Speed);
			}

			if (UEngineInput::IsPress('W'))
			{
				AddActorLocation(FVector::Up * _Delta * Speed);
			}

			if (UEngineInput::IsPress('S'))
			{
				AddActorLocation(FVector::Down * _Delta * Speed);
			}

			std::shared_ptr<UEngineTexture> Tex = UContentsHelper::MapTex;

			float4 PlayerLocation = GetActorLocation();

			PlayerLocation.Y = (Tex->GetScale().Y * 64.0f) - PlayerLocation.Y;
			PlayerLocation /= UContentsHelper::TileSize;
			Color8Bit Color = Tex->GetColor(PlayerLocation, Color8Bit::Black);

			if (Color == Color8Bit::Black)
			{
				GravityVector = FVector::Zero;
				JumpOn = false;
			}

		});


	State.CreateState("");
	
	// 체인지Player_Idle
	//State.ChangeState("Player_Debug");
	State.ChangeState("Player_Idle");
}


void APlayer::Die(float _Update)
{

}

void APlayer::Idle(float _DeltaTime)
{

	if (true == IsPress('A') || true == IsPress('D') )
	{
		State.ChangeState("Player_Run");
		return;
	}

	if (true == IsPress(VK_SPACE))
	{
		State.ChangeState("Player_Jump");
		return;
	}
	if (true == IsDown(VK_RBUTTON))
	{
		State.ChangeState("Player_Dash");
		return;
	}
	
	MoveUpdate(_DeltaTime);

	if (JumpOn == false) 
	{
		DashVector = FVector::Zero;
		SecondDashVector = FVector::Zero;
	}
}

void APlayer::JumpStart()
{
	Renderer->ChangeAnimation("Player_Jump");
	JumpVector = JumpPower;
	PlayerPos.Y = PlayerPos.Y - 40;
	JumpOn = true;
}

void APlayer::Jump(float _DeltaTime)
{
	float Speed = 50.0f;
	if (UEngineInput::IsPress('A'))
	{
		AddMoveVector(FVector::Left * _DeltaTime * Speed);
	}

	if (UEngineInput::IsPress('D'))
	{
		AddMoveVector(FVector::Right * _DeltaTime * Speed);
	}
	if (true == IsPress(VK_SPACE))
	{
		if (JumpVector.Y <= 1200.f)
		{
			JumpVector += (FVector::Up * _DeltaTime * 1500);
		}
	}	

	MoveUpdate(_DeltaTime);
	if (JumpOn == false)
	{
		State.ChangeState("Player_Idle");
		JumpVector = FVector::Zero;
		MoveVector = FVector::Zero;
		LastMoveVector = FVector::Zero;
	}
}

void APlayer::RunStart()
{
	Renderer->ChangeAnimation("Player_Run");
}

void APlayer::Run(float _DeltaTime)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		int a = 0;
	}

	float Speed = 50.0f;


	if (UEngineInput::IsPress('A'))
	{
		AddMoveVector(FVector::Left * _DeltaTime* Speed);
		if (Smoke_Effect->CanPlayEffect() == true)
		{
			Smoke_Effect->SetActorLocation({ GetActorLocation().X + 15, GetActorLocation().Y , GetActorLocation().Z + 1 });
			Smoke_Effect->Run_Smoke_On();
			Smoke_Effect->Left_Dir();
			PlayerMoveDir = true;
		}
	}

	if (UEngineInput::IsPress('D'))
	{
		AddMoveVector(FVector::Right * _DeltaTime* Speed);
		if (Smoke_Effect->CanPlayEffect() == true)
		{
			Smoke_Effect->SetActorLocation({ GetActorLocation().X - 15, GetActorLocation().Y , GetActorLocation().Z + 1 });
			Smoke_Effect->Run_Smoke_On();
			Smoke_Effect->Right_Dir();
			PlayerMoveDir = false;
		}
	}

	if (true == IsUp('A') || true == IsUp('D'))
	{
		State.ChangeState("Player_Idle");
		LastMoveVector = FVector::Zero;
		MoveVector= FVector::Zero;
		return;
	}

	if (true == IsPress(VK_SPACE))
	{
		State.ChangeState("Player_Jump");
		return;
	}

	if (true == IsPress(VK_RBUTTON))
	{
		State.ChangeState("Player_Dash");
		return;
	}
	MoveUpdate(_DeltaTime);
}

void APlayer::DebugStart()
{
}

void APlayer::DebugCeck(float _DeltaTime)
{
}

void APlayer::DashStart()
{
	Renderer->ChangeAnimation("Player_Jump");
	PlayerPos = GetActorLocation();
	CursorPos = Cursor->GetPos();
	DashDir = CursorPos - PlayerPos;
	DashDir.Z = 0.f;
	DashDir.Normalize2D();
	DashDir *= 24.f;
	float Speed = 50.f;
	DashVector = DashDir * Speed;
	JumpOn = true;
	DashTime = 0.f;
	DashCount += 1;
	Dash_Effect_Call();
	AfterImageSwitch = true;

	if (DashDir.X > 0.f)
	{
		AfterImageRight = true;
	}
	else
	{
		AfterImageRight = false;
	}
}

void APlayer::Dash(float _DeltaTime)
{

	MoveUpdate(_DeltaTime);

	if (DashCount < DashMax)
	{
		if (true == IsDown(VK_RBUTTON))
		{
			GravityVector = FVector::Zero;
			DashVector = FVector::Zero;
			State.ChangeState("Player_SecondDash");
			DashTime = 0.f;
			return;
		}
	}


	if (true == IsPress('A') || true == IsPress('D'))
	{		
		int a = 0;
		return;
	}


	DashTime += _DeltaTime;
	if (DashTime >= 0.3f )
	{
		State.ChangeState("Player_Idle");
		GravityVector = FVector::Zero;
		DashTime = 0.f;
		DashCount = 0;
		AfterImageSwitch = false;
		AfterImage_Time = 0.f;
		return;
	}
}

void APlayer::Dash_Effect_Call()
{
	if (CursorPos.X - PlayerPos.X > 0.f)
	{
		Smoke_Effect->SetActorLocation({ GetActorLocation().X - 15, GetActorLocation().Y , GetActorLocation().Z + 1 });
		Smoke_Effect->Run_Smoke_On();
		Smoke_Effect->Right_Dir();
	}
	else
	{
		Smoke_Effect->SetActorLocation({ GetActorLocation().X + 15, GetActorLocation().Y , GetActorLocation().Z + 1 });
		Smoke_Effect->Run_Smoke_On();
		Smoke_Effect->Left_Dir();
	}
}

void APlayer::SecondDashStart()
{
	Renderer->ChangeAnimation("Player_Jump");
	DashVector = FVector::Zero;
	GravityVector = FVector::Zero;
	LastMoveVector = FVector::Zero;
	PlayerPos = GetActorLocation();
	CursorPos = Cursor->GetPos();
	DashDir = CursorPos - PlayerPos;
	DashDir.Z = 0.f;
	DashDir.Normalize2D();
	DashDir *= 24.f;
	float Speed = 50.f;
	SecondDashVector = DashDir * Speed;
	JumpOn = true;
	DashTime = 0.f;
	DashCount += 1;
	Dash_Effect_Call();
	AfterImageSwitch = true;
	AfterImage_Time = 0.f;

	if (DashDir.X > 0.f)
	{
		AfterImageRight = true;
	}
	else
	{
		AfterImageRight = false;
	}
}

void APlayer::SecondDash(float _DeltaTime)
{
	MoveUpdate(_DeltaTime);

	if (true == IsPress('A') || true == IsPress('D'))
	{
		return;
	}

	DashTime += _DeltaTime;
	if (DashTime >= 0.3f)
	{
		SecondDashVector = FVector::Zero;
		GravityVector = FVector::Zero;
		State.ChangeState("Player_Idle");
		DashTime = 0.f;
		DashCount = 0;
		AfterImageSwitch =false;
		AfterImage_Time = 0.f;
		return;
	}
}

void APlayer::DebugFunction()
{
	{
		std::string Msg = std::format("PlayerPos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	{
		std::string Msg = std::format("MousePos : {}\n", GEngine->EngineWindow.GetScreenMousePos().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	{
		std::string Msg = std::format("PlayerCollisionPos : {}\n", Collision->GetWorldPosition().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void APlayer::Direction()
{
	PlayerPos = GetActorLocation();
	CursorPos = Cursor->GetPos();

	float Dir = CursorPos.X - PlayerPos.X;

	if (Dir >= 0.f)
	{
		Renderer->SetDir(EEngineDir::Right);
	}
	else
	{
		Renderer->SetDir(EEngineDir::Left);
	}
}

void APlayer::Dash_Direction(float _DeltaTime)
{
	PlayerPos = GetActorLocation();
	CursorPos = Cursor->GetPos();

	DashDir = CursorPos - PlayerPos;
	DashDir.Z = 0.f;
	DashDir.Normalize2D();
	DashDir *= 24.f;
	float Speed = 150.f;
	AddMoveVector(DashDir * _DeltaTime * Speed);
}

void APlayer::CalLastMoveVector(float _DeltaTime)
{
	LastMoveVector = FVector::Zero;
	LastMoveVector = LastMoveVector + MoveVector;
	LastMoveVector = LastMoveVector + JumpVector;
	LastMoveVector = LastMoveVector + DashVector;
	LastMoveVector = LastMoveVector + SecondDashVector;
	LastMoveVector = LastMoveVector + GravityVector;
}

void APlayer::CalMoveVector(float _DeltaTime)
{
	FVector CheckPos = GetActorLocation();

	if (true == UEngineInput::IsFree('A') && true == UEngineInput::IsFree('D'))
	{
		if (0.001 <= MoveVector.Size2D())
		{
			MoveVector += (-MoveVector.Normalize2DReturn()) * _DeltaTime * MoveAcc;
		}
		else {
			MoveVector = float4::Zero;
		}
	}
	if (MoveMaxSpeed <= MoveVector.Size2D())
	{
		MoveVector = MoveVector.Normalize2DReturn() * MoveMaxSpeed;
	}
}

void APlayer::CalJumpVector(float _DeltaTime)
{
}

void APlayer::CalGravityVector(float _DeltaTime)
{	// 제로로 만들어서 초기화 시킨다.
	GravityVector += GravityAcc * _DeltaTime;		
	std::shared_ptr<UEngineTexture> Tex = UContentsHelper::MapTex;

#ifdef _DEBUG
	if (nullptr == Tex)
	{
		MsgBoxAssert("이미지 충돌체크중 이미지가 존재하지 않습니다.");
	}
#endif

	Direction();

	Color8Bit Color;
	Color8Bit UPColor;
	Color8Bit HillColor;
	Color8Bit WallColor;
	if (Foot_Collision_Check_At_Town == true)
	{
		float4 PlayerLocation = GetActorLocation();
		float4 PlayerUpLocation = GetActorLocation();		
		PlayerUpLocation.Y = -PlayerUpLocation.Y-15;
		UPColor = Tex->GetColor(PlayerUpLocation, Color8Bit::Black);

		if (UPColor == Color8Bit::Black)
		{
			GravityVector += GravityAcc * _DeltaTime;
			Color = Color8Bit::Blue;			
		}
		else
		{
			PlayerLocation.Y = -PlayerLocation.Y;
			Color = Tex->GetColor(PlayerLocation, Color8Bit::Black);
			if (PlayerMoveDir == true)	//왼쪽
			{
				float4 HillCheck= GetActorLocation();
				HillCheck.X = HillCheck.X - 15;
				HillCheck.Y = -HillCheck.Y;
				HillColor = Tex->GetColor(HillCheck, Color8Bit::Red);		
				if (HillColor == Color8Bit::Red)
				{
					GravityVector = FVector::Zero;
					AddActorLocation({0.f, 0.001f});
				}		
			}
			else		//오른쪽
			{
				float4 HillCheck = GetActorLocation();
				HillCheck.X = HillCheck.X + 15;
				HillCheck.Y = -HillCheck.Y;
				HillColor = Tex->GetColor(HillCheck, Color8Bit::Red);
				if (HillColor == Color8Bit::Red)
				{			
					GravityVector = FVector::Zero;
					AddActorLocation({ 0.f, 0.001f });
				}
			}
		}
	}
	else
	{
		std::shared_ptr<UEngineTexture> Tex = UContentsHelper::MapTex;

		float4 PlayerLocation = GetActorLocation();

		PlayerLocation.Y = (Tex->GetScale().Y * 64.0f) - PlayerLocation.Y-25;
		PlayerLocation /= UContentsHelper::TileSize;
		Color = Tex->GetColor(PlayerLocation, Color8Bit::Black);

		if (Color == Color8Bit::Black)
		{
			GravityVector = FVector::Zero;
			JumpOn = false;
		}
	}		
	if (Color == Color8Bit::Black)
	{
		GravityVector = FVector::Zero;	
		JumpOn = false;	
	}
}

void APlayer::MoveLastMoveVector(float _DeltaTime)
{	
	// 카메라는 x축으로만 움직여야 하니까.	
	AddActorLocation(LastMoveVector * _DeltaTime);
}

void APlayer::MoveUpdate(float _DeltaTime)
{
	Direction();
	CalMoveVector(_DeltaTime);
	CalGravityVector(_DeltaTime);	
	CalLastMoveVector(_DeltaTime);
	MoveLastMoveVector(_DeltaTime);
	GroundUp(_DeltaTime);
}

void APlayer::GroundUp(float _DeltaTime)
{
//	std::shared_ptr<UEngineTexture> Tex = UContentsHelper::MapTex;
//
//#ifdef _DEBUG
//	if (nullptr == Tex)
//	{
//		MsgBoxAssert("이미지 충돌체크중 이미지가 존재하지 않습니다.");
//	}
//#endif
//
//	Direction();
//	PlayerPos.Y = PlayerPos.Y - 44;
//	PlayerPos.Y = -PlayerPos.Y;
//
//	Color8Bit Color = Tex->GetColor(PlayerPos, Color8Bit::Black);
//
//	if (Color != Color8Bit::Black)
//	{
//		AddActorLocation(float4::Down * _DeltaTime * 350.0f);
//	}

	//while (true)
	//{
	//	Color8Bit Color = UContentsHelper::ColMapImage->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), Color8Bit::MagentaA);
	//	if (Color == Color8Bit(255, 0, 255, 0))
	//	{
	//		AddActorLocation(FVector::Up);
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}
}

void APlayer::AddMoveVector(const FVector& _DirDelta)
{
	MoveVector += _DirDelta * MoveAcc;
}

void APlayer::PlayAfterImage(float _DeltaTime, FVector _PlayerPos)
{
	if (AfterImageSwitch == true)
	{
		static int Num = 0;
		After_Image[Num]->SetActorLocation(_PlayerPos);
		After_Image[Num]->ImageOn();
		if (AfterImageRight == true)
		{
			After_Image[Num]->RightDir();
		}
		else
		{
			After_Image[Num]->LeftDir();
		}

		static float check = AfterImage_Time;
		AfterImage_Time += _DeltaTime;
		if ((AfterImage_Time - check) >= 0.02f)
		{
			check = AfterImage_Time;
			if (Num < 9)
			{
				Num++;
			}
			else if (Num >= 9)
			{
				Num = 0;
				check = 0.f;
				AfterImage_Time = 0.f;
			}
		}
	}
}

void APlayer::colorsetting()
{
	//if (true == IsPress('W'))
	//{
	//	AddActorLocation(FVector::Up * _DeltaTime * Speed);
	//}

	//if (true == IsPress('S'))
	//{
	//	AddActorLocation(FVector::Down * _DeltaTime * Speed);
	//}

	//if (true == IsPress(VK_NUMPAD1))
	//{
	//	// AddActorRotation(float4{0.0f, 0.0f, 1.0f} * 360.0f * _DeltaTime);
	//	// Color.X += _DeltaTime;
	//}

	//if (true == IsPress(VK_NUMPAD2))
	//{
	//	Color.X -= _DeltaTime;
	//}

	//if (true == IsPress(VK_NUMPAD4))
	//{
	//	Color.Y += _DeltaTime;
	//}

	//if (true == IsPress(VK_NUMPAD5))
	//{
	//	Color.Y -= _DeltaTime;
	//}

	//if (true == IsPress(VK_NUMPAD7))
	//{
	//	Color.Z += _DeltaTime;
	//}

	//if (true == IsPress(VK_NUMPAD8))
	//{
	//	Color.Z -= _DeltaTime;
	//}

}
