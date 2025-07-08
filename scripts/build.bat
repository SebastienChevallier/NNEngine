@echo off
setlocal enableextensions

set "ROOT_DIR=%~dp0.."
set "BUILD_DIR=%ROOT_DIR%\build"

REM V�rifie si VCPKG_ROOT est d�fini, sinon utilise un chemin par d�faut
if defined VCPKG_ROOT (
    echo [INFO] Utilisation de VCPKG_ROOT : %VCPKG_ROOT%
    set "VCPKG_PATH=%VCPKG_ROOT%"
) else (
    echo [WARN] VCPKG_ROOT non defini, utilisation du dossier par defaut: %ROOT_DIR%\vcpkg
    set "VCPKG_PATH=%ROOT_DIR%\vcpkg"
)

set "TOOLCHAIN=%VCPKG_PATH%\scripts\buildsystems\vcpkg.cmake"

REM V�rifier existence vcpkg.cmake
if not exist "%TOOLCHAIN%" (
    echo [ERREUR] vcpkg.cmake introuvable a l'emplacement "%TOOLCHAIN%"
    echo Verifie ton installation de vcpkg ou ta variable VCPKG_ROOT.
    pause
    exit /b 1
)

REM Supprimer build pr�c�dent pour un build propre
if exist "%BUILD_DIR%" (
    echo [INFO] Suppression de l'ancien dossier build...
    rmdir /s /q "%BUILD_DIR%"
)

mkdir "%BUILD_DIR%"

echo [INFO] Generation de la solution Visual Studio...
cmake -B "%BUILD_DIR%" -S "%ROOT_DIR%" -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN%" %*

echo [INFO] Construction du projet...
cmake --build "%BUILD_DIR%"

pause
