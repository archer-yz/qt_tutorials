@echo off
setlocal enabledelayedexpansion

REM Loop through each project and build
for /d %%p in (*) do (
    REM Skip Template
    if exist "%%p\CMakeLists.txt" (
        REM Skip Template project
        if /I NOT "%%p"=="Template" (
            echo Building %%p...

            REM run presets
            if exist "%%p\CMakePresets.json" (
                cd %%p
                cmake --preset vcpkg_release
                cd ..
            )

            REM Create build directory if it doesn't exist
            if not exist "%%p\build" mkdir "%%p\build"

            REM Navigate to build directory
            cd "%%p\build"

            REM Run CMake configuration
            cmake ..

            REM Build project
            cmake --build .

            REM Go back to the main directory
            cd ..\..

            echo Done with %%p!
        )
    )
)

echo All projects built successfully!
pause
