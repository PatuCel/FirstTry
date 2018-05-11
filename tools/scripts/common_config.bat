@echo off

set TOOLS_SCRIPTS=%~dp0\

set ROOT_PATH=%~dp0\..\..\

set EXE_NAME=FirstTry.exe
set BM_EXE_NAME=bm_%EXE_NAME%

set WIN_PATH=%ROOT_PATH%Projects\Win32\Debug.win32\
set SOURCES_PATH=%ROOT_PATH%\Projects\Win32\
set SLN_PATH=%SOURCES_PATH%FirstTry.sln
set WIN_SAVE_PATH=%WIN_PATH%user
