#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include "Target.h"

// 설명 :
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//void RendererOff();
	//void RendererOn();

private:
	USpriteRenderer* Renderer = nullptr;
	float4 Color;
	std::shared_ptr<ATarget> Cursor = nullptr;
	FVector PlayerPos = {};
	FVector CursorPos = {};
	bool JumpOn = false;
	float JumpSpeed = 750.f;


	void StateInit();

	void Die(float _DeltaTime);

	void Idle(float _DeltaTime);

	void JumpStart();
	void Jump(float _DeltaTime);

	void RunStart();
	void Run(float _DeltaTime);

	void DebugFunction();

	void Direction();

	void CalLastMoveVector(float _DeltaTime);
	void CalMoveVector(float _DeltaTime);
	void CalJumpVector(float _DeltaTime);
	void CalGravityVector(float _DeltaTime);
	void MoveLastMoveVector(float _DeltaTime);
	void MoveUpdate(float _DeltaTime);
	void GroundUp();



	FVector MoveVector = FVector::Zero;
	FVector MoveAcc = FVector::Right * 500.0f;
	float MoveMaxSpeed = 500.0f;

	FVector GravityAcc = FVector::Down * 2000.0f;
	FVector GravityVector = FVector::Zero;

	FVector JumpPower = FVector::Up * 1000;
	FVector JumpVector = FVector::Zero;
	// 내가 나갈 모든 방향의 합
	FVector LastMoveVector = FVector::Zero;


};

