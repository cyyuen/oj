/**
 * One of the first users of BIT's new supercomputer was Chip Diller. He extended his exploration of powers of 3 to go from 0 to 333 and he explored taking various sums of those numbers.
 *
 * ``This supercomputer is great,'' remarked Chip. ``I only wish Timothy were here to see these results.'' (Chip moved to a new apartment, once one became available on the third floor of the Lemon Sky apartments on Third Street.)
 *
 * Input
 *
 * The input will consist of at most 100 lines of text, each of which contains a single VeryLongInteger. Each VeryLongInteger will be 100 or fewer characters in length, and will only contain digits (no VeryLongInteger will be negative).
 *
 * The final input line will contain a single zero on a line by itself.
 *
 * Output
 *
 * Your program should output the sum of the VeryLongIntegers given in the input.
 *
 * Sample Input
 *
 * 123456789012345678901234567890
 * 123456789012345678901234567890
 * 123456789012345678901234567890
 * 0
 * Sample Output
 *
 * 370370367037037036703703703670
 *
 * Solution: Use big integer.
 *	bign implementation: use uint64_t array to store the partial result
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define E18 1000000000000000000
#define BLOCK_SIZE 18
#define MIN_BLOCK 10
#define MAX_PREALLOC 100
#define MAX_D 101

typedef struct ubign* ubign_t;

struct ubign
{
	size_t len;
	size_t bp;
	uint64_t buf[];
};

uint64_t str2uint64(const char* str, size_t len) {
	uint64_t tmp = 0;
	int i;
	for (i = 0; i < len; ++i)
	{
		tmp = tmp * 10 + str[i] - '0';
	}
	return tmp;
}

ubign_t new_ubign(size_t len) {
	int num_block = len / BLOCK_SIZE + 1;
	int alloc_block = num_block < MIN_BLOCK? MIN_BLOCK : num_block;

	ubign_t ubign = calloc(1, sizeof(*ubign) + sizeof(uint64_t) * alloc_block);

	ubign->len = len;
	ubign->bp = num_block - 1;
	return ubign;
}

ubign_t str2ubign(const char* str) {
	int len = strlen(str);
	ubign_t ubign = new_ubign(len);

	int base = 0;
	int l = len % BLOCK_SIZE;
	int i = ubign->bp;
	do {
		ubign->buf[i--] = str2uint64(str+base, l);
		base += l;
		l = BLOCK_SIZE;
	} while (i != -1);

	return ubign;
}

ubign_t ubign_add(ubign_t ub1, ubign_t ub2) {
	size_t l1 = ub1->len, l2 = ub2->len;
	int create_new = false;

	ubign_t result;

	if (l1 == l2) {
		result = new_ubign(l1+1);
	} else if (l1 < l2) {
		l1 = l2;
		result = ub2;
	} else {
		result = ub1;
	}

	int i = 0;
	bool addOne = false;
	while(i <= ub1->bp && i <= ub2->bp) {
		result->buf[i] = ub1->buf[i] + ub2->buf[i];

		if (addOne) result->buf[i]++;
		addOne = result->buf[i] / E18 > 0;

		result->buf[i] %= E18;

		i++;
	}
	while(i <= ub1->bp) {
		result->buf[i] = ub1->buf[i];
		if (addOne) result->buf[i]++;
		addOne = result->buf[i] / E18 > 0;
		result->buf[i] %= E18;

		if (i > result->bp) {
			result->bp = i;
		}
		i++;
	}
	while(i <= ub2->bp) {
		result->buf[i] = ub2->buf[i];
		if (addOne) result->buf[i]++;
		addOne = result->buf[i] / E18 > 0;
		result->buf[i] %= E18;

		if (i > result->bp) {
			result->bp = i;
		}
		i++;
	}
	return result;
}

void dump_ubign(ubign_t ubign) {
	int i = ubign->bp;
	if (ubign->buf[i] != 0 || i == 0) {
		printf("%llu", ubign->buf[i]);
	}

	i--;

	while(i != -1) {
		printf("%05llu", ubign->buf[i--]);
	};
}

int main(int argc, char const *argv[])
{
	char buf[MAX_D];
	ubign_t res = str2ubign("0");;

	while(scanf("%s\n", buf) && buf[0] != '0') {
		ubign_t tmp = str2ubign(buf);

		res = ubign_add(res, tmp);
	}
	dump_ubign(res);
	printf("\n");

	return 0;
}