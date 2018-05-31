@echo off
::Read all Paths from _config.inf
::for /f "delims=" %%x in (_config.inf) do (set "%%x")

::Scripts dir
pushd tools\scripts\

:StartProgram
::variables


:Menu
title Space Ship X Menu
::
setlocal EnableDelayedExpansion
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do ( set "DEL=%%a" )

cls
call :color 0f "  ---------------------------------------------------------------------------------------------------------------" & echo.
call :color 0f "  |                                                    Game MENU                                                 |" & echo.
call :color 0f "  ---------------------------------------------------------------------------------------------------------------" & echo.
echo.
call :color 0a "  1.  [WIN32] " & echo Biuld Game (DEBUG)
call :color 0a "  2.  [WIN32] " & echo Biuld Game (Release)
call :color 0f "  ---------------------------------------------------------------------------------------------------------------" & echo.
call :color 0e "  3.  [ANDROID] " & echo Biuld Game (Debug)
call :color 0e "  4.  [ANDROID] " & echo Biuld Game (Release)
call :color 0f "  ---------------------------------------------------------------------------------------------------------------" & echo.
call :color 0b "  5.  [C-Creator] " & echo Fix Project Path
echo.
call :color 0f "  0.  Exit"
echo.
echo.

call :color 0c "  Please choose an option: "
set /p var= 

if %var%==(%1)==() goto Menu
if %var%==1 (
	call :BuildWin32 Debug
	call :result-success
)
if %var%==2 (
	call :BuildWin32 Release
	call :result-success
)
if %var%==3 (
    cls
	title Compiling Android [Debug]
    python cocos_compile.py debug
	call :result-success
)
if %var%==4 (
	cls
	title Compiling Android [Release]
	python cocos_compile.py release
	call :result-success
)
if %var%==5 (
    cls
	title Fix cocos creator project path
	call vbscript FixCocosProject
	call :result-success
)

if %var%==0 (popd & exit)
goto :Menu


:result-success
call :color 0e "Option was done, press enter to continue..."
Pause>Nul
goto :Menu


:result-fail
call :color 0c "Something went wrong, press enter to continue..."
Pause>Nul
goto :Menu


:BuildWin32
cls
title Compiling Win32 [%1]
::Validate VS PATH
if "%VS150COMONTOOLS%" == "" ( call vbscript MsgBox "Create VS150COMONTOOLS Enviromment Variable First!, Example: D:\Visual2017\Common7\Tools\" 16 "MSBuild Error" & goto:eof ) 
::Compile
call win_build.bat %1
goto:eof


:color
rem Prepare a file "X" with only one dot
<nul > X set /p ".=."

rem call :color %1 %2
rem exit /b

set "param=^%~2" !
set "param=!param:"=\"!"
findstr /p /A:%1 "." "!param!\..\X" nul
<nul set /p ".=%DEL%%DEL%%DEL%%DEL%%DEL%%DEL%%DEL%"
if exist X call del X
exit /b

:CompressPackage
set FILENAME=%1
if not exist project_w81\AppPackages (call _MakeGold MsgBox "Error could not create package." 16 "Package Error" & goto :eof)
call %ZIPPER% a %FILENAME% ".\project_w81\AppPackages\DH5_W8\*"
if exist onfinished.bat call onfinished "%cd%\%FILENAME%" %DATA_VERSION% 
if exist %FILENAME% call explorer /select,%FILENAME%
goto :eof

