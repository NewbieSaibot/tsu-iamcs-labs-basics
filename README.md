# TSU IAMCS Labs Basics
Solutions for my assigned problems, intended for studying C/C++ basics. It is recommended to ignore this repository unless you are staff of Tomsk State University

## Dependencies
`
gcc
`

## Building
```
chmod +x comp.sh
./comp.sh
```

## Task 1 - 13th problem

### Statement:
Given boolean vectors `a` and `b` of size `n`, compare them (in terms of discrete mathematics).

### Solution 1:
`s` and `t` are called equal when `s[i]` equals `t[i]` for each `i` in `1..n`;
`s` is less than `t` when for each `t[i]` that is `1` `s[i]` is either `1` or `0` (at least one `s[i]` is `0`) and for each `t[i]` that is `0` `s[i]` is `0`;
`s` and `t` are not incomparable when there exist such unique indices `i` and `j` where `s[i]` and `t[j]` are not equal.

### Solution 2:
Let's set `c = a & ~b` and `d = b & ~a`.
If `c` and `d` are equal to `0`, that means `a` and `b` have the same set bits;
if `c` is not `0` and `d` is `0`, that means `a` is greater than `b` and vice versa;
and finally if `c` and `d` are both not equal to `0`, that means they had such unique indices `i` and `j` where `a[i]` and `b[j]` are not equal to each other and thus `a` and `b` are incomparable.

### Files:

`13_slow.c` --- solution 1 with checking every single bit manually.

`13_fast.c` --- solution 2 with bitwise magic.

`13_bitset.c` --- solution 1 with bitset data structure.

`bitset.h` --- unfinished basic bitset implementation, intended to be used within the scope of the problem.

## Task 2 - 14th problem

### Statement:
Given boolean matrix of size `n` by `m`, sort the columns by their weight

### Input format
```
n m
A[1][1]A[1][2]...A[1][m]
A[2][1]A[2][2]...A[2][m]
... ... ... ...
A[n][1]A[n][2]...A[n][m]
```
### Output format
```
B[1][1]B[1][2]...B[1][m]
B[2][1]B[2][2]...B[2][m]
... ... ... ...
B[n][1]B[n][2]...B[n][m]
```
where `n` and `m` are height and width of the boolean matrix in integers `1 <= n, m <= 16` (`m` can be extended up to 128 with 128 bit unsigned integer type), `A[i][j]` is the `ij`th element of the matrix `0 <= A[i][j] <= 1`

### Solution 1
Let's count and swap each bit in every column when sorting. This solution doesn't need much to be explained.
Time complexity is `O(n * (m ^^ 2))`, can be improved with faster sorting algorithm up to `O(n * m * log m)` but it's a pain to write.

### Solution 2
Let's transpose the matrix, this allows us to quickly sort the rows in the transposed matrix and transpose it back. This sorting is equivalent to sorting used in solution 1. Time complexity is reduced by `O(n)` but introduces `O(n * m)` due to transposing, thus the time complexity overall is `O(n * m) + O(m * log m) + O(n * m) == O(n * m + m * log m)`.

### Files:

`14_slow.c` --- solution 1 with swapping each bit in columns when sorting.
`14_fast.c` --- solution 2 with transposing.

## Task 3 - 24th problem

### Statement:
Given a file and a key `k`, output encrypted file. Unless the character is Latin character, do not encrypt it, else set it to `c := (c + k) % 26 + 'a'`, where `c` is character and `a` is either lowercase `a` or uppercase `A` depending on `c`.

### Solution 1
The solution is fairly straightforward and does not need explaination. Time complexity is `O(n)`.

### Files:

`24.c` or `24_no_args.c` --- solution 1.

## Task 4 - 4th problem

### Statement:
Given file `f`, sort all its contents using natural merge sort.

### Solution 1
Under construction. Time complexity is `O(n log n)`.

### Files:
`4_sort_file.c` --- solution 1.

## Task 5.1 - 2nd problem

### Statement:
By generating an ascending array of random elements, find the indices of `a[i] == k`, where `k` is key using binary search.

### Solution 1
Let's implement lower bound and upper bound binary search functions that output the least and the greatest indices such `a[i] == k` accordingly. Time complexity is `O(log n)`.

### Files:
`5_search_2.c` --- solution 1.

## Task 5.2 - 4th problem

### Statement:
Using Boyre-Moore search algorithm, find the first indices of substrings that match the pattern.

### Solution 1
Let's randomize the string and put our pattern in it a few times. We can use the first indices just to color them. Let's use bad character heuristic for BM search. Worst case time complexity is `O(n * m)`.

### Solution 2
Since GNU/Linux's `grep` command uses Boyre-Moore search algorithm we can call it from our program to do the work for us. The code follows the Unix philosophy by working with other programs.

### Files:
`5_search_4.c` --- solution 1.
`5_search_4_grep.c` --- solution 2.

## Task 6 --- 12th problem

### Statement:
Given information of arbitrary students in a file and a group ID `i`, output last name of the best student that in group `i` that has the most `5` marks and no `2` marks.

### Solution 1
It's fairly straightforward. Time complexity is `O(n)`.

### Files:
`12_struct.c` --- solution 1.

## Task X - Reverse a file

### Solution 1
Let's create 2 temporary files `g1` and `g2` and follow the algorithm:
```
Read x from f into g1
Read all the elements from g1 to g2
Empty g1
Swap g1 and g2
Repeat until the last element of f
```
The destination file is either `g1` or `g2` depending on the parity of the number of elements in `f`. This solution demonstrates how files can be used as queue data structures (sort of).
Time complexity is `O(n^^2)`.

### Solution 2
Let's create `n` temporary files and put every `a[i]` element in `i`th temporary file, then traverse all the temporary files from the last one to add them in the destination file, thus we get a reversed file. Time complexity is `O(n)`.

### Files:

`rev_original.c` --- solution 1.
`rev.c` --- solution 2.

## Note
Trying to compile with MSVC or any other compiler that doesn't use `b` conversion specifier in scanf/printf will or may not work. GCC is strictly recommended
