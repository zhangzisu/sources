#include <algorithm>
#include <cstdio>
long long a, b, c;
int main() {
	scanf("%lld%lld%lld", &a, &b, &c);
	printf("%lld\n", std::min(a + b + 1, c) + b);
	return 0;
}