#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/Renderer.h>
#include "ContentsHelper.h"
#include <cmath>

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

	Cursor = GetWorld()->SpawnActor<ATarget>("Target");
	Cursor->SetActorLocation({ 640.0f, -360.0f, 200.0f });

	Right_Hand = GetWorld()->SpawnActor<APlayer_Hand>("R_Hand");
	Right_Hand->SetActorLocation({ 640.0f, -360.0f, 200.0f });
	//Left_Hand = GetWorld()->SpawnActor<APlayer_Hand>("L_Hand");
	//Left_Hand->SetActorLocation({ 640.0f, -360.0f, 200.0f });	

	Sowrd = GetWorld()->SpawnActor<ALegendSowrd>("Sowrd");
	Sowrd->SetActorLocation({ 640.0f, -360.0f, 200.0f });


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

	
	//Renderer->SetSprite("CuttingTest.png", 11);
	Renderer->SetAutoSize(3.f, true);
	
	Renderer->SetOrder(7);
	
	Renderer->ChangeAnimation("Player_Idle");
	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);
	DebugFunction();

	PlayerPos = GetActorLocation();
	Right_Hand->SetActorLocation({ PlayerPos.X+20,PlayerPos.Y -25, PlayerPos.Z -1});
	Sowrd ->SetActorLocation({ PlayerPos.X + 30,PlayerPos.Y + 55, PlayerPos.Z - 1 });

	FVector PlayerPos = GetActorLocation();
	FVector CursorPos = Cursor->GetPos();

	// Ŀ�� ���������� 2D ���� ���
	FVector Dir = CursorPos - PlayerPos;
	Dir.Z = 0; // Z �� ���� ȸ�� ��꿡 ������ �����Ƿ� 0���� ����

	// atan2�� ����Ͽ� Ŀ�� ���⿡ ���� ���� ��� (����)
	float CursorAngleRad = std::atan2(Dir.Y, Dir.X);

	
	const float Degrees = 100.0f;
	const float AdditionalAngleRad = Degrees * (UEngineMath::PI / 180.f);

	float FinalAngleRad = CursorAngleRad + AdditionalAngleRad;

	FVector SwordRotation = FVector(0.0f, 0.0f, FinalAngleRad* (UEngineMath::PI / 180.f));
	//Sowrd->AddActorRotation(SwordRotation);
	//Sowrd->GetActorTransform().AddRotationDeg(SwordRotation);
	Sowrd->GetActorTransform().SetRotationDeg(SwordRotation);
	//Sowrd->SetActorRotation(SwordRotation);
	//Left_Hand->SetActorLocation({ PlayerPos.X - 20,PlayerPos.Y - 25, PlayerPos.Z - 1 });
	int a = 0;
	//Left_Hand->SetActorLocation();
}