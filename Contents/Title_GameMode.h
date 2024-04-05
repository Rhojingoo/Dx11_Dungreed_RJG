#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATitle_GameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ATitle_GameMode();
	~ATitle_GameMode();

	// delete Function
	ATitle_GameMode(const ATitle_GameMode& _Other) = delete;
	ATitle_GameMode(ATitle_GameMode&& _Other) noexcept = delete;
	ATitle_GameMode& operator=(const ATitle_GameMode& _Other) = delete;
	ATitle_GameMode& operator=(ATitle_GameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

