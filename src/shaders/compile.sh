#!/bin/sh
set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
glslc "$DIR/shader.vert" -o "$DIR/vert.spv"
glslc "$DIR/shader.frag" -o "$DIR/frag.spv"
glslc "$DIR/shadow.vert" -o "$DIR/shadow_vert.spv"
glslc "$DIR/shadow.frag" -o "$DIR/shadow_frag.spv"
