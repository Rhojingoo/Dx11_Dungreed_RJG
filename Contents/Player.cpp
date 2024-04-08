#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(320.0f, 320.0f, 100.0f));
	
	Renderer->CreateAnimation("Player_Idle", "Player_Idle",0.1f);
	Renderer->CreateAnimation("Player_Jump", "Player_Jump", 0.1f);
	Renderer->CreateAnimation("Player_Run", "Player_Run", 0.1f);
	Renderer->CreateAnimation("Player_Die", "Player_Die", 0.1f);

	Renderer->CreateAnimation("Boss_Attack", "Boss_Idle", 0.1f);
	Renderer->CreateAnimation("Boss_Die", "Boss_Die", 0.1f);
	Renderer->CreateAnimation("Boss_Enter", "Boss_Enter", 0.1f);
	Renderer->CreateAnimation("Boss_Exit", "Boss_Exit", 0.1f);
	Renderer->CreateAnimation("Boss_Idle", "Boss_Idle", 0.1f);

	Renderer->ChangeAnimation("Player_Idle");


}

void APlayer::Tick(float _DeltaTime)
{
	// 위에 뭔가를 쳐야할때도 있다.
	Super::Tick(_DeltaTime);

	float Speed = 100.0f;

	if (true == UEngineInput::IsPress('1'))
	{
		Renderer->ChangeAnimation("Idle");
	}

	if (true == UEngineInput::IsPress('2'))
	{
		Renderer->ChangeAnimation("Jump");
	}

	if (true == UEngineInput::IsPress('3'))
	{
		Renderer->ChangeAnimation("Run");
	}

	if (true == UEngineInput::IsPress('4'))
	{
		Renderer->ChangeAnimation("Die");
	}


	if (true == UEngineInput::IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);		
	}

	if (true == UEngineInput::IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);		
	}

	if (true == UEngineInput::IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (true == UEngineInput::IsPress('S'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	//if (true == UEngineInput::IsPress(VK_NUMPAD1))
	//{
	//	Color.X += _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD2))
	//{
	//	Color.X -= _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD4))
	//{
	//	Color.Y += _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD5))
	//{
	//	Color.Y -= _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD7))
	//{
	//	Color.Z += _DeltaTime;
	//}

	//if (true == UEngineInput::IsPress(VK_NUMPAD8))
	//{
	//	Color.Z -= _DeltaTime;
	//}



	// Renderer->SetConstanctBuffer("Ftransform", GetTransform());


}

void APlayer::RendererOff()
{
	Renderer->SetSprite("CuttingTest.png", 11);
	//Renderer->SetActive(false);
	DelayCallBack(0.2f, std::bind(&APlayer::RendererOn, this));
}

void APlayer::RendererOn()
{
	Renderer->SetSprite("CuttingTest.png", 11);
	//Renderer->SetActive(true);
	DelayCallBack(0.2f, std::bind(&APlayer::RendererOff, this));
}
