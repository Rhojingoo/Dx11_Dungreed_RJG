#include "PreCompile.h"

#include <Contents/GameCore.h>
// EnginePlatform�� �����ϴ� enginewindow����� �翬�� �̿��ϰ� ���� ���̴�.

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UEngineCore::Start<UGameCore>(hInstance);
}