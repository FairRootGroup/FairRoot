#! /bin/bash

set -e

workdir="$(mktemp -d --tmpdir fairsoft-for-fairroot.XXXXXX)"
cd "$workdir"
pwd

repo="https://github.com/FairRootGroup/FairSoft"
# repo="https://github.com/ChristianTackeGSI/FairSoft"
branch="$1"
install_name="dev"

git clone --branch "$branch" "$repo"
./FairSoft/legacy/setup-ubuntu.sh

mkdir build
cmake -DBUILD_METHOD=legacy \
      -DCMAKE_INSTALL_PREFIX="/opt/fairsoft/$install_name" \
      -S FairSoft -B build
cmake --build build -j20
cmake --install build

cd /tmp
rm -rf "$workdir"
