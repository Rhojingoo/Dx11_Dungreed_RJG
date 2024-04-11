#pragma once
#include <EngineCore/Actor.h>

enum class Axis
{
	X,
	Y,
	Z,
	End,
};

class USpriteRenderer;
class APlayer_Hand : public AActor
{
	GENERATED_BODY(AActor)



public:
	APlayer_Hand();
	~APlayer_Hand();

	// delete Function
	APlayer_Hand(const APlayer_Hand& _Other) = delete;
	APlayer_Hand(APlayer_Hand&& _Other) noexcept = delete;
	APlayer_Hand& operator=(const APlayer_Hand& _Other) = delete;
	APlayer_Hand& operator=(APlayer_Hand&& _Other) noexcept = delete;
	
	void InverseArmAxis(Axis axis);


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:
	USpriteRenderer* Renderer = nullptr;
	bool Revurse_X;
	float Offset_Angle;

};

