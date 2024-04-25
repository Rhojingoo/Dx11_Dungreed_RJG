#pragma once
#include <EngineCore/Actor.h>
#include "Target.h"
#include "Player_Attack_Effect.h"


enum class SwordHand_Type
{
	None,
	Demon_Sword,
	Demon_Blade,
	AttackEnd,
};


enum class Hand_LeftRight
{
	Left,
	Right,
	End
};

class UImage;
class UCollision;
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
	void Attack_Effect_Dir();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void HandStateUpdate();
	

	void SwordType_Choice();
	void ChangeSwordType(SwordHand_Type _Set);
	void DemonBlade_Choice();
	void LasliSword_Choice();

private:
	static SwordHand_Type SwordType;

	UImage* Weapon_Front_UI = nullptr;
	UImage* Weapon_Back_UI = nullptr;
	UImage* WeaponType = nullptr;


	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Hand_Renderer = nullptr;
	USpriteRenderer* Sword_Renderer = nullptr;
	USpriteRenderer* AttatEffect_Renderer = nullptr;
	UCollision* Collision = nullptr;

	std::shared_ptr<APlayer_Attack_Effect> Swing_EF = nullptr;
	float Attack_Degree = 0.f;
	FVector Attack_EffectDir = {};

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

