#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, a[MAXN], b[MAXN], c[MAXN], count[10], ans;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int i = 1; i <= n; i++) c[i] = (b[i] - a[i] + 4) % 4;
    for (int i = n; i >= 1; i--) c[i] -= c[i - 1];
    for (int i = 1; i <= n; i++) ans += std::max(c[i], 0);
    for (int i = 1; i <= n; i++) {
        if (c[i] > 0) {
            if (c[i] == 3) {
                if (count[1])
                    ans -= 2, count[1]--;
                else if (count[2])
                    ans--, count[2]--;
            } else if (c[i] == 2) {
                if (count[1]) ans--, count[1]--;
            }
        } else {
            count[c[i] + 4]++;
        }
    }
    printf("%d\n", ans);
    return 0;
}