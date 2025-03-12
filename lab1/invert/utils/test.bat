@echo off
setlocal

set PROGRAM="..\cmake-build-debug\invert.exe"

if "%PROGRAM%"=="" (
    echo Error: PROGRAM variable is not set.
    exit /B 1
)

rem Создаем папку для тестов, если её нет
if not exist .\test mkdir .\test

rem 1. Обычная матрица
echo 1.0   2.0  3.0> .\test\input.txt
echo 0.0   1.0   4.0>> .\test\input.txt
echo 5.0   6.0   0.0>> .\test\input.txt
echo -24.000	18.000	5.000> .\test\expected.txt
echo 20.000	-15.000	-4.000>> .\test\expected.txt
echo -5.000	4.000	1.000>> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run first test
if ERRORLEVEL 1 (
    echo First test failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo First test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo first test ok

rem 2. Нет обратной матрицы
echo 1.0  2.0  3.0> .\test\input.txt
echo 4.0  5.0  6.0>> .\test\input.txt
echo 7.0  8.0  9.0>> .\test\input.txt
echo Non-invertible> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run second test
if ERRORLEVEL 1 (
    echo Second test failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Second test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo second test ok

rem 3. Единичная матрица
echo 1.0  0.0  0.0> .\test\input.txt
echo 0.0  1.0  0.0>> .\test\input.txt
echo 0.0  0.0  1.0>> .\test\input.txt
echo 1.000	0.000	0.000> .\test\expected.txt
echo 0.000	1.000	0.000>> .\test\expected.txt
echo 0.000	0.000	1.000>> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run third test
if ERRORLEVEL 1 (
    echo Third test failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Third test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo third test ok

rem 4. Матрица с нулями
echo 1.0  0.0  0.0> .\test\input.txt
echo 0.0  1.0  0.0>> .\test\input.txt
echo 0.0  0.0  1.0>> .\test\input.txt
echo 1.000	0.000	0.000> .\test\expected.txt
echo 0.000	1.000	0.000>> .\test\expected.txt
echo 0.000	0.000	1.000>> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run fourth test
if ERRORLEVEL 1 (
    echo Fourth test failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Fourth test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo fourth test ok

rem 5. Только нули
echo 0.0  0.0  0.0> .\test\input.txt
echo 0.0  0.0  0.0>> .\test\input.txt
echo 0.0  0.0  0.0>> .\test\input.txt
echo Non-invertible> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run fifth test
if ERRORLEVEL 1 (
    echo Fifth test failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Fifth test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo fifth test ok

rem 6. Матрица с отрицательными значениями
echo -1.0  -2.0  3.0> .\test\input.txt
echo 4.0   -5.0  6.0>> .\test\input.txt
echo -7.0   8.0  9.0>> .\test\input.txt
echo -0.387	0.175	0.013> .\test\expected.txt
echo -0.325	0.050	0.075>> .\test\expected.txt
echo -0.013	0.092	0.054>> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run sixth test
if ERRORLEVEL 1 (
    echo Sixth test failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Sixth test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo sixth test ok

rem 7. Некорректный ввод матрицы 3 на 3 в ширину
echo 1.0 2.0 3.0> .\test\input.txt
echo 4.0 5.0 6.0>> .\test\input.txt
echo 7.0 8.0>> .\test\input.txt
echo Invalid matrix> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run seventh test
if NOT ERRORLEVEL 0 (
    echo Seventh test failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Seventh test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo seventh test ok

rem 8. Некорректный ввод матрицы 3 на 3 в длину
echo 1.0 2.0 3.0> .\test\input.txt
echo 4.0 5.0 6.0>> .\test\input.txt
echo Invalid matrix format> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run eighth test
if NOT ERRORLEVEL 0 (
    echo Eighth test failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Eighth test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo eighth test ok

rem 9. Некорректный ввод матрицы 3 на 3, буква вместо цифры
echo 1.0 2.0 a> .\test\input.txt
echo 4.0 5.0 6.0>> .\test\input.txt
echo 7.0 8.0 3.0>> .\test\input.txt
echo Invalid matrix> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run ninth test
if NOT ERRORLEVEL 0 (
    echo Ninth test failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Ninth test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo ninth test ok

rem 10. float и int
echo 4.0   7.0   2.3> .\test\input.txt
echo 2.0   1.0   1.0>> .\test\input.txt
echo 3.0   -2.0  -2.31>> .\test\input.txt
echo -0.009	0.321	0.131> .\test\expected.txt
echo 0.212	-0.448	0.017>> .\test\expected.txt
echo -0.194	0.806	-0.278>> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run tenth test
if ERRORLEVEL 1 (
    echo Tenth test failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Tenth test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo tenth test ok

rem 11. Пустой входной файл
echo.> .\test\input.txt
echo Invalid matrix> .\test\expected.txt
%PROGRAM% .\test\input.txt > .\test\output.txt
echo run eleventh test
if NOT ERRORLEVEL 0 (
    echo Eleventh test failed: Program did not return an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Eleventh test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo eleventh test ok

rem 12. Ввод через stdin (обычная матрица)
echo 1.0   2.0   3.0> .\test\input.txt
echo 0.0   1.0   4.0>> .\test\input.txt
echo 5.0   6.0   0.0>> .\test\input.txt
echo -24.000	18.000	5.000> .\test\expected.txt
echo 20.000	-15.000	-4.000>> .\test\expected.txt
echo -5.000	4.000	1.000>> .\test\expected.txt
type .\test\input.txt | %PROGRAM% > .\test\output.txt
echo run twelfth test
if ERRORLEVEL 1 (
    echo Twelfth test failed: Program returned an error.
    goto err
)
fc.exe .\test\output.txt .\test\expected.txt >nul
if ERRORLEVEL 1 (
    echo Twelfth test failed: Output does not match expected.
    echo Expected output:
    type .\test\expected.txt
    echo Actual output:
    type .\test\output.txt
    goto err
)
echo twelfth test ok

rem Остальные тесты через stdin...

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1