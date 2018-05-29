#include <cmath>
#include <cstdio>
#include <cstdlib>
int a, b;
int main() {
    scanf("%d%d", &a, &b);
    if (a == b) return puts("="), 0;
    if (a == 1) return puts("<"), 0;
    if (b == 1) return puts(">"), 0;
    long double x = log(a) * b;
    long double y = log(b) * a;
    if (std::abs(x - y) <= 1e-50) return puts("="), 0;
    return puts(x < y ? "<" : ">"), 0;
    return 0;
}