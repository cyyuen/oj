#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25

typedef struct node {
	int id;
	int next;
	int prev;
} node;

node list[MAX_N];

void deletenode(int *len, int nd) {
	printf("%3d", list[nd].id);

	list[list[nd].next].prev = list[nd].prev;
	list[list[nd].prev].next = list[nd].next;

	(*len)--;
}

void resetList(int N) {
	int max = N - 1;
	int i;

	for (i = 1; i < max; ++i) {
		list[i].next = i + 1;
		list[i].prev = i - 1;
	}

	list[0].next = 1;
	list[0].prev = max;

	list[max].next = 0;
	if (max != 0)
		list[max].prev = max - 1;
	else
		list[max].prev = 0;
}

void initList() {
	int i;
	for (i = 0; i != MAX_N; ++i) {
		list[i].id = i + 1;
	}

	resetList(MAX_N);
}



void dole(int N, int k, int m) {
	int len = N;

	int workerk = 0;
	int workerm = N - 1;
	int i = 0;

	while(len != 0) {
		if (i)
			printf(",");

		for(i = 1; i <k; ++i) {
			workerk = list[workerk].next;
		}

		for (i = 1; i < m; ++i) {
			workerm = list[workerm].prev;
		}

		if (workerk == workerm) {
			deletenode(&len, workerk);
			if (len == 0) break;

			workerk = list[workerk].next;
			workerm = list[workerm].prev;

		} else {
			deletenode(&len, workerk);
			deletenode(&len, workerm);
			if (len == 0) break;

			workerk = list[list[workerk].prev].next;
			workerm = list[list[workerm].next].prev;
		}
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int N, k, m;
	initList();
	while (scanf("%d %d %d", &N, &k, &m) != EOF && N != 0) {
		resetList(N);
		dole(N, k, m);
	}
	return 0;
}