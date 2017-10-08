#!/usr/bin/env sh

# this program requires scan-build and clang.
# you can get scan-build with pip:
# pip3 install scan-build

# delete all object files so that make builds everything:
make clean

# run make through scan-build to generate a report:
scan-build --stats -o scan-build-reports make

