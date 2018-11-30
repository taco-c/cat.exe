:: Because Windows doesn't have "make".

@echo off

set files=cat.c
set binfolder=bin
set exe=%binfolder%/cat.exe
set debugexe=%binfolder%/cat-debug.exe
set std=c89
set flags=-Werror -Wall -Wextra -pedantic

if not exist %binfolder% mkdir %binfolder%

if "%1"=="debug" (
	echo Compiling %debugexe%.
	gcc -o %debugexe% %files% %flags% -std=%std% -DDEBUG
) else (
	echo Compiling %exe%.
	gcc -o %exe% %files% %flags% -std=%std% -O3
)
