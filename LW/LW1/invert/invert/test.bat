@echo on

SET program="%~1"
set OUT="%TEMP%\out.txt"
if %program% == "" goto err

%program% >%OUT%
fc.exe %OUT% "%~dp0NotParams.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1

%program% "0.txt" >%OUT%
fc.exe %OUT% "%~dp0Failed.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK2

%program% "%~dp0Empty.txt" >%OUT%
fc.exe %OUT% "%~dp0NotCorrect.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% "%~dp0inputNotCorrect.txt" >%OUT%
fc.exe %OUT% "%~dp0NotCorrect.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

%program% "%~dp0matrix2.txt" >%OUT%
fc.exe %OUT% "%~dp0ExprMatrix.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK5

%program% "%~dp0matrix.txt" >%OUT%
fc.exe %OUT% "%~dp0result1.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK6

echo OK
exit /B

:testFailed
echo Testing failed
exit /B 1                                      

:err
echo Usage: test.bat <Path to program>
exit /B 1