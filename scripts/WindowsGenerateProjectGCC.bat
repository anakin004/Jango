@echo off
:: Move up one directory
pushd ..

:: Recurse through all subdirectories from the current (base) directory
for /r %%D in (*) do (
    if exist "%%D\Makefile" (
        echo Replacing Makefile in directory: %%D
        pushd "%%D"
        del Makefile
        popd
    )
)


echo Generating Makefiles in the base directory...
call vendor\bin\premake\premake5.exe gmake

:: Return to the original directory
popd
pause
