#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int enc, n, m, q, a[MAXN];
struct trans {
    int a, b;
    inline trans(int a = 0, int b = 0) : a(a), b(b) {}
    inline friend trans operator+(trans a, trans b) {
        return trans(a.a * b.a, a.b * b.a + b.b);
    }
};

int main() {
    scanf("%d%d%d", &enc, &n, &m);
    enc &= 1;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    return 0;
}