#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class ATitlre_Cloud : public AActor
{
	GENERATED_BODY(AActor)

public:
	ATitlre_Cloud();
	~ATitlre_Cloud();

	// delete Function
	ATitlre_Cloud(const ATitlre_Cloud& _Other) = delete;
	ATitlre_Cloud(ATitlre_Cloud&& _Other) noexcept = delete;
	ATitlre_Cloud& operator=(const ATitlre_Cloud& _Other) = delete;
	ATitlre_Cloud& operator=(ATitlre_Cloud&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* FrontCloud_Renderer = nullptr;
	USpriteRenderer* BackCloud_Renderer = nullptr;
	FVector Vertexplus = {};

};

