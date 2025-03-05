set PROGRAM="..\cmake-build-debug\invert.exe"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem print help
%PROGRAM% "-h" > "%TEMP%\output.txt"
echo run first test
fc.exe "%TEMP%\output.txt" /test-data/test1/output.txt > nul
if ERRORLEVEL 1 goto err
echo first test ok

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
