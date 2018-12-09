#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

inline unsigned fuckrand() {
	return (unsigned)rand() << 16 | rand();
}

int main() {
	int q = 2000;
	int k = 1000000000;
	srand(time(NULL));
	printf("%d %d\n", q, k);
	for (; q; q--) {
		switch (rand() % 3) {
			case 0:
				printf("1 %d %d\n", fuckrand() % k + 1, rand() % 1000 + 1);
				break;
			case 1:
				printf("2 %d %d\n", fuckrand() % k + 1, rand() % 1000 + 1);
				break;
			case 2:
				printf("3 %d\n", fuckrand() % k + 1);
				break;
		}
	}
}