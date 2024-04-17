#pragma once
#include "TileMapLevel.h"


class APlayer;
class UCamera;
class ATileSet_Mode : public ATileMapLevel
{
	GENERATED_BODY(ATileMapLevel)

public:
	ATileSet_Mode();
	~ATileSet_Mode();

	// delete Function
	ATileSet_Mode(const ATileSet_Mode& _Other) = delete;
	ATileSet_Mode(ATileSet_Mode&& _Other) noexcept = delete;
	ATileSet_Mode& operator=(const ATileSet_Mode& _Other) = delete;
	ATileSet_Mode& operator=(ATileSet_Mode&& _Other) noexcept = delete;

protected:
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	std::shared_ptr<UCamera> Camera = nullptr;
};

