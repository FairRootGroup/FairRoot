#!/bin/bash

BASE_COMMIT=${FAIRROOT_FORMAT_BASE:-HEAD}
CLANG_FORMAT=${FAIRROOT_CLANG_FORMAT_BIN:-clang-format}
GIT_CLANG_FORMAT_BIN=${FAIRROOT_GIT_CLANG_FORMAT_BIN:-git-clang-format}

FILES=$(git diff --name-only $BASE_COMMIT | grep -E '*\.(h|hpp|c|C|cpp|cxx|tpl)$' | grep -viE '*LinkDef.h$')
# Include only files that exist
FILES=$(ls -1 $FILES 2>/dev/null)
RESULT=$($GIT_CLANG_FORMAT_BIN --commit $BASE_COMMIT --diff $FILES --extensions h,hpp,c,C,cpp,cxx,tpl)

$CLANG_FORMAT --version

if [ "$RESULT" == "no modified files to format" ] || [ "$RESULT" == "clang-format did not modify any files" ]; then
    echo "format check passed."
    exit 0
else
    echo "ERROR: format check failed. Suggested changes:"
    echo "$RESULT"
    exit 1
fi
