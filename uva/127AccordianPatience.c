#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_CARD 52

#define INCR(n) (((n)++)%3)
#define PREV_D(n, d) (((n)+4-(d))%3)

#define PUSH(nd, card) do {\
	(nd)->buf[(nd)->top++] = (card); \
} while(0)

#define TOP(nd) ((nd)->buf[(nd)->top - 1])

#define SIZE(nd) ((nd)->top)

#define POP(nd) ((nd)->buf[(nd)->top--])

uint8_t suit2uint8(char suit) {
	switch(suit) {
		case 'C': return 0;
		case 'D': return 1;
		case 'H': return 2;
		case 'S': return 3;
		default: return -1;
	}
}

char int2suit(uint8_t i) {
	switch(i) {
		case 0: return 'C';
		case 1: return 'D';
		case 2: return 'H';
		case 3: return 'S';
		default: return '0';
	}
}

uint8_t rank2uint8(char rank) {
	if ( rank >= '2' && rank <= '9') {
		return rank - '0';
	}
	switch(rank) {
		case 'A': return 1;
		case 'T': return 10;
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
		default: return -1;
	}
}

char int2rand(uint8_t i) {
	if (i>= 2 && i <=9) {
		return '0' + i;
	}
	switch(i) {
		case 1: return 'A';
		case 10: return 'T';
		case 11: return 'J';
		case 12: return 'Q';
		case 13: return 'K';
		default: return '0';
	}
}


typedef struct node {
	struct node *next, *prev;
	int top;
	uint8_t buf[];
} node;

typedef struct {
	node* header;
	node* tail;
	int len;
} list;

node* new_node(uint8_t card) {
	node* nd = calloc(1, sizeof(*nd) + sizeof(uint8_t) * NUM_CARD);
	PUSH(nd, card);
	return nd;
}

void printcard(uint8_t i){
	printf("%c%c", int2rand(i>>2), int2suit(i%4));
}

bool ismatch(uint8_t a, uint8_t b) {
	return (a >> 2 == b >> 2) || (a%4 == b%4);
}

void deleteNodeIfEmpty(node* nd, list* l) {
	if (nd->top == 0) {
			l->len--;
	if (nd->next) {
		nd->next->prev = nd->prev;
	}
	if (nd->prev) {
		nd->prev->next = nd->next;
	}

	if (l->header == nd)
		l->header = nd->next;
	}
}

void reducenode(node* nd, list* l) {
	node *max_n = nd, *max_jump = nd;

	while(max_n) {
		max_jump = max_n;
		while(1) {
			if (max_jump->next && max_jump->next->next
				&& max_jump->next->next->next
				&& ismatch(TOP(max_jump->next->next->next), TOP(max_n))) {
				max_jump = max_jump->next->next->next;
			} else if (max_jump->next && ismatch(TOP(max_jump->next), TOP(max_n))) {
				max_jump = max_jump->next;
			} else {
				break;
			}
		}

		if (max_jump != max_n) {
			PUSH(max_jump, TOP(max_n));
			POP(max_n);
			deleteNodeIfEmpty(max_n, l);
			max_n = max_jump->prev;
		} else {
			max_n = max_n->prev;
		}
	}
}

void accordian(list* l) {
	reducenode(l->header, l);
}

void add2list(list* l, uint8_t card) {
	node* nd = new_node(card);
	nd->next = l->header;
	if (nd->next)
		nd->next->prev = nd;
	l->header = nd;

	if (nd->next == NULL)
		l->tail = nd;

	l->len++;

	accordian(l);
}

uint8_t card2uint8(const char* card) {
	return suit2uint8(card[1]) + (rank2uint8(card[0]) << 2);
}

void rdump(node* nd) {
	while(nd) {
		printf(" %d", nd->top);
		nd = nd->prev;
	}
}

int main(int argc, char const *argv[])
{
	char buf[3];
	int i;

	while(scanf("%s", buf) != EOF && buf[0] != '#') {
		list l;
		l.len = 0;
		l.header = NULL;

		uint8_t card = card2uint8(buf);
		add2list(&l, card);

		for (i = 0; i < 51; ++i)
		{
			scanf("%s", buf);
			uint8_t card = card2uint8(buf);
			add2list(&l, card);
		}

		node* nd = l.header;

		printf("%d %s remaining:", l.len, (l.len == 1? "pile": "piles"));
		rdump(l.tail);
		printf("\n");
	}

	return 0;
}