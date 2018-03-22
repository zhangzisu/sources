#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
int n, a[MAXN], b[MAXN], c[MAXN], pfx[MAXN], ans, mask;

inline int cmp(int x, int y){return (b[x] & mask) <( b[y] & mask);}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for (int d = 0; d < 29; d++) {
        mask = (1 << d) - 1;
        for (int i = 1; i <= n; i++) c[i] = i;
        std::sort(c + 1, c + n + 1, cmp);
        int cnt = 0;
        memset(pfx, 0, sizeof(pfx));
        for (int i = 1; i <= n; i++) pfx[i] = pfx[i - 1] + ((b[c[i]] >> d) & 1);
        for (int i = 1; i <= n; i++) {
            int real = a[i] & mask;
            int l = 0, r = n, pos = n + 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if ((b[c[mid]] & mask) + real > mask)
                    pos = mid, r = mid - 1;
                else
                    l = mid + 1;
            }
            int count = pfx[pos - 1] + (n - pos + 1) - pfx[n] + pfx[pos - 1];
            if((a[i] >> d) & 1)count = n - count;
            cnt += count;
        }
        if (cnt & 1) ans |= (1 << d);
    }
    printf("%d\n", ans);
    return 0;
}