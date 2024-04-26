#pragma once
#include <EngineCore/GameMode.h>

class AGameEND_Mode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	AGameEND_Mode();
	~AGameEND_Mode();

	// delete Function
	AGameEND_Mode(const AGameEND_Mode& _Other) = delete;
	AGameEND_Mode(AGameEND_Mode&& _Other) noexcept = delete;
	AGameEND_Mode& operator=(const AGameEND_Mode& _Other) = delete;
	AGameEND_Mode& operator=(AGameEND_Mode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:


};
