#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
long long n, a[MAXN], ddd, X, Y, max;
inline void halt() {
    puts("NO");
    exit(0);
}

int main() {
    scanf("%lld%lld", &n, &a[1]);
    for (long long i = 2; i <= n; i++) {
        scanf("%lld", &a[i]);
        long long delta = std::abs(a[i] - a[i - 1]);
        if (!delta) halt();
        if (delta > 1) {
            if (!ddd)
                ddd = delta;
            else if (ddd != delta)
                halt();
        }
    }

    if (!ddd) {
        for (long long i = 1; i <= n; i++) ddd = std::max(ddd, a[i]);
    }

    X = (a[1] - 1) % ddd + 1;
    Y = (a[1] - 1) / ddd + 1;
    if(X <= 0 || X > ddd)halt();
    if(Y <= 0)halt();
    max = std::max(max, Y);
    for (long long i = 2; i <= n; i++) {
        long long delta = (a[i] - a[i - 1]);
        if (delta >= -1 && delta <= 1) {
            if (!delta) halt();
            X += delta;
            if (X <= 0 || X > ddd) halt();
        } else {
            if (ddd != std::abs(delta)) halt();
            if (delta < 0)
                Y--;
            else
                Y++;
            if (Y <= 0) halt();
        }
        max = std::max(max, Y);
    }
    if (max >= 1000000000) halt();
    if (ddd >= 1000000000) halt();
    puts("YES");
    printf("%lld %lld\n", max, ddd);
    return 0;
}