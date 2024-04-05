#pragma once
#include <EngineCore/GameMode.h>

class ATown_GameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	ATown_GameMode();
	~ATown_GameMode();

	ATown_GameMode(const ATown_GameMode& _Other)					= delete;
	ATown_GameMode(ATown_GameMode& _Other) noexcept					= delete;
	ATown_GameMode& operator =(const 	ATown_GameMode& _Other)		= delete;
	ATown_GameMode& operator =(ATown_GameMode& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

