#!/bin/bash

CLANG_FORMAT_BIN=${FAIRROOT_CLANG_FORMAT_BIN:-clang-format}

FILES=$(find . -type f \( -iname "*.h" ! -iname "*.pb.h" ! -iname "*LinkDef.h" -o -iname "*.hpp" -o -iname "*.cxx" -o -iname "*.cpp" -o -iname "*.c" -o -iname "*.C" \) -not \( -path "./build/*" -o -path "./cmake/*" -prune \))

$CLANG_FORMAT_BIN -i $FILES --verbose
