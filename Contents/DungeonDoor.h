#pragma once
#include <EngineCore/Actor.h>

class AFadeIn_OUT_Black;
class UCollision;
class UDefaultSceneComponent;
class USpriteRenderer;
class ADungeonDoor : public AActor
{
	GENERATED_BODY(AActor)
public:
	ADungeonDoor();
	~ADungeonDoor();

	ADungeonDoor(const ADungeonDoor& _Other) = delete;
	ADungeonDoor(ADungeonDoor& _Other) noexcept = delete;
	ADungeonDoor& operator =(const 	ADungeonDoor& _Other) = delete;
	ADungeonDoor& operator =(ADungeonDoor& _Other)noexcept = delete;

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
};

