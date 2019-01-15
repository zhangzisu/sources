#pragma GCC optimize(0)
#include <cstdint>
#include <cstdio>
#include <cstdlib>

void dummy_function(int a, int b, int c) {
	printf("Callee %d %d %d\n", &a, &b, &c);
}

int main(void) {
	int test;
	dummy_function(1, 2, 3);
	printf("OUTER %zd\n", &test);
	return 0;
}