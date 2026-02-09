# TSU IAMCS Labs Basics
Solutions for my assigned problems, intended for studying C/C++ basics. It is recommended to ignore this repository unless you are staff of Tomsk State University

## Dependencies
`
gcc
`

## Building
`
chmod +x comp.sh

./comp.sh
`

## Task 1 - 13th problem

### Statement:
Given boolean vectors `a` and `b` of size `n`, compare them (in terms of discrete mathematics).

### Solution 1:
`s` and `t` are called equal when `s_i` equals `t_i` for each `i` in `1..n`;
`s` is less than `t` when for each `t_i` that is `1` `s_i` is either `1` or `0` (at least one `s_i` is `0`) and for each `t_i` that is `0` `s_i` is `0`;
`s` and `t` are not incomparable when there exist such unique indices `i` and `j` where `s_i` and `t_j` are not equal.

Such solution is used in `13_slow.c` and `13_bitset.c`.

### Solution 2:
Let's set `c = a & ~b` and `d = b & ~a`.
If `c` and `d` are equal to `0`, that means `a` and `b` have the same set bits;
if `c` is not `0` and `d` is `0`, that means `a` is greater than `b` and vice versa;
and finally if `c` and `d` are both not equal to `0`, that means they had such unique indices `i` and `j` where `a_i` and `b_j` are not equal to each other and thus `a` and `b` are incomparable.

### Files:

`13_slow.c` --- solution 1 with checking every single bit manually.

`13_fast.c` --- solution 2 with bitwise magic.

`13_bitset.c` --- solution 1 with bitset data structure.

`bitset.h` --- unfinished basic bitset implementation, intended to be used within the scope of the problem.

## Task 2 - 14th problem

### Statement:
Given boolean matrix of size `n` by `m`, sort the columns by their weight

### Input format
`
n m

A_11A_12...A_1m

A_21A_22...A_2m

... ... ... ...

A_n1A_n2...A_nm
`
### Output format
`
B_11B_12...B_1m

B_21B_22...B_2m

... ... ... ...

B_n1B_n2...B_nm
`
where `n` and `m` are height and width of the boolean matrix in integers `1 <= n, m <= 16` (`m` can be extended up to 128 with 128 bit unsigned integer type), `A_ij` is the `ij`th element of the matrix `0 <= A_ij <= 1`


### Solution 1
Let's count and swap each bit in every column when sorting. This solution doesn't need much to be explained.
Time complexity is `O(n * (m ^^ 2))`, can be improved with faster sorting algorithm up to `O(n * m * log m)` but it's a pain to write.

### Solution 2
Let's transpose the matrix, this allows us to quickly sort the rows in the transposed matrix and transpose it back. This sorting is equivalent to sorting used in solution 1. Time complexity is reduced by `O(n)` but introduces `O(n * m)` due to transposing, thus the time complexity overall is `O(n * m) + O(m * log m) + O(n * m) == O(n * m + m * log m)`.

### Files:

`14_slow.c` --- solution 1 with swapping each bit in columns when sorting.

`14_fast.c` --- solution 2 with transposing.

## Note
Trying to compile with MSVC or any other compiler that doesn't use `b` conversion specifier in scanf/printf will or may not work. GCC is strictly recommended
