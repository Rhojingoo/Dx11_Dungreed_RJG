#pragma once
#include "SceneComponent.h"

// ���� :
class UCollision : public USceneComponent
{
public:
	// constrcuter destructer
	UCollision();
	~UCollision();

	// delete Function
	UCollision(const UCollision& _Other) = delete;
	UCollision(UCollision&& _Other) noexcept = delete;
	UCollision& operator=(const UCollision& _Other) = delete;
	UCollision& operator=(UCollision&& _Other) noexcept = delete;

	template<typename EnumType>
	bool IsCollisionGroup(EnumType _Index)
	{
		SetCollisionGroudp(static_cast<int>(_Index));
	}

	//void SetCollisionGroup(int _Index);
	

protected:

private:

};

