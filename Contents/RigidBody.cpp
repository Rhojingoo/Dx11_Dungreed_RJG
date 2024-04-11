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

	//// �ӵ��� ���ӵ��� �����ش�.
	//mVelocity += mAccelation * _Deltatime;

	//if (_Setgravity == false)
	//{
	//	if (mbGround)
	//	{
	//		// ������ ������
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

	//// �߷°��ӵ� �ִ� �ӵ� ����
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
	//{// ������ ���� ( ����� ���� ����, �ӵ��� 0�� �ƴ�)
	//	if (!(mVelocity == FVector::Zero))
	//	{
	//		//�ӵ��� �ݴ�������� �������� ����ȴ�.
	//		FVector friction = -mVelocity;
	//		friction.Normalize();
	//		friction = friction * mFriction * mMass * _Deltatime;

	//		//���������� ���� �ӵ� ���Ҵ� ���� �ӵ����� ū ���

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

	//// �ӵ��� �°Բ� ��ü�� �̵���Ų��.
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