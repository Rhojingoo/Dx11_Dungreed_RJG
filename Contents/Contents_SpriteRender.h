#pragma once
#include <enginecore/SpriteRenderer.h>
//"EnSpriteRenderer.h"

class Contents_SpriteRender : public USpriteRenderer
{
public:
	Contents_SpriteRender();
	~Contents_SpriteRender();

	Contents_SpriteRender(const Contents_SpriteRender& _Other)						= delete;
	Contents_SpriteRender(Contents_SpriteRender& _Other) noexcept					= delete;
	Contents_SpriteRender& operator =(const 	Contents_SpriteRender& _Other)		= delete;
	Contents_SpriteRender& operator =(Contents_SpriteRender& _Other)noexcept		= delete;

protected:
	void Tick(float _DeltaTime) override;

private:
	//FCuttingData CuttingDataValue;
	float4 MOVEUV = float4::Zero;
};

