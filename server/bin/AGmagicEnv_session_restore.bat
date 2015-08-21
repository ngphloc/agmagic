@echo off
if "%restore_path%" == "" goto end
set path=%restore_path%
echo %path%
:end
echo end