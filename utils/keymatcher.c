#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "keymatcher.h"

#define MAX_N 26

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

void dump_kn(keynode* kn, char* prefix, int prefid) {
	if (kn->is_term) {
		prefix[prefid] = 0;
		printf("%s\n", prefix);
	}

	for(int i=0; i != MAX_N; ++i) {
		if (kn->next[i] != NULL) {
			char* buf = malloc(sizeof(char) * 200);
			strcpy(buf, prefix);
			buf[prefid] = 'a' + i;
			dump_kn(kn->next[i], buf, prefid+1);
		}
	}
}

void dump_km(keymatcher* km) {
	dump_kn(km->start, malloc(sizeof(char) * 200), 0);
}