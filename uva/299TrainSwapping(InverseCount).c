/**
 * Train Swapping
 *
 * At an old railway station, you may still encounter one of the last remaining ``train swappers''. A train swapper is an employee of the railroad, whose sole job it is to rearrange the carriages of trains.
 *
 * Once the carriages are arranged in the optimal order, all the train driver has to do, is drop the carriages off, one by one, at the stations for which the load is meant.
 *
 * The title ``train swapper'' stems from the first person who performed this task, at a station close to a railway bridge. Instead of opening up vertically, the bridge rotated around a pillar in the center of the river. After rotating the bridge 90 degrees, boats could pass left or right.
 *
 * The first train swapper had discovered that the bridge could be operated with at most two carriages on it. By rotating the bridge 180 degrees, the carriages switched place, allowing him to rearrange the carriages (as a side effect, the carriages then faced the opposite direction, but train carriages can move either way, so who cares).
 *
 * Now that almost all train swappers have died out, the railway company would like to automate their operation. Part of the program to be developed, is a routine which decides for a given train the least number of swaps of two adjacent carriages necessary to order the train. Your assignment is to create that routine.
 *
 * Input Specification
 *
 * The input contains on the first line the number of test cases (N). Each test case consists of two input lines. The first line of a test case contains an integer L, determining the length of the train ( L <= 50 ). The second line of a test case contains a permutation of the numbers 1 through L, indicating the current order of the carriages. The carriages should be ordered such that carriage 1 comes first, then 2, etc. with carriage L coming last.
 *
 * Output Specification
 *
 * For each test case output the sentence: 'Optimal train swapping takes S swaps.' where S is an integer.
 *
 * Example Input
 *
 * 3
 * 3
 * 1 3 2
 * 4
 * 4 3 2 1
 * 2
 * 2 1
 * Example Output
 *
 * Optimal train swapping takes 1 swaps.
 * Optimal train swapping takes 6 swaps.
 * Optimal train swapping takes 1 swaps.
 *
 * Solution:
 *	Reduce to inversion counting problem
 *
 * Traps:
 *	L may be 0!!!!!!!!!!!! Be careful!
 */

#include <stdio.h>

#define N 100

unsigned arr[N];
unsigned buffer[N];

unsigned count_inversion(unsigned start, unsigned end)
{

	if (start >= end) {
		return 0;
	}

	unsigned mid = (start + end) / 2;
	unsigned lhs_count = count_inversion(start, mid);
	unsigned rhs_count = count_inversion(mid+1, end);
	unsigned cross_count = 0;

	unsigned i = start, j = mid + 1, k = start, base = 0;

	while (k <= end){

		if (j > end && i <= mid) {
			while (i<=mid){
				buffer[k] = arr[i];
				cross_count += (j - mid - 1);
				k++;
				i++;
			}
			break;
		}

		else if (i > mid && j <= end) {
			while (j <= end){
				buffer[k] = arr[j];
				k++;
				j++;
			}
			break;
		}
		else if (arr[i] < arr[j]) {
			buffer[k] = arr[i];
			cross_count += (j - mid - 1);
			i++;
		} else {
			buffer[k] = arr[j];
			j++;
		}
		k++;
	}

	unsigned z;

	for (z = start; z <= end; z++) {
		arr[z] = buffer[z];
	}

	return lhs_count + rhs_count + cross_count;
}

int main(int argc, char const *argv[])
{
	int numOfTest, numOfTrain, i;

	scanf("%d\n", &numOfTest);

	while(numOfTest--) {
		scanf("%d\n", &numOfTrain);

		for (i = 0; i < numOfTrain; ++i)
		{
			scanf("%d", &arr[i]);
		}

		unsigned c = 0;

		if (numOfTrain) {
			c = count_inversion(0, numOfTrain-1);
		}

		printf("Optimal train swapping takes %u swaps.\n", c);
	}

	return 0;
}
