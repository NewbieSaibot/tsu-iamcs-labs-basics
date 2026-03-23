#!/usr/bin/bash
:"
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
gcc rev_original.c -o rev_original -O2 -Wall -Wextra"
gcc 4_sort_file.c -o 4_sort_file -O2 -Wall -Wextra
gcc list_test.c -o list_test -O2 -Wall -Wextra
gcc 6_list.c -o 6_list -O2 -Wall -Wextra
gcc 6_listi.c -o 6_listi -O2 -Wall -Wextra
gcc 7_rpn.c -o 7_rpn -O2 -Wall -Wextra
gcc 7_rpn_client.c -o 7_rpn_client -O2 -Wall -Wextra -lreadline
