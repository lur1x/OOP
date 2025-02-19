set PROGRAM="..\cmake-build-debug\replace.exe"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem Not enough arguments in command line
%PROGRAM% test1\input.txt "%TEMP%\output.txt" 123
echo run first test
if NOT ERRORLEVEL goto err
echo first test ok

rem Too many arguments on the command line
%PROGRAM% test2\input.txt "%TEMP%\output.txt" "%TEMP\output.txt%" 12 123
echo run second test
if NOT ERRORLEVEL goto err
echo second test ok

rem Non-existent input file
%PROGRAM% test3\input1.txt "%TEMP%\output.txt" 12 123
echo run third test
if NOT ERRORLEVEL goto err
echo third test ok

rem Incorrect output file
%PROGRAM% test4\input.txt replace.exe 12 123
echo run fourth test
if NOT ERRORLEVEL goto err
echo fourth test ok

rem Empty input file
%PROGRAM% test5\empty.txt "%TEMP%\output.txt" 12 123
echo run fifth test
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test5\empty_out.txt >nul
if ERRORLEVEL 1 goto err
echo fifth test ok

rem No replacement
%PROGRAM% test6\no-replacement.txt "%TEMP%\output.txt" 12 123
echo run sixth test
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test6\no-replacement_out.txt >nul
if ERRORLEVEL 1 goto err
echo sixth test ok

rem Empty search string
%PROGRAM% test7\empty-search-string.txt "%TEMP%\output.txt" "" 123
echo run seventh test
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test7\empty-search-string_out.txt >nul
if ERRORLEVEL 1 goto err
echo seventh test ok

rem Replacement for one line
%PROGRAM% test8\one-line.txt "%TEMP%\output.txt" cat dog
echo run eighth test
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test8\one-line_out.txt >nul
if ERRORLEVEL 1 goto err
echo eighth test ok

rem Replacement for multline lines
%PROGRAM% test9\multline.txt "%TEMP%\output.txt" cat dog
echo run ninth test
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test9\multline_out.txt >nul
if ERRORLEVEL 1 goto err
echo ninth test ok


rem Сyclicity check
%PROGRAM% test10\cyclicity.txt "%TEMP%\output.txt" ma mama
echo run tenth test
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test10\cyclicity_out.txt >nul
if ERRORLEVEL 1 goto err
echo tenth test ok


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
