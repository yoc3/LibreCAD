@echo off

if "%Qt_DIR%"=="" goto SetEnv
if "%NSIS_DIR%"=="" goto SetEnv
goto Exit

:SetEnv
set Qt_DIR=C:\Qt\4.8.5
set NSIS_DIR=C:\Program Files (x86)\NSIS
set MINGW_DIR=C:\mingw

if exist custom-windows.bat call custom-windows.bat
set PATH=%MINGW_DIR%\bin;%Qt_DIR%\bin;%NSIS_DIR%\Bin;%PATH%

:Exit
echo on
