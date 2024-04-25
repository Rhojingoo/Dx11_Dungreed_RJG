#pragma once
#include <EngineCore/Actor.h>

class UCollision;
class USpriteRenderer;
class ATitle_UI : public AActor
{
	GENERATED_BODY(AActor)
public:
	ATitle_UI();
	~ATitle_UI();

	ATitle_UI(const ATitle_UI& _Other)					= delete;
	ATitle_UI(ATitle_UI& _Other) noexcept					= delete;
	ATitle_UI& operator =(const 	ATitle_UI& _Other)		= delete;
	ATitle_UI& operator =(ATitle_UI& _Other)noexcept		= delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* GameStart_Renderer = nullptr;
	UCollision* GameStart_Collision = nullptr;

	USpriteRenderer* GameEnd_Renderer = nullptr;
	UCollision* GameEnd_Collision = nullptr;
};
