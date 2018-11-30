:: Because Windows doesn't have "make".

@echo off
set files=cat.c
set exe=cat.exe
set debugexe=cat-debug.exe
set std=c89
set flags=-Werror -Wall -Wextra -pedantic

:: if "%1"=="" ()

echo Compiling debug-exe.
gcc -o %debugexe% %files% %flags% -std=%std% -DDEBUG

echo Compiling normal-exe.
gcc -o %exe% %files% %flags% -std=%std% -O3
