#ifdef BITSET_IMPL

#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
	size_t size;
	size_t real_size;
	unsigned long long* data;
} Bitset;

void BitsetInit(Bitset *bs, size_t size) {
	bs->size = size;
	bs->real_size = (size + 63) / 64;
	bs->data = (unsigned long long*)calloc(bs->real_size, sizeof(unsigned long long));
}

bool BitsetGet(Bitset bs, size_t idx) {
	assert(idx < bs.size);

	size_t w = idx / 64;
	size_t r = idx % 64;

	return (bs.data[w] >> r) & 1;
}

void BitsetSet(Bitset bs, size_t idx, size_t value) {
	assert(value <= 1);
	
	size_t w = idx / 64;
	size_t r = idx % 64;
	
	if (value == 1) bs.data[w] |= (1ULL << r);
	else bs.data[w] &= ~(1ULL << r);
}

void BitsetSetString(Bitset bs, size_t n, char* str) {
	size_t m = ((n < bs.size) ? n : bs.size);
	
	for (size_t i = 0; i < m; i++) {
		assert(str[i] == '0' || str[i] == '1');
		
		BitsetSet(bs, i, str[i] - '0');
	}
}

void BitsetFree(Bitset* bs) {
	free(bs->data);
	bs->data = NULL;
	bs->size = 0;
	bs->real_size = 0;
}

inline size_t popcount(unsigned long long n) {
	size_t ret = 0;
	
	while (n) {
		ret++;
		n &= n - 1;
	}

	return ret;
}

size_t BitsetPopcount(Bitset bs) {
	size_t ret = 0;

	for (size_t i = 0; i < bs.real_size; i++) {
		ret += popcount(bs.data[i]);
	}

	return ret;
}

char* BitsetGetString(Bitset bs) {
	char* ret = (char*)malloc(bs.size + 1);
	for (size_t i = 0; i < bs.size; i++) {
		ret[i] = BitsetGet(bs, i) + '0';
	}
	ret[bs.size] = '\0';
	return ret;
}

void BitsetOr(Bitset a, Bitset b) {
	size_t n = ((a.size < b.size) ? a.size : b.size);

	for (size_t i = 0; i < n; i++) {
		BitsetSet(a, i, BitsetGet(a, i) | BitsetGet(b, i));
	}
}

void BitsetAnd(Bitset a, Bitset b) {
	size_t n = ((a.size < b.size) ? a.size : b.size);

	for (size_t i = 0; i < n; i++) {
		BitsetSet(a, i, BitsetGet(a, i) & BitsetGet(b, i));
	}
}

void BitsetXor(Bitset a, Bitset b) {
	size_t n = ((a.size < b.size) ? a.size : b.size);

	for (size_t i = 0; i < n; i++) {
		BitsetSet(a, i, BitsetGet(a, i) ^ BitsetGet(b, i));
	}
}

void BitsetNot(Bitset a) {
	for (size_t i = 0; i < a.real_size; i++) {
		a.data[i] ^= ULONG_MAX;
	}
}

int BitsetComp(Bitset a, Bitset b) {
	assert(a.size == b.size);
	
	size_t n = a.size;
	
	bool a_le_b = true, b_le_a = true;

	for (size_t i = 0; i < n; i++) {
		if (!(BitsetGet(a, i) <= BitsetGet(b, i))) {
			a_le_b = false;
		}
		if (!(BitsetGet(b, i) <= BitsetGet(a, i))) {
			b_le_a = false;
		}
	}

	if (a_le_b && b_le_a) {
		return 0;
	} else if (a_le_b) {
		return -1;
	} else if (b_le_a) {
		return 1;
	} else {
		return 2;
	}
}

#endif
