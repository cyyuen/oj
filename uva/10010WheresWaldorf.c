/**
 * Where's Waldorf?
 * Given a m by n grid of letters, (  $1 \leq m,n \leq 20$), and a list of words, find the location in the grid at which the word can be found. A word matches a straight, uninterrupted line of letters in the grid. A word can match the letters in the grid regardless of case (i.e. upper and lower case letters are to be treated as the same). The matching can be done in any of the eight directions either horizontally, vertically or diagonally through the grid.
 * Input
 *
 * The input begins with a single positive integer on a line by itself indicating the number of the cases following, each of them as described below. This line is followed by a blank line, and there is also a blank line between two consecutive inputs.
 * The input begins with a pair of integers, m followed by n,  $1 \leq
 * m,n \leq 50$ in decimal notation on a single line. The next m lines contain n letters each; this is the grid of letters in which the words of the list must be found. The letters in the grid may be in upper or lower case. Following the grid of letters, another integer k appears on a line by itself (  $1 \leq k \leq 20$). The next k lines of input contain the list of words to search for, one word per line. These words may contain upper and lower case letters only (no spaces, hyphens or other non-alphabetic characters).
 *
 * Output
 *
 * For each test case, the output must follow the description below. The outputs of two consecutive cases will be separated by a blank line.
 * For each word in the word list, a pair of integers representing the location of the corresponding word in the grid must be output. The integers must be separated by a single space. The first integer is the line in the grid where the first letter of the given word can be found (1 represents the topmost line in the grid, and m represents the bottommost line). The second integer is the column in the grid where the first letter of the given word can be found (1 represents the leftmost column in the grid, and n represents the rightmost column in the grid). If a word can be found more than once in the grid, then the location which is output should correspond to the uppermost occurence of the word (i.e. the occurence which places the first letter of the word closest to the top of the grid). If two or more words are uppermost, the output should correspond to the leftmost of these occurences. All words can be found at least once in the grid.
 *
 * Sample Input
 *
 * 1
 *
 * 8 11
 * abcDEFGhigg
 * hEbkWalDork
 * FtyAwaldORm
 * FtsimrLqsrc
 * byoArBeDeyv
 * Klcbqwikomk
 * strEBGadhrb
 * yUiqlxcnBjf
 * 4
 * Waldorf
 * Bambi
 * Betty
 * Dagbert
 *
 * Sample Output
 *
 * 2 5
 * 2 3
 * 1 2
 * 7 8
*/
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