if "%~1"=="" goto usage
if "%~2"=="" goto usage
echo "%~1\GSChaos.dll"
echo "%~2\asi_plugins\GSChaos.asi"
echo f | xcopy "%~1\GSChaos.dll" "%~2\asi_plugins\GSChaos.asi" /Y
exit 0
:usage
echo Missing arguments
echo Usage: filecopy.bat BuildDirectory HalfLifeDirectory