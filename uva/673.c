#include <stdio.h>

#define MAX_S 130
#define MAX_B 65

char stack[MAX_B];

int top;
int valid;

#define POP() (top--)

#define TOP() (stack[top-1])

#define PUSH(c) do { stack[top++] = c; } while(0)

#define ISEMPTY() (top == 0)

#define ISFULL() (top == MAX_B)

#define INIT() do { top = 0; valid = 0; } while(0)

int ismatch(char c) {
	if (ISEMPTY()) return 0;
	switch(TOP()) {
		case '(': return ')' == c;
		case '[': return ']' == c;
	}
}

int main(int argc, char const *argv[])
{
	char buf[MAX_S];
	char *ptr;
	int n;
	scanf("%d\n", &n);

	while(n--) {
		INIT();
		fgets(buf, MAX_S, stdin);
		ptr = buf;
		while (*ptr != '\n' && *ptr != 0) {
			if (ismatch(*ptr)) {
				POP();
			}
			else {
				PUSH(*ptr);
				if (*ptr == ')' || *ptr == ']' || ISFULL()) {
					break;
				}
			}
			ptr++;
		}
		if (ISEMPTY()) {
			valid = 1;
		}
		if (valid) printf("Yes\n");
		else printf("No\n");
	}

	return 0;
}