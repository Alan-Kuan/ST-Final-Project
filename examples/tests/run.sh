#!/bin/sh
[ "$#" -lt 1 ] && exit 1
LD_LIBRARY_PATH=../../build/test_execution ./$1
