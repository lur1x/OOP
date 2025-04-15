echo off
set PROGRAM="..\..\cmake-build-debug\replace.exe"

if %PROGRAM%=="" (
	exit /B 1
)

echo #1 test: Not enough arguments in command line
%PROGRAM% test-data\test1\input.txt "%TEMP%\output.txt" 123 >nul
if NOT ERRORLEVEL goto err >nul
echo first test ok

echo #2 second test: Too many arguments on the command line
%PROGRAM% test-data\test2\input.txt "%TEMP%\output.txt" "%TEMP\output.txt%" 12 123 >nul
if NOT ERRORLEVEL goto err
echo second test ok

echo #3 third test: Non-existent input file
%PROGRAM% test-data\test3\input1.txt "%TEMP%\output.txt" 12 123
if NOT ERRORLEVEL goto err
echo third test ok

echo #4 fourth test: Incorrect output file
%PROGRAM% test-data\test4\input.txt replace.exe 12 123
if NOT ERRORLEVEL goto err
echo fourth test ok

echo #5 fifth test: Empty input file
%PROGRAM% test-data\test5\empty.txt "%TEMP%\output.txt" 12 123
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test5\empty_out.txt >nul
if ERRORLEVEL 1 goto err
echo fifth test ok

echo #6 sixth test: No replacement
%PROGRAM% test-data\test6\no-replacement.txt "%TEMP%\output.txt" 12 123
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test6\no-replacement_out.txt >nul
if ERRORLEVEL 1 goto err
echo sixth test ok

echo #7 seventh test: Empty search string
%PROGRAM% test-data\test7\empty-search-string.txt "%TEMP%\output.txt" "" 123
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test7\empty-search-string_out.txt > nul
if ERRORLEVEL 1 goto err
echo seventh test ok

echo #8 eighth test: Replacement for one line
%PROGRAM% test-data\test8\one-line.txt "%TEMP%\output.txt" cat dog
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test8\one-line_out.txt >nul
if ERRORLEVEL 1 goto err
echo eighth test ok

echo #9 ninth test: Replacement for multline lines
%PROGRAM% test-data\test9\multline.txt "%TEMP%\output.txt" cat dog
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test9\multline_out.txt >nul
if ERRORLEVEL 1 goto err
echo ninth test ok

echo #10 tenth test: Сyclicity check
%PROGRAM% test-data\test10\cyclicity.txt "%TEMP%\output.txt" ma mama
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test10\cyclicity_out.txt >nul
if ERRORLEVEL 1 goto err
echo tenth test ok

echo #11 eleventh test: Сheck line "12312312345"
%PROGRAM% test-data\test11\input.txt "%TEMP%\output.txt" 1231234 XYZ
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\test11\output.txt >nul
if ERRORLEVEL 1 goto err
echo eleventh test ok


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
