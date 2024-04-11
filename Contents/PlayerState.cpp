#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "ContentsHelper.h"
#include <EngineCore/EngineDebugMsgWindow.h>

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


	// 체인지
	State.ChangeState("Player_Idle");
}


void APlayer::Die(float _Update)
{

}

void APlayer::Idle(float _DeltaTime)
{
	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		State.ChangeState("Player_Run");
		return;
	}

	if (true == IsPress(VK_SPACE))
	{
		State.ChangeState("Player_Jump");
		return;
	}

	MoveUpdate(_DeltaTime);
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
	}

	if (UEngineInput::IsPress('D'))
	{
		AddMoveVector(FVector::Right * _DeltaTime* Speed);
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

	MoveUpdate(_DeltaTime);
	
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

void APlayer::CalLastMoveVector(float _DeltaTime)
{
	LastMoveVector = FVector::Zero;
	LastMoveVector = LastMoveVector + MoveVector;
	LastMoveVector = LastMoveVector + JumpVector;
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
	
	PlayerPos.Y = PlayerPos.Y - 44;	
	PlayerPos.Y = -PlayerPos.Y;

	Color8Bit Color = Tex->GetColor(PlayerPos, Color8Bit::Black);

	if (Color == Color8Bit::Black)
	{
		GravityVector = FVector::Zero;	
		JumpOn = false;
	
	}
}

void APlayer::MoveLastMoveVector(float _DeltaTime)
{	// 카메라는 x축으로만 움직여야 하니까.
	
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
