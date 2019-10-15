#!/bin/bash -e
WHERE=$(dirname $0)
WHERE=$(readlink -f ${WHERE})

rm -rf ${WHERE}/build
mkdir -p ${WHERE}/build
cd ${WHERE}/build

cmake -GNinja ..
ninja
./*.exe

