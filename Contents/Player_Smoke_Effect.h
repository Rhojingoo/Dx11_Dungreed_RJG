#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class APlayer_Smoke_Effect : public AActor
{
	GENERATED_BODY(AActor)
public:
	APlayer_Smoke_Effect();
	~APlayer_Smoke_Effect();

	APlayer_Smoke_Effect(const APlayer_Smoke_Effect& _Other) = delete;
	APlayer_Smoke_Effect(APlayer_Smoke_Effect& _Other) noexcept = delete;
	APlayer_Smoke_Effect& operator =(const 	APlayer_Smoke_Effect& _Other) = delete;
	APlayer_Smoke_Effect& operator =(APlayer_Smoke_Effect& _Other)noexcept = delete;

	bool CanPlayEffect() { return Renderer->IsCurAnimationEnd(); }
	void SmokeOn() { Smoke_Switch = true; }
	void Dash_Smoke_On() { Dash_SmokeOn = true; }
	void Run_Smoke_On() { Run_SmokeON = true; }
	void Right_Dir() { Renderer->SetDir(EEngineDir::Right); }
	void Left_Dir() { Renderer->SetDir(EEngineDir::Left); }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* Renderer = nullptr;
	bool Smoke_Switch= false;
	bool Dash_SmokeOn = false;
	bool Run_SmokeON = false;
	float4 Color;
};