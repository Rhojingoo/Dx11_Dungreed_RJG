#include "PreCompile.h"
#include "RigidBody.h"
#include <EngineBase/EngineMath.h>

RigidBody::RigidBody()
	: mMass(1.f)
	, mForce(FVector::Zero)
	, mAccelation(FVector::Zero)
	, mVelocity(FVector::Zero)
{
	mLimitedVelocity.X = 200.0f;
	mLimitedVelocity.Y = 200.0f;
	mbGround = false;
	mGravity = FVector(0.0f, -800.0f);
	mFriction = 100.0f;
}
RigidBody::~RigidBody()
{
}


void RigidBody::Update(float _Deltatime)
{

	//// F = M * A
	//// A = M / F
	//mAccelation = mForce / mMass;

	//// 속도에 가속도를 더해준다.
	//mVelocity += mAccelation * _Deltatime;

	//if (_Setgravity == false)
	//{
	//	if (mbGround)
	//	{
	//		// 땅위에 있을때
	//		FVector gravity = mGravity;
	//		gravity.Normalize2D();

	//		float dot = mVelocity.DotProduct3D(gravity);
	//		mVelocity -= gravity * dot;
	//	}
	//	else
	//	{
	//		mVelocity += mGravity * _Deltatime;
	//	}
	//}

	//// 중력가속도 최대 속도 제한
	//FVector gravity = mGravity;
	//gravity.Normalize();
	//float dot = mVelocity.Dot(gravity);
	//gravity = gravity * dot;

	//FVector sideVelocity = mVelocity - gravity;
	//if (mLimitedVelocity.y < gravity.Length())
	//{
	//	gravity.Normalize();
	//	gravity *= mLimitedVelocity.y;
	//}

	//if (mLimitedVelocity.x < sideVelocity.Length())
	//{
	//	sideVelocity.Normalize();
	//	sideVelocity *= mLimitedVelocity.x;
	//}

	//if (_SetFriction == false)
	//{// 마찰력 조건 ( 적용된 힘이 없고, 속도가 0이 아님)
	//	if (!(mVelocity == FVector::Zero))
	//	{
	//		//속도에 반대방향으로 마찰력이 적용된다.
	//		FVector friction = -mVelocity;
	//		friction.Normalize();
	//		friction = friction * mFriction * mMass * _Deltatime;

	//		//마찰력으로 인한 속도 감소는 현재 속도보다 큰 경우

	//		if (mVelocity.Length() < friction.Length())
	//		{
	//			mVelocity = FVector::Zero;
	//		}
	//		else
	//		{
	//			mVelocity += friction;
	//		}
	//	}
	//}

	//// 속도에 맞게끔 물체를 이동시킨다.
	//Transform* tr = GetOwner()->GetComponent<Transform>();
	//FVector pos = tr->GetPositionXY();
	//pos = pos + mVelocity * _Deltatime;
	//tr->SetPositionXY(pos);
	//mForce = FVector(FVector::Zero);
}



void RigidBody::AddForce(FVector force)
{
	mForce += force;
}