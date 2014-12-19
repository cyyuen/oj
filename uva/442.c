#include <stdio.h>
#include <stdlib.h>

#define MAX_STK 130

typedef struct
{	int n;
	int m;
} matrix;

matrix** stack;

int top;
int comp;
int valid;

#define POP() (stack[--top])

#define TOP() (stack[top-1])

#define PUSH(c) do { stack[top++] = c; } while(0)

#define ISEMPTY() (top == 0)

#define ISFULL() (top == MAX_B)

#define STK_INIT() do { top = comp = 0; valid = 1; } while(0)

int eval(int n, int m) {
	matrix* mtx = ISEMPTY()? 0: TOP();

	if (mtx) {
		if (mtx->m == n) {
			mtx->m = m;
			comp += (mtx->n * n * m);
			return 1;
		} else {
			return 0;
		}
	} else {
		mtx = malloc(sizeof(*mtx));
		mtx->n = n;
		mtx->m = m;
		PUSH(mtx);
		return 1;
	}
}

int eval_match() {
	matrix* mtx = POP();
	POP();
	int result = eval(mtx->n, mtx->m);
	free(mtx);
	return result;
}

int main(int argc, char const *argv[])
{
	int n;
	char idx;
	char* ptr;
	int r, c;
	char buf[200];

	matrix* A = malloc(sizeof(*A) * 26);
	stack = malloc(sizeof(matrix*) * MAX_STK);

	while(scanf("%d\n", &n) != EOF) {
		while(n--) {
			scanf("%c %d %d\n", &idx, &r, &c);
			int i = idx - 'A';
			A[i].n = r;
			A[i].m = c;
		}

		while(scanf("%s", buf) != EOF) {
			STK_INIT();
			ptr = buf;

			while (*ptr != 0) {
				if (*ptr == '(') {
					PUSH(0);
				} else if (*ptr == ')') {
					if (!eval_match()) {
						valid = 0;
						break;
					}
				} else {
					int idx = *ptr - 'A';
					if (!eval(A[idx].n, A[idx].m)) {
						valid = 0;
						break;
					}
				}
				ptr++;
			}
			if (valid) {
				printf("%d\n", comp);
			} else {
				printf("error\n");
			}
		}
	}

	return 0;
}