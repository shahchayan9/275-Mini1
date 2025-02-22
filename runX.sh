#!/bin/bash

mkdir -p build
cd build

x=${1:-10}
for ((i = 1; i <= x; i++)); do
    echo "Run #$i"
    rm -rf * >/dev/null 2>&1
    cmake .. >/dev/null 2>&1
    make >/dev/null 2>&1
    ./test
    echo ""
done