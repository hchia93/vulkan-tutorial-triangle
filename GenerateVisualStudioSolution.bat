@echo off
echo ========================================
echo Generating Visual Studio Solution
echo ========================================
echo.

REM Check if build directory exists, if not create it
if not exist "generated-vs" (
    echo Creating generated-vs directory...
    mkdir generated-vs
)

REM Change to build directory
cd generated-vs

REM Configure the project with CMake
echo Configuring project with CMake...
cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake" -G "Visual Studio 17 2022" -A x64

if errorlevel 1 (
    echo ERROR: CMake configuration failed!
    echo.
    echo Troubleshooting tips:
    echo 1. Make sure you have Visual Studio 2022 installed
    echo 2. Make sure vcpkg is properly installed and VCPKG_ROOT is set
    echo 3. Try running SetupEnvironment.bat first
    echo.
    pause
    exit /b 1
)

echo.
echo ========================================
echo Solution generated successfully!
echo ========================================
echo.
echo The Visual Studio solution has been created in the 'generated-vs' directory.
echo You can now:
echo 1. Open 'generated-vs/vulkan-tutorial-triangle.sln' in Visual Studio
echo 2. Build the project (Ctrl+Shift+B)
echo 3. Run the project (F5)
echo.
echo Note: The first build may take longer as vcpkg downloads dependencies.
echo.

REM Go back to project root
cd ..

pause 