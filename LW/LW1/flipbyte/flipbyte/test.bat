@echo on

SET program="%~1"
set OUT="%TEMP%\out.txt"
if %program% == "" goto err

%program% < "%~dp0Empty.txt" >%OUT%
fc.exe %OUT% "%~dp0notcorrectvalue.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1

%program% < "%~dp0A.txt" >%OUT%
fc.exe %OUT% "%~dp0notanumber.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK2

%program% < "%~dp0A7A.txt" >%OUT%
fc.exe %OUT% "%~dp0notanumber.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% < "%~dp0300.txt" >%OUT%
fc.exe %OUT% "%~dp0notabyte.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

%program% <  "%~dp06.txt" >%OUT% 
fc.exe %OUT% "%~dp096.txt" >nul
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