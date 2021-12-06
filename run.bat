@echo off

if "%1"=="" (
    echo too few arguments
    exit /b 1
)

if %1==all (
    for /d %%s in (day??) do (
        echo[
        cd %%~ns
        if "%2"=="c" (
            gcc %%~ns.c -o %%~ns.exe -I../
        )
        %%~ns
        cd ../
    )
) else (
    cd %1
    if "%2"=="c" (
        gcc %1.c -o %1.exe -I../
    )
    %1
    cd ../
)