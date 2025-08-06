#!/bin/sh
set -e

# Directory of this script
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="${BUILD_DIR:-$ROOT_DIR/build}"

mkdir -p "$BUILD_DIR"

# Use VCPKG_ROOT if set, otherwise assume ../vcpkg relative to repository root
VCPKG_PATH="${VCPKG_ROOT:-$ROOT_DIR/vcpkg}"
TOOLCHAIN_FILE="$VCPKG_PATH/scripts/buildsystems/vcpkg.cmake"
CMAKE_TOOLCHAIN_ARG=""
if [ -f "$TOOLCHAIN_FILE" ]; then
    CMAKE_TOOLCHAIN_ARG="-DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE"
else
    echo "Warning: vcpkg toolchain file not found at $TOOLCHAIN_FILE, proceeding without it."
    CMAKE_TOOLCHAIN_ARG="-DCMAKE_TOOLCHAIN_FILE="
fi

# Choose an appropriate CMake generator depending on the platform. On Windows
# we keep using Visual Studio while on other systems we rely on CMake's default
# generator (typically Unix Makefiles or Ninja).
GENERATOR=""
case "$(uname -s)" in
    MINGW*|MSYS*|CYGWIN*|Windows_NT)
        GENERATOR="Visual Studio 17 2022"
        ;;
    *)
        ;;
esac

# Configure and build the project
if [ -n "$GENERATOR" ]; then
    cmake -B "$BUILD_DIR" -S "$ROOT_DIR" -G "$GENERATOR" $CMAKE_TOOLCHAIN_ARG "$@"
else
    cmake -B "$BUILD_DIR" -S "$ROOT_DIR" $CMAKE_TOOLCHAIN_ARG "$@"
fi
cmake --build "$BUILD_DIR"

# Run tests if they were generated
if command -v ctest >/dev/null 2>&1; then
    ctest --test-dir "$BUILD_DIR" --output-on-failure
fi
