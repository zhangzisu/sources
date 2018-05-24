#include <algorithm>
#include <cctype>
#include <cstdio>
#define MAXN 200010
const int INF = 0x3F3F3F3F;
const long long INFLL = 0x3F3F3F3F3F3F3F3FLL;
int n, m, l, p[4], q[4], c[MAXN], b[MAXN], a[4][MAXN];
long long s, t;
int main() {
    scanf("%d%d%d", &n, &m, &l);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    for (int i = 0, k; i < 2; i++) {
        scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            int x;
            scanf("%d", &x);
            b[x] |= 1 << i;
        }
    }
    for (int i = 1; i <= n; i++)
        a[b[i]][p[b[i]]++] = c[i];
    for (int i = 0; i < 4; i++)
        std::sort(a[i], a[i] + p[i]), a[i][p[i]] = INF;
    s = INFLL, t = 0;
    for (q[1] = 0; q[1] < l && q[1] < p[1]; ++q[1])
        t += a[1][q[1]];
    for (q[2] = 0; q[2] < l && q[2] < p[2]; ++q[2])
        t += a[2][q[2]];
    while (q[0] + q[1] + q[2] < m && (q[0] < p[0] || q[1] < p[1] || q[2] < p[2])) {
        int i = 0;
        for (int j = 1; j < 3; ++j)
            if (q[j] < p[j] && a[i][q[i]] > a[j][q[j]])
                i = j;
        t += a[i][q[i]++];
    }
    if (q[1] >= l && q[2] >= l && q[0] + q[1] + q[2] == m)
        s = std::min(s, t);
    while (q[3] < p[3]) {
        t += a[3][q[3]++];
        int k = std::max(0, l - q[3]);
        if (q[0] < p[0])
            t += a[0][q[0]++];
        while (q[0] + q[1] + q[2] + q[3] > m && (q[0] > 0 || q[1] > k || q[2] > k)) {
            int i = 0;
            for (int j = 1; j < 3; ++j)
                if (q[j] > k && a[i][q[i] - 1] < a[j][q[j] - 1])
                    i = j;
            t -= a[i][--q[i]];
        }
        if (q[1] + q[3] >= l && q[2] + q[3] >= l && q[0] + q[1] + q[2] + q[3] == m)
            s = std::min(s, t);
    }
    printf("%lld\n", s < INFLL ? s : -1);
    return 0;
}