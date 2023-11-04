@echo off

set /p folderPath=文件夹路径：
cd %folderPath%

set mergeFile=merge.txt
set totalSize=0

for %%F in (*.txt) do (
    if not "%%F"=="merge.txt" (
        type "%%F" >> "%mergeFile%"
        set /a size=%%~zF
        set /a totalSize+=size
    )
)
echo Total size of all .txt files: %totalSize% bytes

for %%F in (*.txt) do (
    if "%%F"=="merge.txt" (
        echo The size of merge.txt: %%F, Size: %%~zF bytes
    )
)

pause
