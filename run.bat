@echo off

if "%1"=="" (
    echo too few arguments
    exit /b 1
)

cls

if %1==all (
    for %%s in (day??.c) do (
        gcc %%~ns.c -o %%~ns.exe -Wpedantic -Wall -Werror && %%~ns
    )
) else (
    gcc %1.c -o %1.exe -Wpedantic -Wall -Werror && %1
)