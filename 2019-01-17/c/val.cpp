#include <cassert>
#include <cstdio>
int a[1000000];
int main() {
	int n = 1454;
	for (int i = 1; i <= 2 * n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= 2 * n; i++) {
		if (a[a[i]] != i) {
			printf("a[ %d ] = %d != %d\n", a[i], a[a[i]], i);
		}
	}
}