#pragma once
#include <EngineCore/Actor.h>


enum class IcePillarState
{
	None,
	Intro,
	Idle,
	Rotation,
	Stop,
	Attack01,
	Attack02,
	Attack03,
	Attack04,
};


class UCollision;
class AMonster_HpBar;
class UDefaultSceneComponent;
class APlayer;
class AIceBullet;
class USpriteRenderer;
class ABoss_IcePillar : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABoss_IcePillar();
	~ABoss_IcePillar();

	ABoss_IcePillar(const ABoss_IcePillar& _Other)						= delete;
	ABoss_IcePillar(ABoss_IcePillar& _Other) noexcept					= delete;
	ABoss_IcePillar& operator =(const 	ABoss_IcePillar& _Other)		= delete;
	ABoss_IcePillar& operator =(ABoss_IcePillar& _Other)noexcept		= delete;

	bool IsCreate() {return Create_Check;}
	void AddPos(FVector _Set) 
	{
		Renderer->AddPosition({ _Set.X, _Set.Y, 0.0f });
	}
	void SetPos(FVector _Set)
	{
		Renderer->SetPosition({ _Set.X, _Set.Y, 0.0f });
	}
	FVector GetPos() { return Renderer->GetLocalPosition(); };

	void SetPlayer(std::shared_ptr<APlayer> _Set) { Player = _Set; }
	void StateChange(IcePillarState _State);
	bool ISIntro() { return IntroCheck; }
	bool IsAttackEnd() { return AttackEnd; }
	void AttackEndFalse() { AttackEnd = false; }
	void FireOn() { SetBullet = true; }
	void DeathCheck();
	bool IsDeath() {return Death;}
	void Regenerate();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateUpdate(float _DeltaTime);
	void CreatBullet(FVector _Dir, FVector _Pos);

private:
	FVector BulletDir = {};
	FVector Pos = {};
	FVector RenderPos = {};
	FVector WorldRottation = {};
	FVector LocalRottation = {};

	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<AMonster_HpBar> Hp_Bar = nullptr;
	

	FVector PlayerPos = {};
	//std::shared_ptr<AIceBullet> IceBullet = nullptr;
	std::shared_ptr<AIceBullet> IceBullet[13] = {};
	bool SetBullet = false;
	bool Create_Bullets = false;
	bool AttackEnd = false;
	bool IcePillarSetting = false;
	bool AttackDirSet = false;
	float FireTime = 0.f;
	float CheckTime = 0.f;
	int AttackCount = 0;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Center_Renderer = nullptr;
	UCollision* Collision = nullptr;

	bool Create_Check = false;

	IcePillarState IcePillar_State = IcePillarState::None;


	void IcePillar_Intro(float _DeltaTime);
	void IcePillar_IntroStart();
	void IcePillar_Idle(float _DeltaTime);
	void IcePillar_IdleStart();
	void IcePillar_Rotation(float _DeltaTime);
	void IcePillar_Stop(float _DeltaTime);


	void IcePillar_Attack_1(float _DeltaTime);
	void IcePillar_AttackStart_1();

	void IcePillar_Attack_2(float _DeltaTime);
	void IcePillar_AttackStart_2();

	void IcePillar_Attack_3(float _DeltaTime);
	void IcePillar_AttackStart_3();

	void IcePillar_Attack_4(float _DeltaTime);
	void IcePillar_AttackStart_4();

	bool IntroCheck = false;



	FVector UpDir = {};
	FVector CenterDir = {};
	FVector BotDir = {};
	FVector UpPosition = {};
	FVector CenterPosition = {};
	FVector BotPosition = {};

	const float MaxHp = 500.f;
	float Hp = MaxHp;
	bool Death = false;
};

