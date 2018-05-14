@echo off

pushd tools\scripts\

if "%VS150COMONTOOLS%" == "" (
	echo
	echo *Crate VS150COMONTOOLS Enviromment Variable First! ,Example: D:\Visual2017\Common7\Tools\"
	goto :end
)

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

