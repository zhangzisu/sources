#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
typedef long long lnt;
int h[MAXN], c, n, m;
lnt f[MAXN];

int main() {
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= n; i++) scanf("%d", h + i), m = std::max(m, h[i]);
    memset(f, 0x3F, sizeof(f));
    f[0] = 0;
    //
    return 0;
}