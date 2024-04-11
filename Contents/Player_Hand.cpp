#include "PreCompile.h"
#include "Player_Hand.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>


APlayer_Hand::APlayer_Hand()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

}


APlayer_Hand::~APlayer_Hand()
{
}

void APlayer_Hand::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(320.0f, 320.0f, 100.0f));
	//Renderer->SetSprite("CuttingTest.png", 11);

	Renderer->CreateAnimation("Player_Hand", "Player_Hand", 0.1f);
	Renderer->ChangeAnimation("Player_Hand");

	Renderer->SetAutoSize(3.f, true);

	Renderer->SetOrder(8);

}

void APlayer_Hand::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);	
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

