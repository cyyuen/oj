/**
 *  Excuses, Excuses!
 *
 * Judge Ito is having a problem with people subpoenaed for jury duty giving
 * rather lame excuses in order to avoid serving. In order to reduce the amount
 * of time required listening to goofy excuses, Judge Ito has asked that you
 * write a program that will search for a list of keywords in a list of excuses
 * identifying lame excuses. Keywords can be matched in an excuse regardless of
 * case.
 *
 * Input
 *
 * Input to your program will consist of multiple sets of data.
 *
 * Line 1 of each set will contain exactly two integers. The first number (0 < k <= 20)
 * defines the number of keywords to be used in the search. The second number ( 0 < e <= 20 )
 * defines the number of excuses in the set to be searched.
 * Lines 2 through K+1 each contain exactly one keyword.
 * Lines K+2 through K+1+E each contain exactly one excuse.
 * All keywords in the keyword list will contain only contiguous lower case
 * alphabetic characters of length L ( 0< L <= 20 ) and will occupy columns 1
 * through L in the input line.
 * All excuses can contain any upper or lower case alphanumeric character, a
 * space, or any of the following punctuation marks [SPMamp".,!?&] not including
 * the square brackets and will not exceed 70 characters in length.
 * Excuses will contain at least 1 non-space character.
 *
 * Output
 *
 * For each input set, you are to print the worst excuse(s) from the list.
 *
 * The worst excuse(s) is/are defined as the excuse(s) which contains the largest
 * number of incidences of keywords.
 * If a keyword occurs more than once in an excuse, each occurrance is considered
 * a separate incidence.
 * A keyword ``occurs" in an excuse if and only if it exists in the string in
 * contiguous form and is delimited by the beginning or end of the line or any
 * non-alphabetic character or a space.
 * For each set of input, you are to print a single line with the number of the
 * set immediately after the string ``Excuse Set #". (See the Sample Output).
 * The following line(s) is/are to contain the worst excuse(s) one per line
 * exactly as read in. If there is more than one worst excuse, you may print
 * them in any order.
 *
 * After each set of output, you should print a blank line.
 *
 * Sample Input
 *
 * 5 3
 * dog
 * ate
 * homework
 * canary
 * died
 * My dog ate my homework.
 * Can you believe my dog died after eating my canary... AND MY HOMEWORK?
 * This excuse is so good that it contain 0 keywords.
 * 6 5
 * superhighway
 * crazy
 * thermonuclear
 * bedroom
 * war
 * building
 * I am having a superhighway built in my bedroom.
 * I am actually crazy.
 * 1234567890.....,,,,,0987654321?????!!!!!!
 * There was a thermonuclear war!
 * I ate my dog, my canary, and my homework ... note outdated keywords?
 * Sample Output
 *
 * Excuse Set #1
 * Can you believe my dog died after eating my canary... AND MY HOMEWORK?
 *
 * Excuse Set #2
 * I am having a superhighway built in my bedroom.
 * There was a thermonuclear war!
 * =============================================================================
 *
 * Tricky Part:
 * 1. [SPMamp".,!?&] shoule be read as [#@".,!?&]. SPMamp => #@
 * 2. Not print in any order but in the appear order
 *
 * Data Structure:
 *	Simplified Radix tree which only support lower case alphebet (a-z)
 */
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_K 20
#define MAX_E 20
#define MAX_L 20
#define MAX_S 200

#define DELIM " #@\n\t\".,!?&0123456789"

#define MAX_N 26

typedef struct keymatcher_ keymatcher;

keymatcher* new_keymatcher();

void addkey(keymatcher* km, const char* key);

bool is_match(keymatcher* km, const char* key);

void dump_km(keymatcher* km);

int kindex(char c) {
	return tolower(c) - 'a';
}

typedef struct keynode_
{
	struct keynode_* next[MAX_N];
	bool is_term;
} keynode;

struct keymatcher_
{
	keynode* start;
};

keynode*
new_keynode() {
	keynode* kn = malloc(sizeof(keynode));
	memset(kn->next, (int)NULL, sizeof(keynode*) * MAX_N);
	kn->is_term = false;
	return kn;
}

keymatcher*
new_keymatcher() {
	keymatcher* km = malloc(sizeof(keymatcher));

	km->start = new_keynode();

	return km;
}

keynode*
addkeynode(keynode* kn, char k) {
	int idx = kindex(k);
	if (kn->next[idx] == NULL) {
		kn->next[idx] = new_keynode();
	}
	return kn->next[idx];
}

keynode*
getkeynode(keynode* kn, char k) {
	int idx = kindex(k);
	return kn->next[idx];
}

bool
haskeynode(keynode* kn, char k) {
	keynode* knode = getkeynode(kn, k);
	return knode != NULL;
}

void
addkey(keymatcher* km, const char* key) {
	int i = 0;
	keynode* kn = km->start;
	while(key[i] != 0) {
		kn = addkeynode(kn, key[i]);
		i++;
	}
	kn->is_term = true;
}

bool
is_match(keymatcher* km, const char* key) {
	int i = 0;
	keynode* kn = km->start;

	while(key[i] != 0) {
		char k = tolower(key[i]);
		if (haskeynode(kn, k)) {
			kn = getkeynode(kn, k);
		} else {
			return false;
		}
		i++;
	}
	return kn->is_term;
}

typedef struct
{
	char** buf;
	int sp;
} sstack;

sstack* new_sstack(int size) {
	sstack* s = malloc(sizeof(sstack));
	s->buf = malloc(sizeof(char*) * size);
	memset(s->buf, (int)NULL, sizeof(char*) * size);
	s->sp = 0;
	return s;
}

void sstack_clean(sstack* s) {
	s->sp = 0;
}

void sstack_push(sstack* s, char* str) {
	if (s->buf[s->sp] == NULL) {
		s->buf[s->sp] = malloc(sizeof(char) * MAX_S);
	}
	strcpy(s->buf[s->sp], str);
	s->sp++;
}

void dump_sstack(sstack* s) {
	int i;
	for (i = 0; i < s->sp; ++i)
	{
		printf("%s", s->buf[i]);
	}
}

int main(int argc, char const *argv[])
{
	int k, e;
	sstack* excusestack = new_sstack(MAX_S);
	int max, i;
	int j = 1;

	char keybuf[MAX_L + 1];
	char excusebuf[MAX_S + 1];
	char delimbuf[MAX_S + 1];

	while(scanf("%d %d\n", &k, &e) > 0) {
		max = 0;

		keymatcher* km = new_keymatcher();

		while(k--) {
			scanf("%s\n", keybuf);
			addkey(km, keybuf);
		}

		while(e--) {
			i = 0;

			fgets(excusebuf, MAX_S + 1, stdin);

			strcpy(delimbuf, excusebuf);

			char * pch;

  			pch = strtok (delimbuf, DELIM);
  			while (pch != NULL)
  			{
  				if (is_match(km, pch))
  				{
  					i++;
  				}
    			pch = strtok (NULL, DELIM);
  			}

  			if (i == max) {
  				sstack_push(excusestack, excusebuf);
  			} else if (i > max) {
  				max = i;
  				sstack_clean(excusestack);
  				sstack_push(excusestack, excusebuf);
  			}

		}

		printf("Excuse Set #%d\n", j++);
		dump_sstack(excusestack);
		printf("\n");

	}
	return 0;
}