#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include "Cursor.h"


class UCollision;
class TitleCusor : public ACursor
{
	GENERATED_BODY(ACursor)
public:
	TitleCusor();
	~TitleCusor();

	// delete Function
	TitleCusor(const TitleCusor& _Other) = delete;
	TitleCusor(TitleCusor&& _Other) noexcept = delete;
	TitleCusor& operator=(const TitleCusor& _Other) = delete;
	TitleCusor& operator=(TitleCusor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UCollision* Collision = nullptr;

};

