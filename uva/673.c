#include <stdio.h>
#include <stdint.h>

#define MAX_S 130
#define MAX_B 64

int top;
int len;
uint64_t stack;
int valid;
int done;

#define MASK 1

#define POP() do { stack = stack >> 1; len--; } while(0)

#define TOP() (stack & MASK)

#define PUSH(c) do { stack = (stack << 1) + (c); len++; } while(0)

#define ISEMPTY() (len == 0)

#define ISFULL() (len == 64)

#define INIT() do { valid = len = stack = 0; done = 1; } while(0)

#define ISMATCH(c) (ISEMPTY()?0:TOP()?']' == (c):')' == (c))

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
			if (ISMATCH(*ptr)) {
				POP();
			}
			else {
				if (*ptr == ')' || *ptr == ']' || ISFULL()) {
					done = 0;
					break;
				}
				PUSH(((int)*ptr) & MASK);
			}
			ptr++;
		}
		if (done && ISEMPTY()) {
			valid = 1;
		}
		if (valid) printf("Yes\n");
		else printf("No\n");
	}

	return 0;
}