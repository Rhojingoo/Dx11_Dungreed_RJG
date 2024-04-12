#pragma once
#include <EngineCore/Actor.h>
#include "Target.h"

enum class Hand_LeftRight
{
	Left,
	Right,
	End
};


class USpriteRenderer;
class APlayer_Hand : public AActor
{
	GENERATED_BODY(AActor)



public:
	APlayer_Hand();
	~APlayer_Hand();

	// delete Function
	APlayer_Hand(const APlayer_Hand& _Other) = delete;
	APlayer_Hand(APlayer_Hand&& _Other) noexcept = delete;
	APlayer_Hand& operator=(const APlayer_Hand& _Other) = delete;
	APlayer_Hand& operator=(APlayer_Hand&& _Other) noexcept = delete;
	
	void SetTarget(std::shared_ptr<ATarget> _Cursor) 
	{
		Cursor = _Cursor;	
	}
	void Right();
	void Left();
	void Hand_Dir();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Hand_Renderer = nullptr;
	USpriteRenderer* Sword_Renderer = nullptr;
	std::shared_ptr<ATarget> Cursor = nullptr;
	Hand_LeftRight Hand_RL= Hand_LeftRight::Right;

	FVector PlayerPos = {};
	FVector CursorPos = {};


	bool Revurse_X;
	float Offset_Angle;

	bool RightSetting = true;
	bool LeftSetting = false;
	bool UpSetting = true;



	FVector Dir = {};
	FVector SwordRotation = {};
};

