@echo on

SET program="%~1"
set OUT="%TEMP%\out.txt"
if %program% == "" goto err

%program% >%OUT%
fc.exe %OUT% "%~dp0notcorrectpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1

%program% "EmptySet.txt" >%OUT%
fc.exe %OUT% "%~dp0ResultEmptySet.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK2

%program% "Dictionary.txt" < "HelloWorld!.txt" >%OUT%
fc.exe %OUT% "%~dp0HelloWorldResult!.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% "Dictionary.txt" < "This.txt" >%OUT%
fc.exe %OUT% "%~dp0ThisN.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

%program% "Dictionary.txt" < "Input1.txt" >%OUT%
fc.exe %OUT% "%~dp0Output1.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK5

echo OK
exit /B

:testFailed
echo Testing failed
exit /B 1                                      

:err
echo Usage: test.bat <Path to program>
exit /B 1