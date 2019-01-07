#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
auto f = []() { return rand() % 1500 - 900; };
int main() {
	srand(time(NULL));
	int n = 20;
	printf("%d\n", n);
	for (int i = 1; i <= n; i++) {
		int x = f(), y = f(), z = f();
		double R = 50. * rand() / RAND_MAX;
		double r = R * rand() / RAND_MAX;
		printf("%d %d %d %f %f\n", x, y, z, R, r);
	}
	return 0;
}