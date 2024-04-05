#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATitleMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	ATitleMode();
	~ATitleMode();

	// delete Function
	ATitleMode(const ATitleMode& _Other) = delete;
	ATitleMode(ATitleMode&& _Other) noexcept = delete;
	ATitleMode& operator=(const ATitleMode& _Other) = delete;
	ATitleMode& operator=(ATitleMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

