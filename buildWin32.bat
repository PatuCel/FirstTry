@echo off

pushd tools\scripts\

set MODE=%1

if "%MODE%" == "" (
	set MODE="Debug"
) else if "%MODE%" == "Release" (
	set MODE="Release"
) else if "%MODE%" == "Debug" (
	set MODE="Debug"
) else (

	echo.
	echo * ERROR Choose One Correct Mode Release - Debug *	
	goto :end
)
call win_build.bat %MODE%

:end
echo.
popd

