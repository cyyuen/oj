#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int maxn = 50;
const int maxm = 51;

int eq(char grid[maxn][maxm], const char* s, int len, int i, int j);

void strtolower(char* s, int len) {
	int i;
	for (i = 0; i != len; ++i) {
		s[i] = tolower(s[i]);
	}
}

int main(int argc, char const *argv[])
{
	int tests, m, n;
	int subtests;
	char subbuf[maxm];
	int buflen;
	int i, j;
	char grid[maxn][maxm];

	scanf("%d", &tests);

	while (tests--) {
		
		scanf("%d %d", &n, &m);

		for (i = 0; i != n; ++i) {
			scanf("%s", grid[i]);

			strtolower(grid[i], m);
		}
		
		scanf("%d", &subtests);

		int brk = 0;

		while(subtests--) {
			scanf("%s", subbuf);

			buflen = strlen(subbuf);

			strtolower(subbuf, buflen);

			brk = 0;

			for (i = 0; i != n; ++i) {
				for (j = 0; j != m; ++j) {
					if (eq(grid, subbuf, buflen, i, j)) {
						brk = 1;
						break;
					}
				}
				if (brk) {
					break;
				}
			}

			printf("%d %d\n", i + 1, j + 1);
		}

		if (tests) {
			printf("\n");
		}
	}
	return 0;
}

int backward_eq(char grid[maxn][maxm], const char* s, int len, int i, int j)
{
	if (j + len > maxm) {
		return 0;
	}
	int k;
	for (k = 0; k != len; ++k) {
		if (s[k] != grid[i][j+k]) {
			return 0;
		}
	}
	return 1;
}

int forward_eq(char grid[maxn][maxm], const char* s, int len, int i, int j) 
{
	if (j - len < -1) {
		return 0;
	}
	int k;
	for (k = 0; k != len; ++k) {
		if (s[k] != grid[i][j-k]) {
			return 0;
		}
	}
	return 1;
}

int upward_eq(char grid[maxn][maxm], const char* s, int len, int i, int j)
{
	if (i - len < -1) {
		return 0;
	}
	int k;
	for (k = 0; k != len; ++k) {
		if (s[k] != grid[i-k][j]) {
			return 0;
		}
	}
	return 1;
}

int downward_eq(char grid[maxn][maxm], const char* s, int len, int i, int j)
{
	if (i + len > maxn + 1) {
		return 0;
	}
	int k;
	for (k = 0; k != len; ++k) {
		if (s[k] != grid[i+k][j]) {
			return 0;
		}
	}
	return 1;
}

int backup_eq(char grid[maxn][maxm], const char* s, int len, int i, int j)
{
	if (i - len < -1) {
		return 0;
	}
	if (j + len > maxm) {
		return 0;
	}
	int k;
	for (k = 0; k != len; ++k) {
		if (s[k] != grid[i-k][j+k]) {
			return 0;
		}
	}
	return 1;
}

int forup_eq(char grid[maxn][maxm], const char* s, int len, int i, int j)
{
	if (i - len < -1) {
		return 0;
	}
	if (j - len < -1) {
		return 0;
	}
	int k;
	for (k = 0; k != len; ++k) {
		if (s[k] != grid[i-k][j-k]) {
			return 0;
		}
	}
	return 1;
}

int backdown_eq(char grid[maxn][maxm], const char* s, int len, int i, int j)
{
	if (i + len > maxn + 1) {
		return 0;
	}
	if (j + len > maxm) {
		return 0;
	}
	int k;
	for (k = 0; k != len; ++k) {
		if (s[k] != grid[i+k][j+k]) {
			return 0;
		}
	}
	return 1;
}

int fordown_eq(char grid[maxn][maxm], const char* s, int len, int i, int j)
{
	if (i + len > maxn + 1) {
		return 0;
	}
	if (j - len < -1) {
		return 0;
	}
	int k;
	for (k = 0; k != len; ++k) {
		if (s[k] != grid[i+k][j-k]) {
			return 0;
		}
	}
	return 1;
}

int eq(char grid[maxn][maxm], const char* s, int len, int i, int j) {
	return forward_eq(grid, s, len, i, j)
		   || backward_eq(grid, s, len, i, j)
		   || upward_eq(grid, s, len, i, j)
		   || downward_eq(grid, s, len, i, j)
		   || forup_eq(grid, s, len, i, j)
		   || fordown_eq(grid, s, len, i, j)
		   || backup_eq(grid, s, len, i, j)
		   || backdown_eq(grid, s, len, i, j);
}