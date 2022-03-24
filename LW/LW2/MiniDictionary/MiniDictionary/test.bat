@echo on

SET program="%~1"
set OUT="%TEMP%\out.txt"
if %program% == "" goto err

%program% >%OUT%
fc.exe %OUT% "%~dp0notcorrectpar.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1

%program% "d1.txt" < "....txt" < "y.txt" >%OUT%
fc.exe %OUT% "%~dp0newDictionaryWithOutWords.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
fc.exe "%~dp0d1.txt" "%~dp0EmptyDictionary.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK2



echo OK
exit /B

:testFailed
echo Testing failed
exit /B 1                                      

:err
echo Usage: test.bat <Path to program>
exit /B 1