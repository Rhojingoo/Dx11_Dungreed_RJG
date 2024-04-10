#include "PreCompile.h"

//#include "EngineShaderResources.h"
//#include "EngineSprite.h"
#include "Contents_SpriteRender.h"

Contents_SpriteRender::Contents_SpriteRender()
{
	Resources->SettingConstantBuffer("FCuttingData", CuttingDataValue);
}

Contents_SpriteRender::~Contents_SpriteRender()
{
}

void Contents_SpriteRender::Tick(float _DeltaTime)
{
	USpriteRenderer::Tick(_DeltaTime);
}
