#pragma once
#include <EnginePlatform/EngineResources.h>

class UEngineBuffer
{
public : 
	UEngineBuffer();
	~UEngineBuffer();

	UEngineBuffer(const UEngineBuffer& _Other)				 = delete;
	UEngineBuffer(UEngineBuffer& _Other) noexcept				 = delete;
	UEngineBuffer& operator =(const UEngineBuffer& _Other)	 = delete;
	UEngineBuffer& operator =(UEngineBuffer& _Other) noexcept	 = delete;

protected:
	D3D11_BUFFER_DESC BufferInfo = {};
	ID3D11Buffer* Buffer = nullptr;

private:
};

