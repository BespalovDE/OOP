@echo on

SET program="%~1"
set OUT="%TEMP%\out.txt"
if %program% == "" goto err

%program% >%OUT%
fc.exe %OUT% "%~dp0test\CONST\notcorrectpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1

%program% "0.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\notcorrectpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK2

%program% "%~dp0emptyINxt" "%~dp0emptyOutxt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\inputFileNotOpened.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% "%~dp0test\IN\in1.txt" "%~dp0test1xt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\outputFileNotOpened.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

%program% "%~dp0test\IN\in1.txt" "%~dp0test\OUT\out1.txt" >%OUT%
fc.exe "%~dp0test\OUT\out1.txt" "%~dp0test\CONST\out1.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK5

%program% "%~dp0test\IN\in2.txt" "%~dp0test\OUT\out2.txt" >%OUT%
fc.exe "%~dp0test\OUT\out2.txt" "%~dp0test\CONST\out2.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK6

%program% "%~dp0test\IN\inBigFill.txt" "%~dp0test\OUT\outBigFill.txt" >%OUT%
fc.exe "%~dp0test\OUT\outBigFill.txt" "%~dp0test\CONST\outBigFill.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK7

echo OK
exit /B

:testFailed
echo Testing failed
exit /B 1                                      

:err
echo Usage: test.bat <Path to program>
exit /B 1