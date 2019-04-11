#!/bin/bash

g++ -O3 -DPAT_EXPAND_RATIO=$1 delaunay.cxx memory_pool.cxx expand_ratio.cxx -o expand_ratio
echo ================$1================
#./expand_ratio &&
#./expand_ratio &&
#./expand_ratio &&
#./expand_ratio &&
./expand_ratio
