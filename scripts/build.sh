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

cmake -B "$BUILD_DIR" -S "$ROOT_DIR" -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" "$@"
cmake --build "$BUILD_DIR"
