#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>

// 설명 :
class ATarget;
class APlayer_Hand;
class APlayer_AfterImage;
class APlayer_Smoke_Effect;
class UCollision;
class USpriteRenderer;
class APlayer : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	UStateManager State;
	void SetColTown() { Foot_Collision_Check_At_Town = true; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//void RendererOff();
	//void RendererOn();

private:
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* ChildRenderer = nullptr;
	UCollision* Collision;
	float4 Color;
	std::shared_ptr<ATarget> Cursor = nullptr;
	std::shared_ptr<APlayer_Hand> Right_Hand = nullptr;
	//std::shared_ptr<APlayer_Hand> Left_Hand = nullptr;
	std::shared_ptr<APlayer_Smoke_Effect> Smoke_Effect = nullptr;
	std::shared_ptr<APlayer_AfterImage> After_Image[10] = {};

	
	

	FVector PlayerPos = {};
	FVector CursorPos = {};
	bool JumpOn = false;
	bool JumpCheck = false;
	float JumpSpeed = 750.f;


	void StateInit();

	void Die(float _DeltaTime);

	void Idle(float _DeltaTime);

	void JumpStart();
	void Jump(float _DeltaTime);

	void RunStart();
	void Run(float _DeltaTime);

	void DashStart();
	void Dash(float _DeltaTime);
	void Dash_Effect_Call();

	void SecondDashStart();
	void SecondDash(float _DeltaTime);

	void DebugFunction();

	void Direction();
	void Dash_Direction(float _DeltaTime);

	void CalLastMoveVector(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);
	void CalJumpVector(float _DeltaTime);
	void CalGravityVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);
	void GroundUp(float _DeltaTime);
	void AddMoveVector(const FVector& _DirDelta);
	void PlayAfterImage(float _DeltaTime, FVector _PlayerPos);
	

	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = FVector::Right * 500.0f;
	float MoveMaxSpeed = 500.0f;

	FVector GravityAcc = FVector::Down * 2000.0f;
	FVector GravityVector = FVector::Zero;

	FVector JumpPower = FVector::Up * 750;
	FVector JumpVector = FVector::Zero;
	FVector DashVector = FVector::Zero;
	FVector SecondDashVector = FVector::Zero;

	// 내가 나갈 모든 방향의 합
	FVector LastMoveVector = FVector::Zero;
	FVector DashDir = FVector::Zero;
	float DashDeceleration = 20.0f;
	float DashTime = 0.f;
	int DashCount = 0;
	const int DashMax = 2;
	bool Foot_Collision_Check_At_Town = false;

	//이미지 잔상
	bool AfterImageSwitch = false;
	float AfterImage_Time = 0.f;
	bool AfterImageRight = false;

	void colorsetting();
};

