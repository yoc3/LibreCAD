call set-windows-env.bat

if exist "..\release\LibreCAD-Installer.exe" del "..\release\LibreCAD-Installer.exe"

cd postprocess-windows
%NSIS_DIR%\makensis.exe /X"SetCompressor /FINAL lzma" nsis-4.8.nsi
cd ..
