#pragma once
#include <EngineCore/EngineRenderTarget.h>

class USpriteRenderer;
class AFadeIn_OUT_White : public UEffect
{
	GENERATED_BODY(UEffect)
public:
	AFadeIn_OUT_White();
	~AFadeIn_OUT_White();

	// delete Function
	AFadeIn_OUT_White(const AFadeIn_OUT_White& _Other) = delete;
	AFadeIn_OUT_White(AFadeIn_OUT_White&& _Other) noexcept = delete;
	AFadeIn_OUT_White& operator=(const AFadeIn_OUT_White& _Other) = delete;
	AFadeIn_OUT_White& operator=(AFadeIn_OUT_White&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;
	USpriteRenderer* Renderer = nullptr;
	bool set = false;
};

