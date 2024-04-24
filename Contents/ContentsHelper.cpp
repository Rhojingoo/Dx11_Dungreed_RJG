#include "PreCompile.h"
#include "ContentsHelper.h"


const float UContentsHelper::TileSize = 64.0f;
std::shared_ptr<UEngineTexture> UContentsHelper::MapTex;
float4 UContentsHelper::MapTexScale;

int UContentsHelper::Random(int _min, int _max)
{	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(_min, _max);
	return dis(gen);	
}

float UContentsHelper::Random(float _min, float _max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(_min, _max);
	return dis(gen);
}
