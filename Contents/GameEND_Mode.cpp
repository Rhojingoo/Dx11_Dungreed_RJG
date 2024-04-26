#include "PreCompile.h"
#include "GameEND_Mode.h"
#include <EngineCore/Camera.h>
#include "TitleCusor.h"
#include "GameEnd_BackGround.h"
#include "EndLevel_UI.h"


AGameEND_Mode::AGameEND_Mode()
{
}

AGameEND_Mode::~AGameEND_Mode()
{
}

void AGameEND_Mode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	GetWorld()->SpawnActor<AGameEnd_BackGround>("End_Bg", EOBJ_Order::BackGround);

	std::shared_ptr<TitleCusor> TitleCursorUI = GetWorld()->SpawnActor<TitleCusor>("ATitle_CursorUI", EOBJ_Order::Cursor);
	TitleCursorUI->SetActorLocation({ 0.0f, 0.0f, 200.0f });

	std::shared_ptr<AEndLevel_UI> EnidLevel_UI = GetWorld()->SpawnActor<AEndLevel_UI>("EnidLevel_UI", EOBJ_Order::Damage_Screen);
	TitleCursorUI->SetActorLocation({ 0.0f, 0.0f, 200.0f });
	

}

void AGameEND_Mode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

