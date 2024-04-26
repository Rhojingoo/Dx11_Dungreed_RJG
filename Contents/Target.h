#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
#include "Cursor.h"

class ATarget : public ACursor
{
	GENERATED_BODY(ACursor)
public:
	ATarget();
	~ATarget();

	// delete Function
	ATarget(const ATarget& _Other) = delete;
	ATarget(ATarget&& _Other) noexcept = delete;
	ATarget& operator=(const ATarget& _Other) = delete;
	ATarget& operator=(ATarget&& _Other) noexcept = delete;
	
	FVector GetPos() { return TargetPos; }


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	//void RendererOff();
	//void RendererOn();

private:


};

