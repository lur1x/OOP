@echo off
setlocal

set PROGRAM="..\cmake-build-debug\radix.exe"

if "%PROGRAM%"=="" (
    echo Error: PROGRAM variable is not set.
    exit /B 1
)

rem Create a folder for tests if it doesn't exist
if not exist .\test mkdir .\test

rem 1. Normal conversion
echo 31> .\test\expected.txt
%PROGRAM% 16 10 1F > .\test\output.txt
echo Running test 1
if ERRORLEVEL 1 (
    echo Test 1 failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 1 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 1 passed

rem 2. Reverse conversion
echo 1F> .\test\expected.txt
%PROGRAM% 10 16 31 > .\test\output.txt
echo Running test 2
if ERRORLEVEL 1 (
    echo Test 2 failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 2 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 2 passed

rem 3. Convert to binary
echo 1010> .\test\expected.txt
%PROGRAM% 10 2 10 > .\test\output.txt
echo Running test 3
if ERRORLEVEL 1 (
    echo Test 3 failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 3 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 3 passed

rem 4. Convert from binary
echo F> .\test\expected.txt
%PROGRAM% 2 16 1111 > .\test\output.txt
echo Running test 4
if ERRORLEVEL 1 (
    echo Test 4 failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 4 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 4 passed

rem 5. Negative number
echo -2A> .\test\expected.txt
%PROGRAM% 10 16 -42 > .\test\output.txt
echo Running test 5
if ERRORLEVEL 1 (
    echo Test 5 failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 5 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 5 passed

rem 6. Zero
echo 0 > .\test\expected.txt
%PROGRAM% 10 2 0 > .\test\output.txt
echo Running test 6
if ERRORLEVEL 1 (
    echo Test 6 failed: Program returned an error.
    goto err
)

rem Use findstr to compare strings
findstr /x /c:"0" .\test\output.txt >nul
if ERRORLEVEL 1 (
    echo Test 6 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 6 passed

rem 7. Source radix greater than 36
echo Invalid radix> .\test\expected.txt
%PROGRAM% 37 10 123 2>&1 > .\test\output.txt
echo Running test 7
if NOT ERRORLEVEL 1 (
    echo Test 7 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 7 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 7 passed

rem 8. Destination radix greater than 36
echo Invalid radix> .\test\expected.txt
%PROGRAM% 10 37 12 2>&1 > .\test\output.txt
echo Running test 8
if NOT ERRORLEVEL 1 (
    echo Test 8 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 8 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 8 passed

rem 9. Source radix less than 2
echo Invalid radix> .\test\expected.txt
%PROGRAM% 1 10 1 2>&1 > .\test\output.txt
echo Running test 9
if NOT ERRORLEVEL 1 (
    echo Test 9 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 9 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 9 passed

rem 10. Destination radix less than 2
echo Invalid radix> .\test\expected.txt
%PROGRAM% 10 1 1 2>&1 > .\test\output.txt
echo Running test 10
if NOT ERRORLEVEL 1 (
    echo Test 10 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 10 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 10 passed

rem 11. Number does not match the radix
echo Invalid digit> .\test\expected.txt
%PROGRAM% 10 2 AB 2>&1 > .\test\output.txt
echo Running test 11
if NOT ERRORLEVEL 1 (
    echo Test 11 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 11 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 11 passed

rem 12. Missing one argument
echo Invalid arguments> .\test\expected.txt
%PROGRAM% 10 2 2>&1 > .\test\output.txt
echo Running test 12
if NOT ERRORLEVEL 1 (
    echo Test 12 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 12 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 12 passed

rem 13. Missing two arguments
echo Invalid arguments> .\test\expected.txt
%PROGRAM% 10 2>&1 > .\test\output.txt
echo Running test 13
if NOT ERRORLEVEL 1 (
    echo Test 13 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 13 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 13 passed

rem 14. Missing all arguments
echo Invalid arguments> .\test\expected.txt
%PROGRAM% 2>&1 > .\test\output.txt
echo Running test 14
if NOT ERRORLEVEL 1 (
    echo Test 14 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 14 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 14 passed

rem 15. Maximum value
echo 7FFFFFFF> .\test\expected.txt
%PROGRAM% 10 16 2147483647 > .\test\output.txt
echo Running test 15
if ERRORLEVEL 1 (
    echo Test 15 failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 15 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 15 passed

rem 16. Overflow
echo Overflow> .\test\expected.txt
%PROGRAM% 10 16 2147483648 2>&1 > .\test\output.txt
echo Running test 16
if NOT ERRORLEVEL 1 (
    echo Test 16 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 16 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 16 passed

rem 17. All maximum values
echo Overflow> .\test\expected.txt
%PROGRAM% 36 36 2147483647 2>&1 > .\test\output.txt
echo Running test 17
if NOT ERRORLEVEL 1 (
    echo Test 17 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 17 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 17 passed

rem 18. One less than maximum value
echo 7FFFFFFE> .\test\expected.txt
%PROGRAM% 10 16 2147483646 > .\test\output.txt
echo Running test 18
if ERRORLEVEL 1 (
    echo Test 18 failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 18 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 18 passed

rem 19. Minimum value
echo -7FFFFFFF> .\test\expected.txt
%PROGRAM% 10 16 -2147483647 > .\test\output.txt
echo Running test 19
if ERRORLEVEL 1 (
    echo Test 19 failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 19 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 19 passed

rem 20. Minimum value - 1
echo Overflow> .\test\expected.txt
%PROGRAM% 10 16 -2147483648 2>&1 > .\test\output.txt
echo Running test 20
if NOT ERRORLEVEL 1 (
    echo Test 20 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 20 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 20 passed

rem 21. Minimum value + 1
echo -7FFFFFFE> .\test\expected.txt
%PROGRAM% 10 16 -2147483646 > .\test\output.txt
echo Running test 21
if ERRORLEVEL 1 (
    echo Test 21 failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 21 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 21 passed

rem 22. Letters as radix
echo Invalid digit> .\test\expected.txt
%PROGRAM% A B 123 2>&1 > .\test\output.txt
echo Running test 22
if NOT ERRORLEVEL 1 (
    echo Test 22 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 22 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 22 passed

rem 23. Letter as source radix
echo Invalid digit> .\test\expected.txt
%PROGRAM% A 16 123 2>&1 > .\test\output.txt
echo Running test 23
if NOT ERRORLEVEL 1 (
    echo Test 23 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 23 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 23 passed

rem 24. Letter as destination radix
echo Invalid digit> .\test\expected.txt
%PROGRAM% 10 A 123 2>&1 > .\test\output.txt
echo Running test 24
if NOT ERRORLEVEL 1 (
    echo Test 24 failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Test 24 failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo Test 24 passed

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1