#pragma once
#include <EngineCore/EngineRenderTarget.h>

class USpriteRenderer;
class AFadeIn_OUT : public UEffect
{
	GENERATED_BODY(UEffect)
public:
	AFadeIn_OUT();
	~AFadeIn_OUT();

	// delete Function
	AFadeIn_OUT(const AFadeIn_OUT& _Other) = delete;
	AFadeIn_OUT(AFadeIn_OUT&& _Other) noexcept = delete;
	AFadeIn_OUT& operator=(const AFadeIn_OUT& _Other) = delete;
	AFadeIn_OUT& operator=(AFadeIn_OUT&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;
	USpriteRenderer* Renderer = nullptr;

};

