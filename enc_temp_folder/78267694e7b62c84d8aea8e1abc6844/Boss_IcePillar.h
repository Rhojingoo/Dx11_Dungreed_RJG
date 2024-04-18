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
};


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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateUpdate(float _DeltaTime);

private:
	FVector BulletDir = {};
	FVector Pos = {};
	FVector RenderPos = {};
	std::shared_ptr<APlayer> Player = nullptr;
	FVector PlayerPos = {};
	//std::shared_ptr<AIceBullet> IceBullet = nullptr;
	std::shared_ptr<AIceBullet> IceBullet[12] = {};
	bool SetBullet = false;
	bool AttackEnd = false;
	bool AttackDirSet = false;
	float FireTime = 0.f;

	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Center_Renderer = nullptr;
	
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

	bool IntroCheck = false;

};

