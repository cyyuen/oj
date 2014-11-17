#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char statemap_bool_t;
#define MAX_BUF 250
#define STATE_TRUE '1'
#define STATE_FALSE '0'
#define STATE_NOT_FOUND -1

typedef struct statemachine {
	statemap_bool_t** statemap;
	statemap_bool_t* is_term;
	statemap_bool_t* starter;
	int size;
	char* hasharr;
	int sp; // state pointer; -1 is undefined
	char buffer[MAX_BUF];
	statemap_bool_t matched;
	char current_state;
} statemachine;

int state_hash(statemachine* sm, char state) {

	for (int i = 0; i != sm->size; ++i) {
		if (state == sm->hasharr[i])
			return i;
	}
	return STATE_NOT_FOUND;
}

statemachine* new_statemachine(const char* hasharr) {
	statemachine* sm = malloc(sizeof(statemachine));
	sm->sp = STATE_NOT_FOUND;

	sm->hasharr = (char*) hasharr;
	sm->size = strlen(hasharr);

	sm->statemap = malloc(sizeof(statemap_bool_t*) * sm->size);

	for (int i = 0; i != sm->size; ++i) {
		sm->statemap[i] = malloc(sizeof(statemap_bool_t) * sm->size);
		memset(sm->statemap[i], STATE_FALSE, sizeof(statemap_bool_t) * sm->size);
	}

	sm->is_term = malloc(sizeof(statemap_bool_t) * sm->size);
	memset(sm->is_term, STATE_FALSE, sizeof(statemap_bool_t) * sm->size);

	sm->starter = malloc(sizeof(statemap_bool_t) * sm->size);
	memset(sm->starter, STATE_FALSE, sizeof(statemap_bool_t) * sm->size);

	return sm;
}

void statemachine_addrule(statemachine* sm, const char src, const char dst) {

	int sidx = state_hash(sm, src);

	int didx = state_hash(sm, dst);

	if (sidx != STATE_NOT_FOUND && didx != STATE_NOT_FOUND) {
		sm->statemap[sidx][didx] = STATE_TRUE;
	}
}

void statemachine_addterm(statemachine* sm, const char term) {
	int idx = state_hash(sm, term);
	if (idx != STATE_NOT_FOUND)
		sm->is_term[idx] = STATE_TRUE;
}

void statemachine_starter(statemachine* sm, const char stat) {
	int idx = state_hash(sm, stat);
	if (idx != STATE_NOT_FOUND)
		sm->starter[idx] = STATE_TRUE;
}

void statemap_dump(statemachine* sm) {
	printf("state map: \n");
	for (int i = 0; i != sm->size; ++i) {
		for (int j = 0; j != sm->size; ++j) {
			printf("%c", sm->statemap[i][j]);
			if (j != sm->size - 1) {
				printf(",");
			}
		}
		printf("\n");
	}

	printf("starter: \n");

	for (int i = 0; i != sm->size; ++i) {
		printf("%c", sm->starter[i]);
		if (i != sm->size - 1) {
				printf(",");
		}
	}
	printf("\n");

	printf("terminal: \n");

	for (int i = 0; i != sm->size; ++i) {
		printf("%c", sm->is_term[i]);
		if (i != sm->size - 1) {
				printf(",");
		}
	}
	printf("\n");
}

int main() {
	char buf[MAX_BUF];

	scanf("%s\n", buf);

	statemachine* sm = new_statemachine(buf);

	char s, e, d;

	while(scanf("%c%c%c\n", &s, &e, &d) > 0) {
		if (e == '>') {
			statemachine_addrule(sm, s, d);
		} else if (s == 'e') {
			statemachine_addterm(sm, d);
		} else {
			statemachine_starter(sm, d);
		}
	}

	statemap_dump(sm);

	return 0;
}