@echo off
echo Generating projects for BaseGame.
pushd %~dp0
set THIS_DIR=%CD%
popd
echo "%THIS_DIR%\project\scripts"
"project/bin/premake5.exe" --file="%THIS_DIR%\project\scripts\demo.lua" clean
"project/bin/premake5.exe" --file="%THIS_DIR%\project\scripts\demo.lua" vs2015