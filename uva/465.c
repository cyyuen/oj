/**
 *
 *  Overflow
 *
 * Write a program that reads an expression consisting of two non-negative integer and an operator. Determine if either integer or the result of the expression is too large to be represented as a ``normal'' signed integer (type integer if you are working Pascal, type int if you are working in C).
 *
 * Input
 *
 * An unspecified number of lines. Each line will contain an integer, one of the two operators + or *, and another integer.
 *
 * Output
 *
 * For each line of input, print the input followed by 0-3 lines containing as many of these three messages as are appropriate: ``first number too big'', ``second number too big'', ``result too big''.
 *
 * Sample Input
 *
 * 300 + 3
 * 9999999999999999999999 + 11
 * Sample Output
 *
 * 300 + 3
 * 9999999999999999999999 + 11
 * first number too big
 * result too big
 *
 * Solution
 *
 * Use uint64_t to do test simplified this question
 *
 * Traps:
 *	a * b is not necessary larger then a + b. (think when a = 1)
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_INT 2147483647

uint64_t str2uint64(const char* str) {
	size_t len = strlen(str);
	uint64_t tmp = 0;
	int i;
	for (i = 0; i < len; ++i)
	{
		tmp = tmp * 10 + str[i] - '0';
	}
	return tmp;
}

int main()
{
    char s1[300],s2[300],c;
    bool oppend2big;
    uint64_t x,y;
    while(scanf("%s %c %s",s1,&c,s2)!=EOF)
    {
    	oppend2big = false;

        printf("%s %c %s\n",s1,c,s2);
        x = str2uint64(s1);
        y = str2uint64(s2);

        if(x > MAX_INT) {
        	oppend2big = true;
        	printf("first number too big\n");
        }

        if(y > MAX_INT) {
        	oppend2big = true;
        	printf("second number too big\n");
        }

        switch(c) {
        	case '+':
        		if (x + y > MAX_INT)
        			printf("result too big\n");
        		break;
        	default:
        		if (x * y > MAX_INT)
        			printf("result too big\n");
        }
    }
    return 0;
}