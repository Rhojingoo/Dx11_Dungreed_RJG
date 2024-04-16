#pragma once
#include <EngineCore/Actor.h>

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
	void SetPos(FVector _Set) 
	{
		Renderer->AddPosition({ _Set.X, _Set.Y, 0.0f });
	}
	void SetPlayer(std::shared_ptr<APlayer> _Set) { Player = _Set; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	FVector BulletDir = {};
	FVector Pos = {};
	FVector RenderPos = {};
	std::shared_ptr<APlayer> Player = nullptr;
	FVector PlayerPos = {};
	//std::shared_ptr<AIceBullet> IceBullet = nullptr;
	std::shared_ptr<AIceBullet> IceBullet[12] = {};
	bool SetBullet = false;
	float FireTime = 0.f;

	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Center_Renderer = nullptr;

	
	bool Create_Check = false;
};

