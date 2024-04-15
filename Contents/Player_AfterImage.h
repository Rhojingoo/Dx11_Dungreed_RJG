#pragma once
#include <EngineCore/Actor.h>

class USpriteRenderer;
class APlayer_AfterImage : public AActor
{
	GENERATED_BODY(AActor)
public:
	APlayer_AfterImage();
	~APlayer_AfterImage();

	APlayer_AfterImage(const APlayer_AfterImage& _Other)					= delete;
	APlayer_AfterImage(APlayer_AfterImage& _Other) noexcept					= delete;
	APlayer_AfterImage& operator =(const 	APlayer_AfterImage& _Other)		= delete;
	APlayer_AfterImage& operator =(APlayer_AfterImage& _Other)noexcept		= delete;

	void ImageOn() 
	{ 
		Switch = true;
		Color = { 0.f,0.f,0.f,255.f };
		Renderer->ChangeAnimation("Player_AfterImage");
	}
	void RightDir() { Renderer->SetDir(EEngineDir::Right); }
	void LeftDir() { Renderer->SetDir(EEngineDir::Left); }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* Renderer = nullptr;

	bool Switch = false;
	float4 Color = { 0.f,0.f,0.f,255.f };
};


