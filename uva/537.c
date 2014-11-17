#include <stdio.h>
#include <stdlib.h>

#define STATE_TRUE '1'
#define STATE_FALSE '0'
#define STATE_NOT_FOUND -1
#define MAX_BUF 1000

const char* hashtbl = "IUP=0123456789.WVAmkM";

const char* sol = "IUP";
const char* unit = "AVW";

char statemap[21][21] = {
	{'0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
	{'0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
	{'0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','0','0','0','0','0','0','0'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
	{'0','0','0','0','1','1','1','1','1','1','1','1','1','1','0','0','0','0','0','0','0'},
	{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
	{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
	{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
	{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','0'},
	{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','0'},
	{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','0'}
};

const char termianls[] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','0','0'};
char starters[] = {'1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};

int state_hash(char state) {
	int i = 0;
	while(hashtbl[i] != 0) {
		if (state == hashtbl[i])
			return i;
		i++;
	}
	return STATE_NOT_FOUND;
}

int record2idx(int record) {
	switch(record) {
		case 1: return 0;
		case 2: return 1;
		case 4: return 2;
	}
	return -1;
}

int idx2record(int idx) {
	switch(idx) {
		case 0: return 1;
		case 1: return 2;
		case 2: return 4;
	}
	return -1;
}

int set_record(int record, int idx) {
	return record | idx2record(idx);
}

int remain_record(int record) {
	return record2idx(7 - record);
}

int num_record(int record) {
	switch(record) {
		case 0: return 0;
		case 1:
		case 2:
		case 4: return 1;
		case 3:
		case 5:
		case 6: return 2;
		case 7: return 3;
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	int t;
	int i;
	char buf[MAX_BUF];
	scanf("%d\n", &t);
	for (i=1; i <= t; ++i) {
		float var[] = {0, 0, 0};
		int sp = -1;
		int is_match = 0;
		int record = 0;

		fgets(buf, MAX_BUF, stdin);
		char* current_state;

		int j = 0;
		int stat_idx;
		int var_idx = -1;
		char num_buf[MAX_BUF];
		int num_buf_idx = 0;
		float base = 1;
		while(buf[j] != 0 && num_record(record) != 2) {
			if (sp == -1) {
				current_state = starters;
			} else {
				current_state = statemap[sp];
			}
			stat_idx = state_hash(buf[j]);
			if (stat_idx == STATE_NOT_FOUND || current_state[stat_idx] == STATE_FALSE) {
				if (var_idx != -1) {
					var[var_idx] = 0;
				}
				var_idx = -1;
				sp = -1;
				num_buf[0] = 0;
				num_buf_idx = 0;
				base = 1;
			} else {

				if (stat_idx <= 2) {
					var_idx = stat_idx;
				}

				else if (stat_idx > 3 && stat_idx < 15) {
					num_buf[num_buf_idx++] = buf[j];
				}

				else if (stat_idx > 17 && stat_idx < 21) {
					switch(stat_idx) {
						case 18: base = 0.001; break;
						case 19: base = 1000; break;
						case 20: base = 1000000; break;
					}
				}
				else if (termianls[stat_idx] == STATE_TRUE) {
					if (unit[var_idx] == buf[j]) {
						num_buf[num_buf_idx] = 0;
						var[var_idx] = atof(num_buf) * base;
						record = set_record(record, var_idx);
					}

					var_idx = -1;
					sp = -1;
					num_buf[0] = 0;
					num_buf_idx = 0;
					base = 1;
					continue;
				}
				sp = stat_idx;
			}
			j++;
		}

		int remain_idx = remain_record(record);

		float val = 0;

		switch(remain_idx) {
			case 0:
				val = var[2] / var[1];
				break;
			case 1:
				val = var[2] / var[0];
				break;
			case 2:
				val = var[0] * var[1];
				break;
		}

		printf("Problem #%d\n", i);
		printf("%c=%.2f%c\n", sol[remain_idx], val, unit[remain_idx]);
		printf("\n");
	}
	return 0;
}