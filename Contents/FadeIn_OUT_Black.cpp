#include "PreCompile.h"
#include "FadeIn_OUT_Black.h"


AFadeIn_OUT_Black::AFadeIn_OUT_Black()
{
	
}

AFadeIn_OUT_Black::~AFadeIn_OUT_Black()
{
	
}



void AFadeIn_OUT_Black::Init()
{
	SetMaterial("FadeINOUT_Black");

	CopyTarget = UEngineRenderTarget::Create();
	// ���� �ٶ󺸴� �ֵ��� ��Ƽ� �׸��� �ִ� ����Ÿ���� ����� �;�.
	float4 Scale = GEngine->EngineWindow.GetWindowScale();
	CopyTarget->CreateTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, Scale, float4::Zero);
	set = true;
}

void AFadeIn_OUT_Black::Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget)
{
	CopyTarget->Copy(EffectTarget);
	EffectTarget->Clear();
	EffectTarget->Setting();	
	Resources->SettingTexture("Image", CopyTarget->GetTexture(), "POINT");
	Render(0.0f);
}

