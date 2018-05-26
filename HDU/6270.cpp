#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 998244353
#define MAXN 100010
int n, a[MAXN], b[MAXN], c[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        c[i] = std::min(a[i], b[i]);
        if (!c[i]) i--, n--;
    }
    if (!n) return puts("0"), 0;
    //
    return 0;
}