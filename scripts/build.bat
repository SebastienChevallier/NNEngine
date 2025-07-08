@echo off
setlocal enableextensions

set "ROOT_DIR=%~dp0.."
set "BUILD_DIR=%ROOT_DIR%\build"

if "%VCPKG_ROOT%"=="" (
    set "VCPKG_PATH=%ROOT_DIR%\vcpkg"
) else (
    set "VCPKG_PATH=%VCPKG_ROOT%"
)

set "TOOLCHAIN=%VCPKG_PATH%\scripts\buildsystems\vcpkg.cmake"

cmake -B "%BUILD_DIR%" -S "%ROOT_DIR%" -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN%" %*
cmake --build "%BUILD_DIR%"
