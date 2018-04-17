#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200010
int n, m, ans[MAXN];
std::pair<int, int> x[MAXN];
int main() {
    scanf("%d", &n);
    m = n / 2;
    for (int i = 1; i <= n; i++) scanf("%d", &x[i].first), x[i].second = i;
    std::sort(x + 1, x + n + 1);
    for (int i = 1; i <= n; i++) {
        if (i > m)
            ans[x[i].second] = x[m].first;
        else
            ans[x[i].second] = x[n - m + 1].first;
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}