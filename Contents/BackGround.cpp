#include "PreCompile.h"
#include "BackGround.h"
#include <EngineCore/Renderer.h>

ABackGround::ABackGround()
{
	Renderer = CreateDefaultSubObject<URenderer>("Renderer");
	Renderer->SetMesh("Rect");
	// ���׸����� ���ִ¼���
	// ���׸����� �ȿ� ���ؽ����̴��� �ȼ����̴��� �Ѵ� ��� ����.
	// ����  ��Ƽ�������ü�� �������ش�.
	// 
	Renderer->SetMaterial("2DImage");
}

ABackGround::~ABackGround()
{
}

void ABackGround::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(1000.0f, 300.0f, 100.0f));

	// �����ָ� �������Ѵ�.
	Renderer->Resources->SettingConstantBuffer("OutPutColor", Color);
	// ���ο��� ���÷��� ���� ã��
	Renderer->Resources->SettingTexture("Image", "MainLogo.png", "POINT");

	//Renderer->

}

void ABackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
