#pragma once
#include <EngineCore/Actor.h>

class AFadeIn_OUT_Black;
class UCollision;
class UDefaultSceneComponent;
class USpriteRenderer;
class ABossDoor : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABossDoor();
	~ABossDoor();

	ABossDoor(const ABossDoor& _Other) = delete;
	ABossDoor(ABossDoor& _Other) noexcept = delete;
	ABossDoor& operator =(const 	ABossDoor& _Other) = delete;
	ABossDoor& operator =(ABossDoor& _Other)noexcept = delete;


	void BossOpne()
	{
		Renderer->ChangeAnimation("BossDoorOpen");
		BossRoomOPENStart = true;			
	}
	void Dungeon_Enter();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	float Time = 0.f;

	std::shared_ptr<AFadeIn_OUT_Black> Fade = nullptr;
	AFadeIn_OUT_Black* Fadeprt = nullptr;

	bool ColCheck = false;
	bool FadeStart = false;
	bool BossRoomOPENStart = false;
};

