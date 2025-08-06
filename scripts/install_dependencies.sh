#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
VCPKG_DIR="${VCPKG_ROOT:-$ROOT_DIR/vcpkg}"

# Basic build tools if using apt
if command -v apt-get >/dev/null 2>&1; then
    sudo apt-get update
    sudo apt-get install -y build-essential cmake git curl
fi

if [ ! -d "$VCPKG_DIR" ]; then
    git clone https://github.com/microsoft/vcpkg.git "$VCPKG_DIR"
    "$VCPKG_DIR/bootstrap-vcpkg.sh"
fi

PACKAGES="glfw3 glm stb vulkan tinyobjloader joltphysics nlohmann-json"
"$VCPKG_DIR/vcpkg" install $PACKAGES

cat <<EOS

Dependencies installed using vcpkg. You can now build the project with:
    cmake -B build -S "$ROOT_DIR" -DCMAKE_TOOLCHAIN_FILE="$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake"
    cmake --build build
EOS

