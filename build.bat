@echo off
REM League of Legends Trainer - Build Script for Windows
REM This script builds the project using CMake

echo =============================================
echo League of Legends Trainer - Build Script
echo =============================================
echo.

REM Check if CMake is available
cmake --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: CMake is not installed or not in PATH
    echo Please install CMake 3.16 or later
    pause
    exit /b 1
)

REM Create build directory
if not exist build (
    echo Creating build directory...
    mkdir build
)

cd build

echo.
echo Configuring project with CMake...
echo.

REM Configure the project
cmake .. -G "Visual Studio 16 2019" -A x64
if errorlevel 1 (
    echo.
    echo ERROR: CMake configuration failed
    echo Trying with default generator...
    cmake ..
    if errorlevel 1 (
        echo ERROR: CMake configuration failed with default generator
        pause
        exit /b 1
    )
)

echo.
echo Building project (Release configuration)...
echo.

REM Build the project
cmake --build . --config Release
if errorlevel 1 (
    echo.
    echo ERROR: Build failed
    pause
    exit /b 1
)

echo.
echo =============================================
echo Build completed successfully!
echo =============================================
echo.
echo Executable location: build\bin\Release\lol-trainer.exe
echo.
echo To run the application:
echo   cd build\bin\Release
echo   lol-trainer.exe
echo.

pause