@echo off

set TOOLS_SCRIPTS=%~dp0\

set ROOT_PATH=%~dp0\..\..\

set EXE_NAME=FirstTry.exe
set BM_EXE_NAME=bm_%EXE_NAME%

set WIN_PATH=%ROOT_PATH%build\Debug.win32\
set SOURCES_PATH=%ROOT_PATH%proj.win32\
set SLN_PATH=%SOURCES_PATH%FirstTry.sln
