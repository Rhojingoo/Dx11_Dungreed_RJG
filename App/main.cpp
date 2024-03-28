#include "PreCompile.h"

#include <Contents/GameCore.h>
// EnginePlatform에 존재하는 enginewindow기능을 당연히 이용하고 싶을 것이다.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UEngineCore::Start<UGameCore>(hInstance);
}