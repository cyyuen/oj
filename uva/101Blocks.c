#include <stdio.h>

#define MAX_B 25

typedef struct block {
	int id;
	int stk;
	struct block *up, *down;
} block;

block blocks[MAX_B];
block positions[MAX_B];

void push(block* a, block* b) {
	if (a->down)
		a->down->up = NULL;
	positions[b->stk].down = positions[a->stk].down;
	positions[a->stk].down = a->down;
	a->down = b;
	b->up = a;
	while(a) {
		a->stk = b->stk;
		a = a->up;
	}
}

void blocks_reset(int num) {
	int i;
	for (i=0; i !=num; ++i) {
		push(&blocks[i], &positions[i]);
	}
}

void blocks_init() {
	int i;
	for (i=0; i !=MAX_B; ++i) {
		blocks[i].id = i;
		blocks[i].stk = i;
		positions[i].stk = i;
		positions[i].down = &blocks[i];
		positions[i].up = &blocks[i];
		blocks[i].down = &positions[i];
	}
}

block* stack_top(block* bk) {
	return positions[bk->stk].down;
}

void clean_top(block* bk) {
	block* b = bk->up;
	while(b) {
		push(b, &positions[b->id]);
		b = b->up;
	}
	positions[bk->stk].down = bk;
}

void showblock(int num) {
	int i;
	block* b;
	for (i = 0; i < num; ++i)
	{
		printf("%d:", i);
		b = positions[i].up;
		while(b) {
			printf(" %d", b->id);
			b = b->up;
		}
		printf("\n");
	}
}

block* get_block(char cmd, int id) {
	block* b = &blocks[id];
	switch(cmd) {
		case 't':
		case 'v': clean_top(b); break;
		case 'l': break;
		case 'e': b = stack_top(b); break;
		default: b = NULL;
	}
	return b;
}

int main(int argc, char const *argv[])
{
	int num;
	char cmd[5];
	int id1, id2;
	char c1;
	blocks_init();
	while(scanf("%d", &num) != EOF) {
		while(scanf("%s", cmd) != EOF && cmd[0] != 'q') {
			char c1 = cmd[2];
			scanf("%d %s %d", &id1, cmd, &id2);
			if (id1 != id2 && blocks[id1].stk != blocks[id2].stk)
				push(get_block(c1, id1), get_block(cmd[2], id2));
		}
		showblock(num);
		blocks_reset(num);
	}
	return 0;
}