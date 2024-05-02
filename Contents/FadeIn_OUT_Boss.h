#pragma once
#include <EngineCore/EngineRenderTarget.h>

class USpriteRenderer;
class AFadeIn_OUT_Boss : public UEffect
{
	GENERATED_BODY(UEffect)
public:
	AFadeIn_OUT_Boss();
	~AFadeIn_OUT_Boss();

	// delete Function
	AFadeIn_OUT_Boss(const AFadeIn_OUT_Boss& _Other) = delete;
	AFadeIn_OUT_Boss(AFadeIn_OUT_Boss&& _Other) noexcept = delete;
	AFadeIn_OUT_Boss& operator=(const AFadeIn_OUT_Boss& _Other) = delete;
	AFadeIn_OUT_Boss& operator=(AFadeIn_OUT_Boss&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;
	USpriteRenderer* Renderer = nullptr;
	bool set = false;

};

