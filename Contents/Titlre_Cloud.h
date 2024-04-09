#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class Titlre_Cloud : public AActor
{
	GENERATED_BODY(AActor)

public:
	Titlre_Cloud();
	~Titlre_Cloud();

	// delete Function
	Titlre_Cloud(const Titlre_Cloud& _Other) = delete;
	Titlre_Cloud(Titlre_Cloud&& _Other) noexcept = delete;
	Titlre_Cloud& operator=(const Titlre_Cloud& _Other) = delete;
	Titlre_Cloud& operator=(Titlre_Cloud&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Renderer = nullptr;

};

