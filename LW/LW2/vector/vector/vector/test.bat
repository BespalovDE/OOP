@echo on

SET program="%~1"
set OUT="%TEMP%\out.txt"
if %program% == "" goto err

%program% >%OUT%
fc.exe %OUT% "%~dp0test\CONST\notcorrectpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1

%program% "0.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\notOpenedFile.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK2

%program% "%~dp0test\IN\emptyIN.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\failedToReadingVector.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% "%~dp0test\IN\notCorrectIN.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\failedToReadingVector.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

%program% "%~dp0test\IN\IN.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\OUT.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK5

%program% "%~dp0test\IN\IN2.txt" >%OUT%
fc.exe %OUT% "%~dp0test\CONST\OUT2.txt" >nul
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