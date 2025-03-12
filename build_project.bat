@echo off
setlocal enabledelayedexpansion

REM Check if an argument is provided
if "%1"=="" (
    echo Usage: build_project.bat [ProjectName]
    echo Example: build_project.bat ProjectA
    exit /b 1
)

set project=%1

REM Check if the specified project folder exists
if not exist "%project%\CMakeLists.txt" (
    echo Error: Project "%project%" does not exist!
    exit /b 1
)

if exist "%project%\CMakePresets.json" (
    cd %project%
    cmake --preset vcpkg_release
    cd ..
)

echo Building %project%...

REM Create build directory if it doesn't exist
if not exist "%project%\build" mkdir "%project%\build"

REM Navigate to build directory
cd "%project%\build"

REM Run CMake configuration
cmake ..

REM Build project
cmake --build .

REM Go back to the main directory
cd ..\..

echo Done with %project%!
pause
