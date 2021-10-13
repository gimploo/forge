@echo off

REM Required dependencies
set DEPENDENCIES=SDL2 GLEW
set SDL2_URL=https://www.libsdl.org/release/SDL2-devel-2.0.16-VC.zip
set GLEW_URL=https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip


:main
    if "%1" == "clean" (
        echo [*] Cleanup in progress ...
        if exist external (
            rd /s /q external
            echo [!] external directory deleted!
        )
        echo [!] Cleanup done!
        exit /b 0
    )
    
    echo [*] Running build script for windows...
    echo [*] Checking if dependenices are installed ...

    if exist external (
        echo [!] external directory found!
    ) else (
        echo [!] external directory not found!
        mkdir external
    )

    echo [!] checking dependenices ...
    call :check_dependencies_are_installed

    exit /b 0



:check_dependencies_are_installed
    pushd external
        for %%x in (%DEPENDENCIES%) do (
            if not exist %%x (
                echo [!] %%x directory not found!
                call :download_dependency %%x

            ) else (
                echo [!] %%x folder found!
            )
        )
    popd
    exit /b 0


:download_dependency
    echo [*] Installing %~1 ...
    call echo [!] link: %%%~1_URL%%%
    call curl -L --output %~1.zip %%%~1_URL%%% 

    mkdir %~1
    tar -xf %~1.zip -C %~1 --strip-components 1
    del %~1.zip

    exit /b 0


:cleanup
    exit /b 0
