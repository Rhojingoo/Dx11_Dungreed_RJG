#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
class USpriteRenderer;
class ABackGround : public AActor
{
	GENERATED_BODY(AActor)

public : 
	ABackGround();
	~ABackGround();

	ABackGround(const ABackGround& _Other)					 = delete;
	ABackGround(ABackGround& _Other) noexcept				 = delete;
	ABackGround& operator =(const ABackGround& _Other)		 = delete;
	ABackGround& operator =(ABackGround& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	USpriteRenderer* Renderer = nullptr;
	USpriteRenderer* Front_Renderer = nullptr;
	USpriteRenderer* Mid_Renderer = nullptr;
	USpriteRenderer* Back_Renderer = nullptr;

private:	
	//URenderer* Renderer;
	//float4 Color;

};

