#pragma once
#include <EngineBase/TransformObject.h>

class RigidBody : public UTransformObject
{
public:
	RigidBody();
	~RigidBody();

	// delete Function
	RigidBody(const RigidBody& _Other) = delete;
	RigidBody(RigidBody&& _Other) noexcept = delete;
	RigidBody& operator=(const RigidBody& _Other) = delete;
	RigidBody& operator=(RigidBody&& _Other) noexcept = delete;

	void Update(float _Deltatime);

protected:
	void AddForce(FVector force);
	void SetMass(float mass) { mMass = mass; }
	void SetGround(bool isGround) { mbGround = isGround; }
	bool GetGround() { return mbGround; }
	bool IsGround() { return mbGround; }


	FVector GetVelocity() { return mVelocity; }
	void SetVelocity(FVector velocity) { mVelocity = velocity; }
	void ClearVelocityX() { mVelocity.X = 0.f; }
	void ClearVelocityY() { mVelocity.Y = 0.f; }
	void ClearVelocity() { mVelocity = FVector(0.f, 0.f); }
	void SetGravity(bool set) { _Setgravity = set; }

private:
	float mMass;
	FVector mForce;
	FVector mAccelation;
	FVector mVelocity;
	FVector mLimitedVelocity;

	FVector mGravity;
	float mFriction;
	bool mbGround;
	bool _Setgravity = false;;

};

