@echo off

set /p folderPath=ÎÄ¼þ¼ÐÂ·¾¶£º

cd %folderPath%

set mergeFile=merge.txt
rem set totalSize=0

for %%F in (*.txt) do (
    if not "%%F"=="merge.txt" (
        type "%%F" >> "%mergeFile%"
rem         set /a size=%%~zF
rem         set /a totalSize+=size
    )
)
rem echo Total size of all .txt files: %totalSize% bytes

rem for %%F in (*.txt) do (
rem     if "%%F"=="merge.txt" (
rem         echo The size of merge.txt: %%F, Size: %%~zF bytes
rem     )
rem )

pause