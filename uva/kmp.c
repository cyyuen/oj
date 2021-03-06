#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

unsigned* kmp_init_failure(const char* pattern, size_t len) {

	unsigned* f = calloc(len, sizeof(unsigned));

	f[0] = 0;

	unsigned k = 0;

	for(int i = 1; i != len; ++i) {
		k = f[i-1];
		while(k != 0 && pattern[k] != pattern[i]) {
			k = f[k];
		}
		if (pattern[k] == pattern[i]) {
			f[i] = f[k] + 1;
		} else {
			f[i] = f[k];
		}
	}

	return f;
}

int kmp_find(const char* text, const char* pattern) {
	size_t len = strlen(pattern);

	unsigned* f = kmp_init_failure((const char*)pattern, len);

	assert(f != NULL);

	int i = 0, p = 0;

	while(text[i] != 0)
	{
		while(p != 0 && text[i] != pattern[p]) {
			p = f[p];
		}

		if (text[i] == pattern[p]) {
			p++;

			if (p == len) {
				return i - p + 1;
			}
		}

		i++;
	}

	return -1;
}

int main(int argc, char const *argv[])
{
	printf("1: %d\n", kmp_find("banbann", "ban"));
	return 0;
}