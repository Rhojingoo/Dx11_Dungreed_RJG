#pragma once
#include <EngineCore/Actor.h>
#include <EnginePlatform\EngineSound.h>

class AFadeIn_OUT_Black;
class UCollision;
class UDefaultSceneComponent;
class USpriteRenderer;
class ATown_DungeonDoor : public AActor
{
	GENERATED_BODY(AActor)
public:
	ATown_DungeonDoor();
	~ATown_DungeonDoor();

	ATown_DungeonDoor(const ATown_DungeonDoor& _Other)					= delete;
	ATown_DungeonDoor(ATown_DungeonDoor& _Other) noexcept					= delete;
	ATown_DungeonDoor& operator =(const 	ATown_DungeonDoor& _Other)		= delete;
	ATown_DungeonDoor& operator =(ATown_DungeonDoor& _Other)noexcept		= delete;

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

