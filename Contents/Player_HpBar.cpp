#include "PreCompile.h"
#include "Player_HpBar.h"
#include <EngineCore/Image.h>
#include <EngineCore/TextWidget.h>
#include <EngineCore/Image.h>

APlayer_HpBar::APlayer_HpBar()
{

}

APlayer_HpBar::~APlayer_HpBar()
{
}

void APlayer_HpBar::BeginPlay()
{
	Super::BeginPlay();
		
	{
		PlayerLifeBase = CreateWidget<UImage>(GetWorld(), "PlayerLifeBase");
		PlayerLifeBase->AddToViewPort(1);
		PlayerLifeBase->SetSprite("PlayerLifeBase.png");
		PlayerLifeBase->SetAutoSize(4.f, true);
		PlayerLifeBase->SetPosition({ -450, 300 });
		PlayerLifeBase->SetOrder(1);

		PlayerLifeBack = CreateWidget<UImage>(GetWorld(), "PlayerLifeBack");
		PlayerLifeBack->AddToViewPort(0);
		PlayerLifeBack->SetSprite("PlayerLifeBack.png");
		PlayerLifeBack->SetAutoSize(4.f, true);
		PlayerLifeBack->SetPosition({ -450, 300 });
		PlayerLifeBack->SetOrder(0);

		LifeBar = CreateWidget<UImage>(GetWorld(), "LifeBar");
		LifeBar->AddToViewPort(3);
		LifeBar->SetSprite("LifeBar.png");
		//LifeBar->SetParent({ PlayerLifeBase });
		LifeBar->SetScale({ 200.f,50.f });
		LifeBar->SetOrder(3);

		LifeBarWave = CreateWidget<UImage>(GetWorld(), "Player_LifeWave");
		LifeBarWave->AddToViewPort(2);
		LifeBarWave->CreateAnimation("Player_LifeWave", "Player_LifeWave", 0.1f);
		LifeBarWave->SetParent(LifeBar);
		LifeBarWave->SetScale({ 0.15f,1.f });
		LifeBarWave->AddPosition({ 0.55f,0.f });
		LifeBarWave->SetOrder(2);
		LifeBarWave->SetActive(false);

		PlayerPicture = CreateWidget<UImage>(GetWorld(), "PlayerUI");
		PlayerPicture->AddToViewPort(4);
		PlayerPicture->SetSprite("PlayerUI.png");
		PlayerPicture->SetAutoSize(4.f, true);
		PlayerPicture->SetPosition({ -550, 300 });
		PlayerPicture->SetOrder(4);		
	}


}

void APlayer_HpBar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (EnergyDown == true)
	{
		WaveHp = true;
		if (Life <= 0.f)
		{
			return;
		}
		Life -= MaxLife - (MaxLife * ratio);
		float Setratio = (Life / MaxLife);  // ü�� ������ ���
		float fullWidth = LifeBar->GetWorldScale().X;  // �̹��� ��ü ����
		float basePos = -410;  // �⺻ ��ġ
		LifePos = basePos - ((MaxLife / 2) * (1 - Setratio));  // ���� ��ŭ �������� �̵�
		if (WaveHp == true)
		{
			LifeBarWave->SetActive(true);
			LifeBarWave->ChangeAnimation("Player_LifeWave");
		}
		EnergyDown = false;
	}


	if (UEngineInput::IsDown('M'))
	{
		WaveHp = true;
		Life -= 10;
		float Setratio = (Life / MaxLife);  // ü�� ������ ���
		float fullWidth = LifeBar->GetWorldScale().X;  // �̹��� ��ü ����
		float basePos = -410;  // �⺻ ��ġ
		LifePos = basePos - ((MaxLife / 2) * (1 - Setratio));  // ���� ��ŭ �������� �̵�
		if (WaveHp == true)
		{
			LifeBarWave->SetActive(true);
			LifeBarWave->ChangeAnimation("Player_LifeWave");
		}
	}
	LifeBar->SetScale({ Life, 50.f });
	LifeBar->SetPosition({ LifePos, 300.f });
}
	
//ȣ�����
//{
	// �ڱ��ڽ��� �ڱ��ڽ��� std::shared_ptr<UImage>�� ������ �־ ����.
			// �𸮾� �����Ѱ�
			// �𸮾� �ȳ��ɴϴ�.
			//ȣ�����
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

				// ȭ�鿡 ���� �Ѵ�.
				// Image->SetSprite("HPBar");
				// Image->SetScale();
//}