#pragma once
#include <EngineCore/GameMode.h>

class UCamera;
class AGameEnd_BackGround;
class AEndLevel_UI;
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

	static void EndLevelEnter() { EndLevel = true; }
	static void BossClear() { Boss_Clear = true; }
	static void PlayerDie() { Player_Die = true; }

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	std::shared_ptr<UCamera> Camera = nullptr;
	std::shared_ptr<AEndLevel_UI> EndUI = nullptr;
	std::shared_ptr<AGameEnd_BackGround> BackGR = nullptr;

	static bool EndLevel;
	static bool Boss_Clear;
	static bool Player_Die;

	float Time = 0.f;
};
