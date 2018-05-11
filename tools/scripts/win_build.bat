@echo off

call common_config.bat

call "%VS150COMONTOOLS%VsDevCmd.bat"
msbuild /maxcpucount /verbosity:minimal /p:Configuration=%MODE% %SLN_PATH%

echo.
if %ERRORLEVEL% EQU 0 (
	echo copying: %BM_EXE_NAME%
	copy /Y %WIN_PATH%%EXE_NAME% %WIN_PATH%%BM_EXE_NAME%
) else (
	echo.
	echo * BUILD FAILED *
	goto :end
)
:end
echo.

pause