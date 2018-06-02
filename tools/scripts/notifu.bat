REM *****************************************************************
REM show windows tool tip message
REM usage:
REM notifu.bat "message to display"
REM *****************************************************************
set type=info
if %ERRORLEVEL% NEQ 0 (
	set type=error
)

start %TOOLS_DIR%\notifu\notifu.exe /p "Patucel" /d 10500 /t %type% /m %1
