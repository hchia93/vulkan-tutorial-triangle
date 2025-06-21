@echo off
echo ========================================
echo Vulkan Tutorial Triangle - Environment Setup
echo ========================================
echo.

REM Check if vcpkg is installed
if not exist "%VCPKG_ROOT%\vcpkg.exe" (
    echo ERROR: vcpkg not found!
    echo Please install vcpkg and set VCPKG_ROOT environment variable.
    echo Visit: https://github.com/microsoft/vcpkg
    echo.
    pause
    exit /b 1
)

echo Found vcpkg at: %VCPKG_ROOT%
echo.

REM Check if CMake is available
cmake --version >nul 2>&1
if errorlevel 1 (
    echo ERROR: CMake not found!
    echo Please install CMake and add it to your PATH.
    echo Visit: https://cmake.org/download/
    echo.
    pause
    exit /b 1
)

echo Found CMake: 
cmake --version
echo.

REM Check if Visual Studio is available
where cl >nul 2>&1
if errorlevel 1 (
    echo WARNING: Visual Studio compiler not found in PATH.
    echo You may need to run this from a Visual Studio Developer Command Prompt.
    echo.
)

echo Environment setup completed successfully!
echo.
echo Next steps:
echo 1. Run GenerateVisualStudioSolution.bat to create the VS solution
echo 2. Open the generated .sln file in Visual Studio
echo 3. Build and run the project
echo.
pause 