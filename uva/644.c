/**
 * Immediate Decodability
 * An encoding of a set of symbols is said to be immediately decodable if no code for one symbol is the prefix of a code for another symbol. We will assume for this problem that all codes are in binary, that no two codes within a set of codes are the same, that each code has at least one bit and no more than ten bits, and that each set has at least two codes and no more than eight.
 *
 *
 * Examples: Assume an alphabet that has symbols {A, B, C, D}
 *
 *
 * The following code is immediately decodable:
 *
 *
 * A:01 B:10 C:0010 D:0000
 *
 *
 * but this one is not:
 *
 *
 * A:01 B:10 C:010 D:0000 (Note that A is a prefix of C)
 *
 * Input
 *
 * Write a program that accepts as input a series of groups of records from a data file. Each record in a group contains a collection of zeroes and ones representing a binary code for a different symbol. Each group is followed by a single separator record containing a single 9; the separator records are not part of the group. Each group is independent of other groups; the codes in one group are not related to codes in any other group (that is, each group is to be processed independently).
 *
 * Output
 *
 * For each group, your program should determine whether the codes in that group are immediately decodable, and should print a single output line giving the group number and stating whether the group is, or is not, immediately decodable.
 *
 * The Sample Input describes the examples above.
 *
 * Sample Input
 *
 * 01
 * 10
 * 0010
 * 0000
 * 9
 * 01
 * 10
 * 010
 * 0000
 * 9
 * Sample Output
 *
 * Set 1 is immediately decodable
 * Set 2 is not immediately decodable
 *
 * =====================================================
 * Use Radix Tree to check the prefix (ternimal node has childs)
 *  case 1: append to exist node
 *		ex. 01 010
 *		node 010 appends 0 to 01 and hence 01 is the prefix
 *
 *	case 2: split the exist path
 *		ex. 010 01
 *		node 01 set the term node in the middle of the path of 010. 01 is the prefix
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 200

typedef struct bradix_tree* brt_t;
typedef struct rnode* rnode_t;

int r_index(char c) {
	return c - '0';
}

struct rnode
{
	bool is_term;
	struct rnode* next[2];
};

struct bradix_tree
{
	rnode_t root;
};

rnode_t new_rnode() {
	rnode_t rnode = calloc(1, sizeof(*rnode));
	return rnode;
}

brt_t new_brt() {
	brt_t brt = calloc(1, sizeof(*brt));
	brt->root = new_rnode();
	return brt;
}

rnode_t add_rnode(rnode_t rn, char k) {
	int idx = r_index(k);
	if (rn->next[idx] == NULL) {
		rn->next[idx] = new_rnode();
	}
	return rn->next[idx];
}

bool add_node(brt_t brt, char* str) {
	int i = 0;
	rnode_t rn = brt->root;
	while(str[i] != 0) {
		rn = add_rnode(rn, str[i]);
		if (rn->is_term)
			return false;
		i++;
	}
	rn->is_term = true;

	if (rn->next[0] != NULL || rn->next[1] != NULL)
		return false;

	return true;
}

int main(int argc, char const *argv[])
{
	char buf[MAX_N];
	bool can_decode = true;
	int i = 1;
	brt_t brt = new_brt();

	while(scanf("%s\n", buf) != EOF) {

		if (buf[0] == '9') {

			if (can_decode) {
				printf("Set %d is immediately decodable\n", i++);
			} else {
				printf("Set %d is not immediately decodable\n", i++);
			}

			can_decode = true;
			brt = new_brt();

			continue;
		}

		if (!can_decode) continue;

		can_decode = add_node(brt, buf);
	}
	return 0;
}