@echo on

SET program="%~1"
set OUT="%TEMP%\out.txt"
if %program% == "" goto err

%program% >%OUT%
fc.exe %OUT% "%~dp0noparams.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1

%program% Hello >%OUT% 
fc.exe %OUT% "%~dp0noparams.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK2

%program% "%~dp0t1.txt" >%OUT%
fc.exe %OUT% "%~dp0noparams.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% Hello hello >%OUT%
fc.exe %OUT% "%~dp0notexists.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

%program% "%~dp0t1.txt" virtal >%OUT% 
fc.exe %OUT% "%~dp0notfound.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK5

%program% "%~dp0t1.txt" hello >%OUT%
IF ERRORLEVEL 1 goto testFailed
fc.exe %OUT% "%~dp0result.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK6

%program% "%~dp0t2.txt" ivent >%OUT%
IF ERRORLEVEL 1 goto testFailed
fc.exe %OUT% "%~dp0ivent.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK7

%program% "%~dp0t3.txt" lost >%OUT%
IF ERRORLEVEL 1 goto testFailed
fc.exe %OUT% "%~dp0lost.txt" >nul
IF ERRORLEVEL 1 goto :testFailed

echo OK
exit /B

:testFailed
echo Testing failed
exit /B 1                                      

:err
echo Usage: test.bat <Path to program>
exit /B 1