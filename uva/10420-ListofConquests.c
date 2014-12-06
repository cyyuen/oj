#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SKIPLIST_MAX_LEVEL 32
#define SKIPLIST_P 0.25
#define MAX_D 76

typedef struct skiplistNode
{
	char* key;
	int value;
    struct skiplistNode* forward[];
} skiplistNode;

typedef struct skiplist
{
	skiplistNode *head, *tail;
	unsigned int level;
	unsigned long length;
} skiplist;

/**
 * Create a node with level
 */
skiplistNode* slCreateNode(const char* key, int v, int level) {
	skiplistNode* sn = malloc(sizeof(*sn) + sizeof(skiplistNode*)*level);
	sn->key = malloc(sizeof(char) * MAX_D);
	strcpy(sn->key, key);
	sn->value = v;
	return sn;
}

/**
 * create a empty skiplist
 */
skiplist* skiplistCreate() {
	skiplist* sl = malloc(sizeof(*sl));
	sl->level = 0;
	sl->length = 0;
	sl->head = slCreateNode("0", 0, SKIPLIST_MAX_LEVEL);
	sl->tail = NULL;
	return sl;
}

/* Returns a random level for the new skiplist node we are going to create.
 * The return value of this function is between 1 and SKIPLIST_MAX_LEVEL
 */
int slRandomLevel(void) {
    int level = 1;
    while ((random()&0xFFFF) < (SKIPLIST_P * 0xFFFF))
        level += 1;
    return (level<SKIPLIST_MAX_LEVEL) ? level : SKIPLIST_MAX_LEVEL;
}

/**
 *	@param searchKey
 *  @return return the value associated with the key if the key found, otherwise NULL
 */
int skiplistInsert(skiplist *sl, const char* searchKey, int newValue) {
	skiplistNode* update[SKIPLIST_MAX_LEVEL], *x;

	x = sl->head;

	int i;

	for (i = sl->level; i >= 0; --i)
	{
		while(x->forward[i] && strcmp(x->forward[i]->key, searchKey) < 0)
			x = x->forward[i];
		update[i] = x;
	}

	if (x->forward[0])
		x = x->forward[0];

	if (x && strcmp(x->key, searchKey) == 0) {
		x->value = newValue;
		return 1;
	} else {
		int lv = slRandomLevel();

		x = slCreateNode(searchKey, newValue, lv);

		if (lv > sl->level) {
			for (i = lv; i > sl->level; --i)
			{
				update[i] = sl->head;
			}
			sl->level = lv;
		}

		for (i = lv; i >= 0; --i)
		{
			x->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = x;
		}
		sl->length++;
	}

	if (!x->forward[0]) {
		sl->tail = x;
	}

	return 0;
}

typedef void (*skiplist_foreachfunc_t) (skiplistNode*);

void skiplistForeach(skiplist* sl, skiplist_foreachfunc_t func) {
	skiplistNode *x = sl->head;
	while(x->forward[0]) {
		(*func)(x->forward[0]);
		x = x->forward[0];
	}
}

/**
 *	@param searchKey
 *  @return return the value associated with the key if the key found, otherwise NULL
 */
int skiplistSearch(skiplist *sl, const char* searchKey) {
	skiplistNode* x = sl->head;

	int i;

	for (i = sl->level; i >= 0; --i) {
		while(x->forward[i] && strcmp(x->forward[i]->key, searchKey) < 0)
			x = x->forward[i];
	}

	x = x->forward[0];

	if (x && strcmp(x->key, searchKey) == 0) {
		return x->value;
	}

	return 0;
}

void dump(skiplistNode* sn) {
	printf("%s %d\n", sn->key, sn->value);
}

int main(int argc, char const *argv[])
{
	int t, n;
	char buf[20];
	char dummy[MAX_D];

	while(scanf("%d\n", &t) != EOF) {
		skiplist* sl = skiplistCreate();

		while(t--) {
			scanf("%s", buf);
			fgets(dummy, MAX_D, stdin);

			n = skiplistSearch(sl, (const char*)buf);
			skiplistInsert(sl, (const char*)buf, n+1);
		}

		skiplistForeach(sl, &dump);
	}

	return 0;
}