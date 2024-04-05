#include "PreCompile.h"
#include "BackGround.h"
#include <EngineCore/Renderer.h>

ABackGround::ABackGround()
{
	Renderer = CreateDefaultSubObject<URenderer>("Renderer");
	Renderer->SetMesh("Rect");
	// 메테리얼을 해주는순간
	// 메테리얼은 안에 버텍스쉐이더와 픽셀쉐이더를 둘다 들고 있죠.
	// 색깔  머티리얼그자체에 세팅해준다.
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

	// 안해주면 터져야한다.
	Renderer->Resources->SettingConstantBuffer("OutPutColor", Color);
	// 내부에서 샘플러도 같이 찾을
	Renderer->Resources->SettingTexture("Image", "MainLogo.png", "POINT");

	//Renderer->

}

void ABackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
