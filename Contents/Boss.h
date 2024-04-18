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
	Ready,

};


class APlayer;
class ABoss_IcePillar;
class USpriteRenderer;
class ABoss : public AActor
{
	GENERATED_BODY(AActor)

public:
	ABoss();
	~ABoss();

	ABoss(const ABoss& _Other)					= delete;
	ABoss(ABoss& _Other) noexcept					= delete;
	ABoss& operator =(const 	ABoss& _Other)		= delete;
	ABoss& operator =(ABoss& _Other)noexcept		= delete;

	void SetPlayer(std::shared_ptr<APlayer> _Set); 


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
	void Boss_Patton4(float _DeltaTime);

	void Boss_Ready(float _DeltaTime);
	void Boss_ReadyStart();
	//void RendererOff();
	//void RendererOn();

private:
	USpriteRenderer* Renderer = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<ABoss_IcePillar> IcePillar[4] = {};
	BossState Boss_State = BossState::Idle;

	FVector Bullet_Pos[4] = {};
	const float Bullet = 150.f;
	float Boss_Time = 0.f;
	bool IntroOn = false;
	bool Attack_Check = false;
	bool Attack_End = false;
	void CreateIcePillar();
	void Direction();
};

