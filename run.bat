@echo off

if "%1"=="" (
    echo too few arguments
    exit /b 1
)

if %1==all (
    for /d %%s in (day??) do (
        cd %%~ns
        gcc %%~ns.c -o %%~ns.exe -I../ && %%~ns
        echo[
        cd ../
    )
) else (
    cd %1
    gcc %1.c -o %1.exe -I../ && %1
    cd ../
)