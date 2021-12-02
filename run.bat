@echo off

if "%1"=="" (
    echo too few arguments
    exit /b 1
)

cls

if %1==all (
    for /d %%s in (day??) do (
        cd %%~ns
        gcc %%~ns.c -o %%~ns.exe -Wpedantic -Wall -Werror -I../ && %%~ns
        cd ../
    )
) else (
    cd %1
    gcc %1.c -o %1.exe -Wpedantic -Wall -Werror -I../ && %1
    cd ../
)