@echo off 
for /f "tokens=* delims=" %%a in ('dir /b/s C:\Portfolio\Dx\GM\DX\DirectX\EngineBase\*.h') do copy /y "%%a" "C:\Portfolio\Dx\Dx_Game_RJG\EngineBase\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\Portfolio\Dx\GM\DX\DirectX\EngineCore\*.h') do copy /y "%%a" "C:\Portfolio\Dx\Dx_Game_RJG\EngineCore\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\Portfolio\Dx\GM\DX\DirectX\EnginePlatform\*.h') do copy /y "%%a" "C:\Portfolio\Dx\Dx_Game_RJG\EnginePlatform\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\Portfolio\Dx\GM\DX\DirectX\EngineShader\*.fx') do copy /y "%%a" "C:\Portfolio\Dx\Dx_Game_RJG\EngineShader\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\Portfolio\Dx\GM\DX\DirectX\EngineShader\*.hlsli') do copy /y "%%a" "C:\Portfolio\Dx\Dx_Game_RJG\EngineShader\"

for /f "tokens=* delims=" %%a in ('dir /b/s C:\Portfolio\Dx\GM\DX\DirectX\EngineBase\*.cpp') do copy /y "%%a" "C:\Portfolio\Dx\Dx_Game_RJG\EngineBase\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\Portfolio\Dx\GM\DX\DirectX\EngineCore\*.cpp') do copy /y "%%a" "C:\Portfolio\Dx\Dx_Game_RJG\EngineCore\"
for /f "tokens=* delims=" %%a in ('dir /b/s C:\Portfolio\Dx\GM\DX\DirectX\EnginePlatform\*.cpp') do copy /y "%%a" "C:\Portfolio\Dx\Dx_Game_RJG\EnginePlatform\"
