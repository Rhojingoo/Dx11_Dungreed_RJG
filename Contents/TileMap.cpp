#include "PreCompile.h"
#include "TileMap.h"
#include <EngineCore/TileRenderer.h>

ATileMap::ATileMap() 
{
	TileRenderer = CreateDefaultSubObject<UTileRenderer>("Renderer");
	SetRoot(TileRenderer);
	TileRenderer->SetOrder(ERenderOrder::TileMap); 
}

ATileMap::~ATileMap() 
{
}

