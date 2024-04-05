#pragma once
#include <EngineCore/GameMode.h>

class ABoss_GameMode :  public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	ABoss_GameMode();
	~ABoss_GameMode();

	ABoss_GameMode(const ABoss_GameMode& _Other)					= delete;
	ABoss_GameMode(ABoss_GameMode& _Other) noexcept					= delete;
	ABoss_GameMode& operator =(const 	ABoss_GameMode& _Other)		= delete;
	ABoss_GameMode& operator =(ABoss_GameMode& _Other)noexcept		= delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
};

