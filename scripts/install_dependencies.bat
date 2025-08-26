@echo off
setlocal enableextensions

REM Directory of this script
set "ROOT_DIR=%~dp0.."

REM Use VCPKG_ROOT if set, otherwise default to ..\vcpkg
if defined VCPKG_ROOT (
    echo [INFO] Using VCPKG_ROOT: %VCPKG_ROOT%
    set "VCPKG_PATH=%VCPKG_ROOT%"
) else (
    echo [WARN] VCPKG_ROOT not defined, using default: %ROOT_DIR%\vcpkg
    set "VCPKG_PATH=%ROOT_DIR%\vcpkg"
)

REM Install vcpkg if missing
if not exist "%VCPKG_PATH%\vcpkg.exe" (
    echo [INFO] Cloning vcpkg...
    git clone https://github.com/microsoft/vcpkg "%VCPKG_PATH%"
    call "%VCPKG_PATH%\bootstrap-vcpkg.bat"
)

REM Install required packages
"%VCPKG_PATH%\vcpkg.exe" install glfw3 glm stb vulkan tinyobjloader joltphysics nlohmann-json imgui

echo Dependencies installed using vcpkg.
echo You can now build the project with:
echo     cmake -B build -S "%ROOT_DIR%" -DCMAKE_TOOLCHAIN_FILE="%VCPKG_PATH%\scripts\buildsystems\vcpkg.cmake"
echo     cmake --build build

pause
