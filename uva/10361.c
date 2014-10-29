#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char buf1[101], buf2[101], s1[101], s2[101], s3[101], s4[101], s5[101];
	char* dummy;

	int test;
	int i, j;
	int buflen1, buflen2;
	int nbytes;

	scanf("%d\n", &test);

	while(test--) {
		fgets (buf1, 101, stdin);
		fgets (buf2, 101, stdin);

		buflen1 = strlen(buf1);
		buflen2 = strlen(buf2);

		i = j = 0;

		while(buf1[i] != '<') {
			s1[j++] = buf1[i];
			i++;
		}
		s1[j] = 0;
		i++;

		j = 0;
		while(buf1[i] != '>') {
			s2[j++] = buf1[i];
			i++;
		}
		s2[j] = 0;
		i++;

		j = 0;
		while(buf1[i] != '<') {
			s3[j++] = buf1[i];
			i++;
		}
		s3[j] = 0;
		i++;

		j = 0;
		while(buf1[i] != '>') {
			s4[j++] = buf1[i];
			i++;
		}
		s4[j] = 0;
		i++;

		j = 0;
		while(i < buflen1) {
			s5[j++] = buf1[i];
			i ++;
		}
		s5[j] = 0;

		i = 0;
		while(buf2[i] != '.') i++;
		buf2[i] = 0;

		printf("%s%s%s%s%s", s1, s2, s3, s4, s5);
		printf("%s%s%s%s%s", buf2, s4, s3, s2, s5);
	}

	return 0;
}