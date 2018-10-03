#include <cstdio>
#include <cstdlib>
#include <cstring>

FILE *userout = fopen("userout", "r");
FILE *output = fopen("output", "r");
char buf0[1 << 25], buf1[1 << 25];

int main() {
	int token = 0;
	while (true) {
		++token;
		int u = fscanf(userout, "%s", buf0);
		int o = fscanf(output, "%s", buf1);
		if (u == -1 && o == -1) break;
		if (u == -1) {
			printf("Output too short\n");
			return 1;
		}
		if (o == -1) {
			printf("Output too long\n");
			return 1;
		}
		if (strcmp(buf0, buf1)) {
			printf("Wrong answer on token %d\n", token);
			return 1;
		}
	}
	return 0;
}