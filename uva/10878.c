/**
 * Your boss has just unearthed a roll of old computer tapes. The tapes have holes in them and might contain some sort of useful information. It falls to you to figure out what is written on them.
 *
 * Input
 * The input will contain one tape.
 *
 * Output
 * Output the message that is written on the tape.
 *
 * Sample Input	Sample Output
 * ___________
 * | o   .  o|		A quick brown fox jumps over the lazy dog.
 * |  o  .   |
 * | ooo .  o|
 * | ooo .o o|
 * | oo o.  o|
 * | oo  . oo|
 * | oo o. oo|
 * |  o  .   |
 * | oo  . o |
 * | ooo . o |
 * | oo o.ooo|
 * | ooo .ooo|
 * | oo o.oo |
 * |  o  .   |
 * | oo  .oo |
 * | oo o.ooo|
 * | oooo.   |
 * |  o  .   |
 * | oo o. o |
 * | ooo .o o|
 * | oo o.o o|
 * | ooo .   |
 * | ooo . oo|
 * |  o  .   |
 * | oo o.ooo|
 * | ooo .oo |
 * | oo  .o o|
 * | ooo . o |
 * |  o  .   |
 * | ooo .o  |
 * | oo o.   |
 * | oo  .o o|
 * |  o  .   |
 * | oo o.o  |
 * | oo  .  o|
 * | oooo. o |
 * | oooo.  o|
 * |  o  .   |
 * | oo  .o  |
 * | oo o.ooo|
 * | oo  .ooo|
 * |  o o.oo |
 * |    o. o |
 * ___________
 *
 * This is trivial. convert the 'o' to 1 and ' ' to 0 and convert the whole binary number to ascii code.
 *
 * Trape:
 *	1. No '\n' needed. The tape has newline
 *	2. '_______' doesn't means the end. There might be multiple tapes.
 */
#include <stdio.h>

#define MAX_N 20

int main(int argc, char const *argv[])
{
	int i, base;
	char buf[MAX_N];
	fgets(buf, MAX_N, stdin);
	while(fgets(buf, MAX_N, stdin)) {

		if (buf[0] != '|') continue;

		i = 0;
		base = 0;

		while(buf[i] != 0) {

			if (buf[i] == 'o')
				base = base * 2 + 1;
			else if (buf[i] == ' ')
				base = base * 2;

			i++;
		}

		printf("%c", base);
	}
	return 0;
}