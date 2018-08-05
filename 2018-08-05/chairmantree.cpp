#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, k, a[MAXN], b[MAXN], c[MAXN];
long long g;
int main() {
    scanf("%d%d%lld", &n, &k, &g);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    memcpy(b, a, sizeof(b));
    std::sort(b + 1, b + n + 1);
    m = std::unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + m + 1, a[i]) - b;
    register int l = 1, r = m, ans = -1, mid;
    long long tot;
    while (l <= r) {
        mid = (l + r) >> 1;
        tot = 0;
        for (int i = 1; i <= n; i++) c[i] = c[i - 1] + (a[i] < mid);
        for (int i = 1, j = 0; i <= n; i++) {
            for (; j < n && (c[j + 1] - c[i - 1]) < k;) j++;
            if (j - i + 1 >= k) tot += j - i - k + 2;
        }
        if (tot >= g) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", (~ans ? b[ans] : b[m]));
    return 0;
}