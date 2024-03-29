#pragma once
#include "SceneComponent.h"

class UDefaultSceneComponent : public USceneComponent
{
public : 
	UDefaultSceneComponent();
	~UDefaultSceneComponent();

	UDefaultSceneComponent(const UDefaultSceneComponent& _Other)				 = delete;
	UDefaultSceneComponent(UDefaultSceneComponent& _Other) noexcept				 = delete;
	UDefaultSceneComponent& operator =(const UDefaultSceneComponent& _Other)	 = delete;
	UDefaultSceneComponent& operator =(UDefaultSceneComponent& _Other) noexcept	 = delete;

protected:

private:
};

