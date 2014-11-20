/**
 * Text-processing tools like awk and sed allow you to automatically perform a
 * sequence of editing operations based on a script. For this problem we
 * consider the specific case in which we want to perform a series of string
 * replacements, within a single line of text, based on a fixed set of rules.
 * Each rule specifies the string to find, and the string to replace it with,
 * as shown below.
 *
 * Rule	Find	Replace-by
 * 1.	ban		bab
 * 2.	baba	be
 * 3.	ana		any
 * 4.	ba b	hind the g
 *
 * To perform the edits for a given line of text, start with the first rule.
 * Replace the first occurrence of the find string within the text by the
 * replace-by string, then try to perform the same replacement again on the new
 * text. Continue until the find string no longer occurs within the text, and
 * then move on to the next rule. Continue until all the rules have been
 * considered. Note that (1) when searching for a find string, you always start
 * searching at the beginning of the text, (2) once you have finished using a
 * rule (because the find string no longer occurs) you never use that rule
 * again, and (3) case is significant.
 *
 * For example, suppose we start with the line
 *
 * banana boat
 *
 * and apply these rules. The sequence of transformations is shown below, where
 * occurrences of a find string are underlined and replacements are boldfaced.
 * Note that rule 1 was used twice, then rule 2 was used once, then rule 3 was
 * used zero times, and then rule 4 was used once.
 *
 * Before	After
 * banana boat	babana boat
 * babana boat	bababa boat
 * bababa boat	beba boat
 * beba boat	behind the goat
 *
 * The input contains one or more test cases, followed by a line containing only
 * 0 (zero) that signals the end of the file. Each test case begins with a line
 * containing the number of rules, which will be between 1 and 10. Each rule is
 * specified by a pair of lines, where the first line is the find string and the
 * second line is the replace-by string. Following all the rules is a line
 * containing the text to edit. For each test case, output a line containing
 * the final edited text.
 *
 * Both find and replace-by strings will be at most 80 characters long. Find
 * strings will contain at least one character, but replace-by strings may be
 * empty (indicated in the input file by an empty line). During the edit process
 * the text may grow as large as 255 characters, but the final output text will
 * be less than 80 characters long.
 *
 * The first test case in the sample input below corresponds to the example shown
 * above.
 *
 * Example input:
 *
 * 4
 * ban
 * bab
 * baba
 * be
 * ana
 * any
 * ba b
 * hind the g
 * banana boat
 * 1
 * t
 * sh
 * toe or top
 * 0
 *
 * Example output:
 *
 * behind the goat
 * shoe or shop
 *
 * Solution:
 *	1. Use kmp for string matching
 *  2. Use string list for string manupilation
 *
 * Traps:
 *	1. the replace-by string may be empty
 *  2. the final result may be empty
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_S 100
#define MAX_T 256
#define MAX_R 10

typedef struct str_list* slst_t;
typedef struct str_node* snde_t;

struct str_node {
	char c;
	snde_t next;
	snde_t prev;
};

struct str_list {
	snde_t head;
	snde_t tail;
};

snde_t new_node(char c) {
	snde_t nd = calloc(1, sizeof(*nd));
	nd->c = c;
	return nd;
}

slst_t new_slist() {
	slst_t lt = calloc(1, sizeof(*lt));
	return lt;
}

void lst_push(slst_t lst, char c) {
	snde_t nd = new_node(c);

	nd->prev = lst->tail;

	if (nd->prev) {
		nd->prev->next = nd;
	} else {
		lst->head = nd;
	}

	lst->tail = nd;
}

void append(slst_t lst, slst_t ap) {
	lst->tail->next = ap->head;
	ap->head->prev = lst->tail;
}

void lst_dump(slst_t lst) {
	snde_t i = lst->head;
	while(i != NULL) {
		printf("%c", i->c);
		i = i->next;
	}
}

slst_t str2lst(const char* str) {
	int i = 0;
	slst_t lst = new_slist();
	while(str[i] != 0) {
		lst_push(lst, str[i]);
		i++;
	}
	return lst;
}

unsigned* kmp_init_failure(const char* pattern, size_t len) {

	unsigned* f = calloc(len, sizeof(unsigned));

	f[0] = 0;

	unsigned k = 0;

	int i;

	for(i = 1; i != len; ++i) {
		k = f[i-1];
		while(k != 0 && pattern[k] != pattern[i]) {
			k = f[k];
		}
		if (pattern[k] == pattern[i]) {
			f[i] = f[k] + 1;
		} else {
			f[i] = f[k];
		}
	}

	return f;
}

int slst_kmp_find(slst_t ltext, char* pattern, size_t len, unsigned* f) {

	int i = 0, p = 0;
	snde_t sn = ltext->head;

	while(sn != NULL)
	{
		while (p != 0 && sn->c != pattern[p]) {
			p = f[p];
		}

		if (sn->c == pattern[p]) {
			p++;

			if (p == len) {
				return i - p + 1;
			}
		}

		i++;
		sn = sn->next;
	}

	return -1;
}

void slst_replace(slst_t ltext, size_t idx, size_t len, slst_t sub) {
	snde_t start, end, substart, subend;

	snde_t sn = ltext->head;

	while(idx--) sn = sn->next;
	start = sn->prev;
	while(len--) sn = sn->next;
	end = sn;

	if (sub->head) {
		if(start)
			start->next = sub->head;
		else
			ltext->head = sub->head;
		sub->head->prev = start;

		if (end) {
			end->prev = sub->tail;
		}
		sub->tail->next = end;
	} else {
		if(start) {
			start->next = end;
			if (end) end->prev = start;
		}
		else {
			ltext->head = end;
			if (end) end->prev = NULL;
		}
	}
}

int main(int argc, char const *argv[])
{
	char buf[MAX_S];
	char text[MAX_T];
	int r;
	char ruletbl[MAX_R][MAX_S];
	char subtbl[MAX_R][MAX_S];
	unsigned* ftbl[MAX_R];
	size_t lentbl[MAX_R];
	int i, idx;

	while(scanf("%d\n", &r)) {
		if (r == 0) break;

		for(i = 0; i != r; ++i) {
			fgets(buf, MAX_S, stdin);
			int l = strlen(buf);
			buf[--l] = 0;
			strcpy(ruletbl[i], buf);
			lentbl[i] = l;
			ftbl[i] = kmp_init_failure(buf, lentbl[i]);

			fgets(buf, MAX_S, stdin);
			buf[strlen(buf) - 1] = 0;
			strcpy(subtbl[i], buf);
		}

		fgets(text, MAX_T, stdin);
		text[strlen(text) - 1] = 0;

		slst_t ltext = str2lst((const char*)text);

		for (i = 0; i < r; ++i)
		{
			while((idx = slst_kmp_find(ltext, ruletbl[i], lentbl[i], ftbl[i])) != -1) {
				slst_replace(ltext, idx, lentbl[i], str2lst((const char*)subtbl[i]));
			}
		}

		lst_dump(ltext);
		printf("\n");
	}

	return 0;
}