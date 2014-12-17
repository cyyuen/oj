#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int id;
	struct node* next;
	struct node* prev;
} node;

typedef struct list {
	int len;
	node* head;
	node* tail;
} list;

node* newnode(int id) {
	node* nd = malloc(sizeof(*nd));
	nd->id = id;
	return nd;
}

void addnode(list* lt, int id) {
	node* nd = newnode(id);

	if (lt->len == 0) {
		lt->head = lt->tail = nd;
	}

	nd->next = lt->head;
	lt->head->prev = nd;

	nd->prev = lt->tail;
	lt->tail->next = nd;

	lt->tail = nd;


	lt->len++;
}

list* newlist(int len) {
	list* lt = malloc(sizeof(*lt));
	int i;
	lt->len = 0;
	for (i = 1; i <= len; ++i) {
		addnode(lt, i);
	}
	return lt;
}

void deletenode(list* lt, node* nd) {
	printf("%3d", nd->id);

	nd->next->prev = nd->prev;
	nd->prev->next = nd->next;

	lt->len--;
}

void dole(list* lt, int k, int m) {
	node* workerk = lt->head;
	node* workerm = lt->tail;
	int i = 0;

	while(lt->len != 0) {
		if (i)
			printf(",");

		for(i = 1; i <k; ++i) {
			workerk = workerk->next;
		}

		for (i = 1; i < m; ++i) {
			workerm = workerm->prev;
		}

		if (workerk == workerm) {
			node* tmp = workerk;
			deletenode(lt, workerk);
			if (lt->len == 0) break;

			workerk = workerk->next;
			workerm = workerm->prev;

			free(tmp);
		} else {
			node *tmpk = workerk, *tmpm = workerm;
			deletenode(lt, workerk);
			deletenode(lt, workerm);
			if (lt->len == 0) break;

			workerk = workerk->prev->next;
			workerm = workerm->next->prev;

			free(tmpk);
			free(tmpm);
		}
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int N, k, m;
	while (scanf("%d %d %d", &N, &k, &m) != EOF && N != 0) {
		list* lt = newlist(N);
		dole(lt, k, m);
	}
	return 0;
}