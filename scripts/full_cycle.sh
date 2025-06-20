# full_cycle.sh
#!/bin/bash

set -e

SIZE=$1
BUILD_DIR=build

echo ">> removing old build directory"
rm -rf "$BUILD_DIR"

echo ">> configuring cmake with SIZE=$SIZE"
cmake -S . -B "$BUILD_DIR" -DSIZE="$SIZE"

echo ">> running benchmarks"
cmake --build "$BUILD_DIR" --target full_cycle
