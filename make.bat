:: Because Windows doesn't have "make".

@echo off

:: if not exist %binfolder% mkdir %binfolder%

if "%1"=="debug" (
	mingw32-make debug
) else (
	mingw32-make
)
