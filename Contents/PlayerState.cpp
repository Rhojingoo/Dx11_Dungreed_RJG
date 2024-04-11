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
	// ������Ʈ �����
	State.CreateState("Player_Die");
	State.CreateState("Player_Idle");
	State.CreateState("Player_Jump");
	State.CreateState("Player_Run");

	InputOn();
	// �Լ��� �����ϰ�
	State.SetUpdateFunction("Player_Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));

	// �ݹ�[0]  �ݹ�[1]   �ݹ�[2][3][4][5][6] [7] �ݹ�8

	Renderer->SetFrameCallback("Player_Run", 0, [=]
		{
			int a = 0;
		});


	// �Ｎ �Լ�
	// = [ ����ĸ�� Renderer]
	// {
	//    �Լ� ����
	// }
	
	// ����ĸó�� ����ȿ� =�� ����
	// ���� ���ÿ��� ��밡���� ���纻�� �����.
	// �޸𸮸� �Ҵ��ؼ� Renderer�� ���� �̸����� �����Ѵ�.

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



	// ü����
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


	Direction();
	std::shared_ptr<UEngineTexture> Tex = UContentsHelper::MapTex;
	//Pos /= UContentsHelper::TileSize;
	PlayerPos.Y = PlayerPos.Y - 44;
	PlayerPos.Y = -PlayerPos.Y;

	Color8Bit Color = Tex->GetColor(PlayerPos, Color8Bit::Black);

	if (Color != Color8Bit::Black)
	{
		AddActorLocation(float4::Down * _DeltaTime * 350.0f);
	}
}

void APlayer::JumpStart()
{
	Renderer->ChangeAnimation("Player_Jump");
	JumpOn = true;
	JumpSpeed = 350.f;
}

void APlayer::Jump(float _DeltaTime)
{
	Direction();
	if (JumpOn == true)
	{
		JumpSpeed -= 550.0f * _DeltaTime;
		AddActorLocation(float4::Up * JumpSpeed);
		if(JumpSpeed<=0.f)
		JumpOn = false;
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

	if (true == IsUp('A') || true == IsUp('D'))
	{
		State.ChangeState("Player_Idle");
		return;
	}


	float Speed = 500.0f;

	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (true == IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (true == IsPress('S'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (true == IsPress(VK_NUMPAD1))
	{
		// AddActorRotation(float4{0.0f, 0.0f, 1.0f} * 360.0f * _DeltaTime);
		// Color.X += _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD2))
	{
		Color.X -= _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD4))
	{
		Color.Y += _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD5))
	{
		Color.Y -= _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD7))
	{
		Color.Z += _DeltaTime;
	}

	if (true == IsPress(VK_NUMPAD8))
	{
		Color.Z -= _DeltaTime;
	}

	std::shared_ptr<UEngineTexture> Tex = UContentsHelper::MapTex;

#ifdef _DEBUG
	if (nullptr == Tex)
	{
		MsgBoxAssert("�̹��� �浹üũ�� �̹����� �������� �ʽ��ϴ�.");
	}
#endif

	Direction();
	PlayerPos.Y = PlayerPos.Y - 44;
	PlayerPos.Y = -PlayerPos.Y;

	Color8Bit Color = Tex->GetColor(PlayerPos, Color8Bit::Black);

	if (Color != Color8Bit::Black)
	{
		AddActorLocation(float4::Down * _DeltaTime * 350.0f);
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
	LastMoveVector + JumpVector;
}

void APlayer::CalMoveVector(float _DeltaTime)
{

}

void APlayer::CalJumpVector(float _DeltaTime)
{
}

void APlayer::CalGravityVector(float _DeltaTime)
{
}

void APlayer::MoveLastMoveVector(float _DeltaTime)
{
}

void APlayer::MoveUpdate(float _DeltaTime)
{
}

void APlayer::GroundUp()
{
}
