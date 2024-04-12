#pragma once
#include <EngineCore/Actor.h>
#include "Target.h"

enum class Axis
{
	X,
	Y,
	Z,
	End,
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
	
	void InverseArmAxis(Axis axis);
	void SetTarget(std::shared_ptr<ATarget> _Cursor) 
	{
		Cursor = _Cursor;	
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Hand_Renderer = nullptr;
	USpriteRenderer* Sword_Renderer = nullptr;
	std::shared_ptr<ATarget> Cursor = nullptr;

	FVector PlayerPos = {};
	FVector CursorPos = {};
	bool Left = false;
	bool Right = false;
	bool Revurse_X;
	float Offset_Angle;
	bool RightSetting = true;
	bool LeftSetting = false;
};

