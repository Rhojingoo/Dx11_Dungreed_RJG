#include "PreCompile.h"
#include "AHP_Bar.h"
#include <EngineCore/Image.h>


AHP_Bar::AHP_Bar()
{

}

AHP_Bar::~AHP_Bar()
{
}

void AHP_Bar::BeginPlay()
{
	Super::BeginPlay();

	{
		// UI를 만들겠다.
		// std::shared_ptr<UImage> Image = CreateWidget<UImage>(GetWorld(), "HpBar");
		PlayerLifeBase = CreateWidget<UImage>(GetWorld(), "PlayerLifeBase  ");
		PlayerLifeBase->AddToViewPort(3);
		PlayerLifeBase->SetSprite("PlayerLifeBase.png");
		PlayerLifeBase->SetAutoSize(4.f, true);
		PlayerLifeBase->SetPosition({ -450, 300 });
		PlayerLifeBase->SetOrder(3);
		


		PlayerLifeBack = CreateWidget<UImage>(GetWorld(), "PlayerLifeBack ");
		PlayerLifeBack->AddToViewPort(0);
		PlayerLifeBack->SetSprite("PlayerLifeBack.png");
		PlayerLifeBack->SetAutoSize(4.f, true);
		PlayerLifeBack->SetPosition({ -450, 300 });
		PlayerLifeBack->SetOrder(0);


		LifeBar = CreateWidget<UImage>(GetWorld(), "LifeBar ");
		LifeBar->AddToViewPort(1);
		LifeBar->SetSprite("LifeBar.png");
		//LifeBar->SetAutoSize(4.f, true);
		LifeBar->SetParent({ PlayerLifeBase });
		LifeBar->SetScale({ 200.f,50.f });
		//LifeBar->SetPosition({ 0, 300 });
		LifeBar->SetOrder(1);


		LifeBarWave = CreateWidget<UImage>(GetWorld(), "LifeBarWave ");
		LifeBarWave->AddToViewPort(2);
		LifeBarWave->CreateAnimation("LifeBar_LifeWave", "LifeBar_LifeWave", 0.1f);
		//LifeBarWave->SetAutoSize(0.05f, true);
		LifeBarWave->SetParent(LifeBar);
		LifeBarWave->SetScale({ 0.15f,1.f });
		LifeBarWave->AddPosition({ 0.55f,0.f });
		//LifeBarWave->SetPosition({ LifeBar->GetLocalPosition().X+100,LifeBar->GetLocalPosition().Y,LifeBar->GetLocalPosition().Z });
		LifeBarWave->SetOrder(2);
		//LifeBarWave->ChangeAnimation("LifeBar_LifeWave");





		// 자기자신이 자기자신을 std::shared_ptr<UImage>로 가지고 있어도 난다.
		// 언리얼 따라한것
		// 언리얼 안나옵니다.
		//호버기능
		//Image->SetUnHover([=]()
		//	{
		//		Image->SetSprite("HPBar.png");
		//		// UEngineDebugMsgWindow::PushMsg("Hover!!!");
		//	});

		//Image->SetHover([=]()
		//	{
		//		Image->SetSprite("Back.png");
		//		Image->SetAutoSize(1.0f, false);
		//		// UEngineDebugMsgWindow::PushMsg("Hover!!!");
		//	});

	/*	Image->SetDown([=]()
			{
				UEngineDebugMsgWindow::PushMsg("Down!!!");
			});*/

			// Image->SetScale({200, 200});

			// 화면에 떠야 한다.
			// Image->SetSprite("HPBar");
			// Image->SetScale();
	}
}

void AHP_Bar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (UEngineInput::IsDown('M'))
	{	
		EnergyDown = true;
		Life -= 10;
		float Setratio = (Life / MaxLife);  // 체력 비율을 계산
		float fullWidth = LifeBar->GetWorldScale().X;  // 이미지 전체 길이
		float basePos = -410;  // 기본 위치
		LifePos = basePos - ((MaxLife/2) * (1 - Setratio));  // 깎인 만큼 왼쪽으로 이동
		if (EnergyDown == true)
		{
			LifeBarWave->ChangeAnimation("LifeBar_LifeWave");
			//LifeBarWave-> SetPosition({ LifePos+10, LifeBar->GetLocalPosition().Y });
		}
	}
	LifeBar->SetScale({ Life, 50.f });
	LifeBar->SetPosition({ LifePos, 300.f });
}
	

