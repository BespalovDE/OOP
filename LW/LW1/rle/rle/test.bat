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

%program% "not" "%~dp0test\IN\emptyIN.txt" "%~dp0test\OUT\emptyOut.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\notcorrectpackpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% "pack" "%~dp0test\IN\input1.txt" "%~dp0test\OUT\output1.txt" >%OUT%
fc.exe "%~dp0test\CONST\resultOutput1.txt" "%~dp0test\OUT\output1.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

%program% "unpack" "%~dp0test\IN\inputD1.txt" "%~dp0test\OUT\outputD1.txt" >%OUT%
fc.exe "%~dp0test\CONST\resultOutputD1.txt" "%~dp0test\OUT\outputD1.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK5

%program% "pack" "%~dp0test\IN\inManyOneSim.txt" "%~dp0test\OUT\outManyOneSim.txt" >%OUT%
fc.exe "%~dp0test\CONST\ManyOneSim.txt" "%~dp0test\OUT\outManyOneSim.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK6

%program% "unpack" "%~dp0test\IN\inManyOneSimD.txt" "%~dp0test\OUT\outManyOneSimD.txt" >%OUT%
fc.exe "%~dp0test\CONST\ManyOneSimD.txt" "%~dp0test\OUT\outManyOneSimD.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK7

%program% "pack" "%~dp0test\IN\inputNumber.txt" "%~dp0test\OUT\emptyOut.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\hasnumber.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK8

%program% "unpack" "%~dp0test\IN\inNotCorrectRLE1.txt" "%~dp0test\OUT\emptyOut.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\outNotCorRLE.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK9

%program% "unpack" "%~dp0test\IN\inNotCorrectRLE2.txt" "%~dp0test\OUT\emptyOut.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\outNotCorRLE.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK10

%program% "pack" "%~dp0test\IN\inMultyString.txt" "%~dp0test\OUT\outMultyString.txt" >%OUT%
fc.exe "%~dp0test\CONST\MultyString.txt" "%~dp0test\OUT\outMultyString.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK11

%program% "unpack" "%~dp0test\IN\inMultyStringD.txt" "%~dp0test\OUT\outMultyStringD.txt" >%OUT%
fc.exe "%~dp0test\CONST\MultyStringD.txt" "%~dp0test\OUT\outMultyStringD.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK12

%program% "pack" "%~dp0test\IN\inLimits.txt" "%~dp0test\OUT\outLimits.txt" >%OUT%
fc.exe "%~dp0test\CONST\outLimits.txt" "%~dp0test\OUT\outLimits.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK13

%program% "unpack" "%~dp0test\IN\inLimitsD.txt" "%~dp0test\OUT\outLimitsD.txt" >%OUT%
fc.exe "%~dp0test\CONST\outLimitsD.txt" "%~dp0test\OUT\outLimitsD.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK14

echo OK
exit /B

:testFailed
echo Testing failed
exit /B 1                                      

:err
echo Usage: test.bat <Path to program>
exit /B 1