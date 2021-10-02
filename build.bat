@echo off

REM Required dependencies
set DEPENDENCIES=SDL2 GLEW
set SDL2_URL=https://www.libsdl.org/release/SDL2-devel-2.0.16-VC.zip
set GLEW_URL=https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download


:main
    if "%1" == "clean" (
        call :cleanup
        exit /b 0
    )
    
    echo [*] Running build script for windows...
    echo [*] Checking if dependenices are installed ...
    call :check_dependencies_are_installed

    exit /b 0



:check_dependencies_are_installed
    if exist external (
        echo [!] external directory found!
    ) else (
        echo [!] external directory not found!
        mkdir external
        call :download_dependency
    )
    exit /b 0


:download_dependency
    pushd external
        for %%x in (%DEPENDENCIES%) do (
            if not exist %%x (
                echo [!] %%x directory not found!
                echo [!] Creating %%x directory!
                mkdir %%x
                echo [*] Installing %%x ...

                REM TODO premission denied bullshit 
                call curl %%%%x_URL%% --output %%x

            ) else (
                echo [!] %%x folder found!
            )
        )
    popd
    exit /b 0


:cleanup 
    echo [*] Cleanup in progress ...
    if exist external (
        rd /s /q external
        echo [!] external directory deleted!
    )
    echo [!] Cleanup done!
    exit /b 0
