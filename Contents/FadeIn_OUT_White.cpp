#include "PreCompile.h"
#include "FadeIn_OUT_White.h"

AFadeIn_OUT_White::AFadeIn_OUT_White()
{
}

AFadeIn_OUT_White::~AFadeIn_OUT_White()
{
}

void AFadeIn_OUT_White::Init()
{
	SetMaterial("FadeINOUT_White");

	CopyTarget = UEngineRenderTarget::Create();
	// 내가 바라보는 애들을 모아서 그릴수 있는 랜더타겟을 만들고 싶어.
	float4 Scale = GEngine->EngineWindow.GetWindowScale();
	CopyTarget->CreateTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, Scale, float4::Zero);
	set = true;
}

void AFadeIn_OUT_White::Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget)
{
	CopyTarget->Copy(EffectTarget);
	EffectTarget->Clear();
	EffectTarget->Setting();
	Resources->SettingTexture("Image", CopyTarget->GetTexture(), "POINT");
	Render(0.0f);
}










