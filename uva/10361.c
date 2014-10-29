/**
 * Uva 10361	Automatic Poetry
 * Running Time: 0.015
 *
 * author: cyyuen (colsy2@gmail.com)
 * date: 2014.10.29
 *
 *
 * Q & A:
 * 1. why don't use strtok().
 *		since strtok would ignore empty string.
 *		ex. abcd <> sdk
 *		I want to spilt the string using < and >, the results would be "abcd " and " sdk" using strtok
 *		However, what I need is "abcd ", "" (an empty string) and " sdk"
 */
#include <stdio.h>
#include <string.h>

const char* _strfetch_pointer;

char* strfetch(const char* s, const char deliminater)
{
	if (s != NULL) {
		_strfetch_pointer = s;
	}
	
	int len = strlen(_strfetch_pointer);

	char* c = malloc(sizeof(char) * (len+1));

	int i = 0;

	while (*_strfetch_pointer != deliminater && _strfetch_pointer != NULL) {

		c[i++] = *_strfetch_pointer;

		_strfetch_pointer++;
	}
	c[i] = 0;
	_strfetch_pointer++;

	return c;
}

int main(int argc, char const *argv[])
{
	char buf1[101], buf2[101], *s1, *s2, *s3, *s4, *s5;

	int test;
	int i;
	int buflen1, buflen2;
	int nbytes;

	scanf("%d\n", &test);

	while(test--) {
		fgets (buf1, 101, stdin);
		fgets (buf2, 101, stdin);

		buflen2 = strlen(buf2);

		s1 = strfetch(buf1, '<');
		s2 = strfetch(NULL, '>');
		s3 = strfetch(NULL, '<');
		s4 = strfetch(NULL, '>');
		s5 = strfetch(NULL, '\n');

		i = 0;
		while(buf2[i] != '.') i++;
		buf2[i] = 0;

		printf("%s%s%s%s%s\n", s1, s2, s3, s4, s5);
		printf("%s%s%s%s%s\n", buf2, s4, s3, s2, s5);
	}

	return 0;
}