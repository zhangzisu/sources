#include <cstdio>
int n;
int main() {
	scanf("%d", &n);
	switch (n) {
		case 1:
			puts("1");
			puts("1");
			break;
		case 2:
			puts("1 2");
			puts("1 2");
			break;
		case 3:
			puts("1 3 2");
			puts("1 2 3");
			break;
		case 4:
			puts("2 1 4 3");
			puts("4 1 2 3");
			break;
		case 5:
			puts("2 1 4 5 3");
			puts("5 1 2 3 4");
			break;
		case 6:
			puts("2 3 1 5 6 4");
			puts("6 1 2 3 4 5");
			break;
		case 7:
			puts("2 3 1 5 6 7 4");
			puts("7 1 2 3 4 5 6");
			break;
	}
}