#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
#define MAXN 1000010
int pri[MAXN], vis[MAXN], pnt = 0;
inline void shai() {
    for (int i = 2; i < MAXN; i++) {
        if (!vis[i]) pri[++pnt] = i;
        for (int j = 1; j <= pnt; j++) {
            if (i * pri[j] >= MAXN) break;
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
}
int sum[MAXN << 2];
inline void add(int n, int l, int r, int p) {
    while (l < r) {
        sum[n]++;
        int mid = (l + r) >> 1;
        if (p <= mid) {
            r = mid;
            n = n << 1;
        } else {
            l = mid + 1;
            n = n << 1 | 1;
        }
    }
    sum[n]++;
}
inline int find(int n, int l, int r) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (sum[n << 1] == mid - l + 1) {
            l = mid + 1;
            n = n << 1 | 1;
        } else {
            r = mid;
            n = n << 1;
        }
    }
    return l;
}
inline int find(int n, int l, int r, int L, int R, int kth) {
    if (l == L && r == R && r - l + 1 - sum[n] < kth) return -(r - l + 1 - sum[n]);
    if (l == r) return l;
    int mid = (l + r) >> 1;
    if (R <= mid) return find(n << 1, l, mid, L, R, kth);
    if (L > mid) return find(n << 1 | 1, mid + 1, r, L, R, kth);
    int x = find(n << 1, l, mid, L, mid, kth);
    if (x > 0) return x;
    int y = find(n << 1 | 1, mid + 1, r, mid + 1, R, kth + x);
    if (y > 0) return y;
    return x + y;
}
int t, n, k;
int main() {
    freopen("harbin.in", "r", stdin);
    freopen("harbin.out", "w", stdout);
    shai();
    for (scanf("%d", &t); t; t--) {
        scanf("%d%d", &n, &k);
        register int p = *std::lower_bound(pri + 1, pri + pnt + 1, n);
        register int ans = 0;
        if (k >= n) {
            for (int i = 0, t = 1; i < n; i++, t = 1LL * t * p % MOD) up(ans, 1LL * i * t % MOD);
        } else {
            memset(sum, 0, sizeof(sum));
            for (register int t = 1; sum[1] < n; t = 1LL * t * p % MOD) {
                register int cur = (n - sum[1] + k - 1) / k;
                register int x = find(1, 0, n - 1);
                up(ans, 1LL * x * t % MOD);
                add(1, 0, n - 1, x);
                for (register int j = 1; j < cur; j++) {
                    x = find(1, 0, n - 1, x + 1, n - 1, k);
                    t = 1LL * t * p % MOD;
                    up(ans, 1LL * x * t % MOD);
                    add(1, 0, n - 1, x);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}