#!/bin/bash

mkdir -p build
cd build

for i in {1..10}; do
    echo "Run #$i"
    rm -rf * >/dev/null 2>&1
    cmake .. >/dev/null 2>&1
    make >/dev/null 2>&1
    ./test
    echo ""
done