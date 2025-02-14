#!/bin/sh

taskset --cpu-list 2 ./binary_search_3 512 
taskset --cpu-list 2 ./binary_search_3 1024 
taskset --cpu-list 2 ./binary_search_3 2048 
taskset --cpu-list 2 ./binary_search_3 4096 
taskset --cpu-list 2 ./binary_search_3 8192 
taskset --cpu-list 2 ./binary_search_3 16384
taskset --cpu-list 2 ./binary_search_3 32768
taskset --cpu-list 2 ./binary_search_3 65536
taskset --cpu-list 2 ./binary_search_3 131072
taskset --cpu-list 2 ./binary_search_3 262144 
taskset --cpu-list 2 ./binary_search_3 524288 
taskset --cpu-list 2 ./binary_search_3 1048576 
taskset --cpu-list 2 ./binary_search_3 2097152 
taskset --cpu-list 2 ./binary_search_3 4194304
taskset --cpu-list 2 ./binary_search_3 8388608
taskset --cpu-list 2 ./binary_search_3 16777216

