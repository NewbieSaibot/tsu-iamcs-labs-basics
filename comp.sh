#!/usr/bin/bash

gcc 13_slow.c -o 13_slow -O2 -Wall -Wextra
gcc 13_fast.c -o 13_fast -O2 -Wall -Wextra
gcc 13_bitset.c -o 13_bitset -O2 -Wall -Wextra
gcc 14_slow.c -o 14_slow -O2 -Wall -Wextra
gcc 14_fast.c -o 14_fast -O2 -Wall -Wextra
gcc 24.c -o 24 -O2 -Wall -Wextra
gcc 24_no_args.c -o 24_no_args -O2 -Wall -Wextra
gcc 5_search_2.c -o 5_search_2 -O2 -Wall -Wextra
gcc 5_search_4.c -o 5_search_4 -O2 -Wall -Wextra
gcc 5_search_4_grep.c -o 5_search_4_grep -O2 -Wall -Wextra
gcc 5_sort.c -o 5_sort -O2 -Wall -Wextra
gcc 5_sort_no_args.c -o 5_sort_no_args -O2 -Wall -Wextra
gcc 12_struct.c -o 12_struct -O2 -Wall -Wextra
gcc fill_rand.c -o fill_rand -O2 -Wall -Wextra
gcc rev.c -o rev -O2 -Wall -Wextra
