@echo on

SET program="%~1"
set OUT="%TEMP%\out.txt"
if %program% == "" goto err

%program% >%OUT%
fc.exe %OUT% "%~dp0notcorrectpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1

%program% "0.txt" >%OUT%
fc.exe %OUT% "%~dp0notcorrectpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK2

%program% "not" "%~dp0emptyIN.txt" "%~dp0emptyOut.txt" >%OUT%
fc.exe %OUT% "%~dp0notcorrectpackpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% "pack" "%~dp0input1.txt" "%~dp0output1.txt" >%OUT%
fc.exe "%~dp0resultOutput1.txt" "%~dp0output1.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

%program% "unpack" "%~dp0inputD1.txt" "%~dp0outputD1.txt" >%OUT%
fc.exe "%~dp0resultOutputD1.txt" "%~dp0outputD1.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK5

%program% "pack" "%~dp0inManyOneSim.txt" "%~dp0outManyOneSim.txt" >%OUT%
fc.exe "%~dp0ManyOneSim.txt" "%~dp0outManyOneSim.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK6

%program% "unpack" "%~dp0inManyOneSimD.txt" "%~dp0outManyOneSimD.txt" >%OUT%
fc.exe "%~dp0ManyOneSimD.txt" "%~dp0outManyOneSimD.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK7

%program% "pack" "%~dp0inputNumber.txt" "%~dp0emptyOut.txt" >%OUT%
fc.exe %OUT% "%~dp0hasnumber.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK8

%program% "unpack" "%~dp0inNotCorrectRLE1.txt" "%~dp0emptyOut.txt" >%OUT%
fc.exe %OUT% "%~dp0outNotCorRLE.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK9

%program% "unpack" "%~dp0inNotCorrectRLE2.txt" "%~dp0emptyOut.txt" >%OUT%
fc.exe %OUT% "%~dp0outNotCorRLE.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK10

%program% "pack" "%~dp0inMultyString.txt" "%~dp0outMultyString.txt" >%OUT%
fc.exe "%~dp0MultyString.txt" "%~dp0outMultyString.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK11

%program% "unpack" "%~dp0inMultyStringD.txt" "%~dp0outMultyStringD.txt" >%OUT%
fc.exe "%~dp0MultyStringD.txt" "%~dp0outMultyStringD.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK12

echo OK
exit /B

:testFailed
echo Testing failed
exit /B 1                                      

:err
echo Usage: test.bat <Path to program>
exit /B 1