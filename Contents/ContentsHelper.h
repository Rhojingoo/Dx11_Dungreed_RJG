#pragma once
#include <random>

class UContentsHelper
{
public:
	static const float TileSize;
	static std::shared_ptr<UEngineTexture> MapTex;
	static float4 MapTexScale;
	static int Random(int _min, int _max);
	static float Random(float _min, float _max);
};

