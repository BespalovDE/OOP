@echo on

SET program="%~1"
set OUT="%TEMP%\out.txt"
if %program% == "" goto err

%program% >%OUT%
fc.exe %OUT% "%~dp0notcorrectpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1

%program% "cat" >%OUT%
fc.exe %OUT% "%~dp0notcorrectpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK2

%program% "text" "cat" >%OUT%
fc.exe %OUT% "%~dp0catResult.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% "Summer" "cat" >%OUT%
fc.exe %OUT% "%~dp0notFound.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

echo OK
exit /B

:testFailed
echo Testing failed
exit /B 1                                      

:err
echo Usage: test.bat <Path to program>
exit /B 1