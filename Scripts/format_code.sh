#!/bin/sh

find . -type f -name "*.cpp" -o -name "*.hpp" | while read file; do
    clang-format -i $file
done

