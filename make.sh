#!/bin/bash

g++ -O3 delaunay.cxx memory_pool.cxx basic.cxx -o basic
g++ -O3 delaunay.cxx memory_pool.cxx incremental.cxx -o incremental
g++ -O3 delaunay.cxx memory_pool.cxx blocksize.cxx -o blocksize
