#include <stdio.h>
#include <string.h>

const char* reversed = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";

const int numbase = 'Z' - 'A' + 1;

const char* fmt_regular = "%s -- is not a palindrome.\n\n";
const char* fmt_palindrom = "%s -- is a regular palindrome.\n\n";
const char* fmt_mirror = "%s -- is a mirrored string.\n\n";
const char* fmt_palindrom_mirror = "%s -- is a mirrored palindrome.\n\n";

int idx(const char c)
{
	if ( 'A' <= c && c <= 'Z') {
		return c - 'A';
	} else {
		return c - '1' + numbase;
	}
}

int main(int argc, char const *argv[])
{
	int is_palin, is_mirror;

	char buffer[21];

	while(scanf("%s", buffer) > 0) {
		int len = strlen(buffer);

		int i = 0, j = len - 1;
		is_palin = is_mirror = 1;

		while (i <= j) {

			if (buffer[i] != buffer[j]) {
				is_palin = 0;
			}

			if (reversed[idx(buffer[j])] == ' ' || buffer[i] != reversed[idx(buffer[j])]) {
				is_mirror = 0;
			}

			if (!is_palin && !is_mirror) {
				break;
			}

			i++; 
			j--;
		}

		if (is_palin && is_mirror) {
			printf(fmt_palindrom_mirror, buffer);
		} else if (is_palin) {
			printf(fmt_palindrom, buffer);
		} else if (is_mirror) {
			printf(fmt_mirror, buffer);
		} else {
			printf(fmt_regular, buffer);
		}
	}

	return 0;
}