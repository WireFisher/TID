#!/bin/bash

g++ -O3 -DPAT_BLOCK_DIM=$1 delaunay.cxx memory_pool.cxx blocksize.cxx -o blocksize
echo ================$1================
./blocksize &&
./blocksize &&
./blocksize &&
./blocksize &&
./blocksize
