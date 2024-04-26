#include "PreCompile.h"
#include "FadeIn_OUT.h"


AFadeIn_OUT::AFadeIn_OUT()
{
	
}

AFadeIn_OUT::~AFadeIn_OUT()
{
}



void AFadeIn_OUT::Init()
{
	SetMaterial("FadeINOUT");

	CopyTarget = UEngineRenderTarget::Create();
	// ���� �ٶ󺸴� �ֵ��� ��Ƽ� �׸��� �ִ� ����Ÿ���� ����� �;�.
	float4 Scale = GEngine->EngineWindow.GetWindowScale();
	CopyTarget->CreateTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, Scale, float4::Zero);
}

void AFadeIn_OUT::Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget)
{
	CopyTarget->Copy(EffectTarget);
	EffectTarget->Clear();
	EffectTarget->Setting();

	Resources->SettingTexture("Image", CopyTarget->GetTexture(), "POINT");
	Render(0.0f);
}