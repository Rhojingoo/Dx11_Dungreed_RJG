#pragma once
#include <EngineCore/Actor.h>

enum class MonsterState
{
	Idle,
	Left,
	Right,
	Move,
	Attack,
	Death,
};

class UCollision;
class APlayer;
class UDefaultSceneComponent;
class USpriteRenderer;
class AMonster : public AActor
{
	GENERATED_BODY(AActor)
public:
	AMonster();
	~AMonster();

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster& _Other) noexcept = delete;
	AMonster& operator =(const 	AMonster& _Other) = delete;
	AMonster& operator =(AMonster& _Other)noexcept = delete;

	void SetPlayer(std::shared_ptr<APlayer> _Set) { Player = _Set; };

	float Getdamage();
	bool IsDieMonster() { return MonsterDie; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void Idle(float _DeltaTime) {};
	virtual void IdleStart() {};

	virtual void Left(float _DeltaTime) {};
	virtual void LeftStart() {};

	virtual void Right(float _DeltaTime) {};
	virtual void RightStart() {};

	virtual void Move(float _DeltaTime) {};
	virtual void MoveStart() {};

	virtual void Attack(float _DeltaTime) {};
	virtual void AttackStart() {};

	virtual void Death(float _DeltaTime) {};
	virtual void DeathStart() {};

	virtual void ChangeState(MonsterState _Set);
	virtual void StateUpdate(float _DeltaTime);
	virtual void CollisionCheck_Function();
	virtual void DeathEffect() {};

	MonsterState Monster_state = MonsterState::Idle;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* EffectRenderer = nullptr;
	UCollision* Collision = nullptr;
	UCollision* SerchCollision = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;
	bool MonsterDie = false;

private:
};

