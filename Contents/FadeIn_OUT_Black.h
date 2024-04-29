#pragma once
#include <EngineCore/EngineRenderTarget.h>

class USpriteRenderer;
class AFadeIn_OUT_Black : public UEffect
{
	GENERATED_BODY(UEffect)
public:
	AFadeIn_OUT_Black();
	~AFadeIn_OUT_Black();

	// delete Function
	AFadeIn_OUT_Black(const AFadeIn_OUT_Black& _Other) = delete;
	AFadeIn_OUT_Black(AFadeIn_OUT_Black&& _Other) noexcept = delete;
	AFadeIn_OUT_Black& operator=(const AFadeIn_OUT_Black& _Other) = delete;
	AFadeIn_OUT_Black& operator=(AFadeIn_OUT_Black&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;
	USpriteRenderer* Renderer = nullptr;
	bool set = false;

};

