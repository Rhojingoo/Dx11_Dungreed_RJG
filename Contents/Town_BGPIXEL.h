#pragma once
#include "BackGround.h"
#include <EngineCore/SpriteRenderer.h>

class ATown_BGPIXEL : public ABackGround
{
	GENERATED_BODY(AActor)
public:
	ATown_BGPIXEL();
	~ATown_BGPIXEL();

	// delete Function
	ATown_BGPIXEL(const ATown_BGPIXEL& _Other) = delete;
	ATown_BGPIXEL(ATown_BGPIXEL&& _Other) noexcept = delete;
	ATown_BGPIXEL& operator=(const ATown_BGPIXEL& _Other) = delete;
	ATown_BGPIXEL& operator=(ATown_BGPIXEL&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:


};

