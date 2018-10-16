#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int t;
double h, v0;
const double g = 9.80665;
int main() {
	for (scanf("%d", &t); t; t--) {
		scanf("%lf%lf", &h, &v0);
		double vt = sqrt(v0 * v0 + 2 * g * h);
		printf("%lf\n", (v0 * vt) / g);
	}
}