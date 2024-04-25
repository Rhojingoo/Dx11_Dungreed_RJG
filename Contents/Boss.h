#pragma once
#include <EngineCore/Actor.h>
//#include <EngineCore/SpriteRenderer.h>

enum class BossState
{
	Intro,
	Idle,
	Patton1,
	Patton2,
	Patton3,
	Patton4,
	Patton5,
	Fainting,
	Ready,
	Ready2,
	Ready3,
	TeleportIn,
	TeleportOut,
	Death,
};

class UCollision;
class ABoss_HpBar;
class AIceSpear;
class APlayer;
class ABoss_IcePillar;
class USpriteRenderer;
class ABoss : public AActor
{
	GENERATED_BODY(AActor)

public:
	ABoss();
	~ABoss();

	ABoss(const ABoss& _Other)						= delete;
	ABoss(ABoss& _Other) noexcept					= delete;
	ABoss& operator =(const 	ABoss& _Other)		= delete;
	ABoss& operator =(ABoss& _Other)noexcept		= delete;

	void SetPlayer(std::shared_ptr<APlayer> _Set); 
	void SetTOWN() { Foot_Collision_Check_At_Town = true; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);
	void StateChange(BossState _State);


	void Boss_Intro(float _DeltaTime);
	void Boss_IntroStart();
	void Boss_Idle(float _DeltaTime);
	void Boss_IdleStart();
	void Boss_Patton1(float _DeltaTime);
	void Boss_Patton1Start();
	void Boss_Patton2(float _DeltaTime);
	void Boss_Patton2Start();
	void Boss_Patton3(float _DeltaTime);
	void Boss_Patton3Start();
	void Boss_Patton4(float _DeltaTime);
	void Boss_Patton4Start();
	void Boss_Patton5(float _DeltaTime);
	void Boss_Patton5Start();


	void IcePallarCheck();
	void Boss_Fainting(float _DeltaTime);
	void Boss_FaintingStart();
	
	void IceSpear_Aattack();

	void Boss_Ready(float _DeltaTime);
	void Boss_ReadyStart();

	void Boss_Ready2(float _DeltaTime);
	void Boss_ReadyStart2();

	void Boss_TeleportIn(float _DeltaTime);
	void Boss_TeleportInStart();

	void Boss_TeleportOut(float _DeltaTime);
	void Boss_TeleportOutStart();

	void Boss_Death(float _DeltaTime);
	void Boss_DeathStart();
		
	
private:
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Effect_Renderer = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<ABoss_IcePillar> IcePillar[4] = {};
	std::shared_ptr<AIceSpear> IceSpear = nullptr;
	std::shared_ptr<ABoss_HpBar>Boss_HpBAR = nullptr;
	BossState Boss_State = BossState::Idle;
	UCollision* Collision = nullptr;

	FVector GravityAcc = FVector::Down * 250.0f;
	FVector GravityVector = FVector::Zero;

	FVector PlRotation[4] = {};
	FVector Bullet_Pos[4] = {};
	const float Bullet = 150.f;
	float Boss_Time = 0.f;
	bool IntroOn = false;
	bool Attack_Check = false;
	bool Attack_End = false;

	void CreateIcePillar();
	void IcePillarPosSetting();
	void Direction();


	bool SpearCreat = false;
	bool IcicleCreat = false;
	static float IcePillarPos;

	bool Foot_Collision_Check_At_Town = false;
	bool DamageOn = false;
	bool Regenerate = false;

	const float Max_Hp = 2500.f;
	float Hp = Max_Hp;
	bool CollisionStart = false;

	const float MaxX_Map_Pos = 2080.f;
	const float MinX_Map_Pos = 400.f;
	const float MaxY_Map_Pos = 750.f;
	const float MinY_Map_Pos = 450.f;

	bool Death = false;
};

