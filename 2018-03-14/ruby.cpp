#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define MAXN 500010
#define MOD 1000000007

int n, m, x, y, k, b;
std::vector<int> next[MAXN];
int w[MAXN], Q[MAXN], H, T;
int pos[MAXN], f[MAXN], first[MAXN], last[MAXN];
struct Tag {
    long long m, next, s;
} t[MAXN << 2];
void Build(int x, int l, int r) {
    t[x].m = 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    Build(x << 1, l, mid);
    Build(x << 1 | 1, mid + 1, r);
}
void maintain(int x, int y) {
    t[x].next = t[x].next * y % MOD;
    t[x].m = t[x].m * y % MOD;
    t[x].s = t[x].s * y % MOD;
}
void calc(int x, int l, int r, int y) {
    t[x].next = (t[x].next + y) % MOD;
    t[x].s = (t[x].s + y * (r - l + 1LL)) % MOD;
}
void pushDown(int x, int l, int r) {
    if (l == r) return;
    maintain(x << 1, t[x].m);
    maintain(x << 1 | 1, t[x].m);
    int mid = (l + r) >> 1;
    calc(x << 1, l, mid, t[x].next);
    calc(x << 1 | 1, mid + 1, r, t[x].next);
    t[x].m = 1, t[x].next = 0;
}
void Modify(int x, int l, int r, int L, int R, int k, int b) {
    pushDown(x, l, r);
    if (l == L && r == R) return maintain(x, k), calc(x, l, r, b);
    int mid = (l + r) >> 1;
    if (R <= mid)
        Modify(x << 1, l, mid, L, R, k, b);
    else if (L > mid)
        Modify(x << 1 | 1, mid + 1, r, L, R, k, b);
    else
        Modify(x << 1, l, mid, L, mid, k, b), Modify(x << 1 | 1, mid + 1, r, mid + 1, R, k, b);
    t[x].s = (t[x << 1].s + t[x << 1 | 1].s) % MOD;
    return;
}
int Query(int x, int l, int r, int L, int R) {
    pushDown(x, l, r);
    if (l == L && r == R) return t[x].s;
    int mid = (l + r) >> 1;
    if (R <= mid)
        return Query(x << 1, l, mid, L, R);
    else if (L > mid)
        return Query(x << 1 | 1, mid + 1, r, L, R);
    else
        return (Query(x << 1, l, mid, L, mid) + Query(x << 1 | 1, mid + 1, r, mid + 1, R)) % MOD;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        next[x].push_back(y);
        next[y].push_back(x);
    }
    pos[Q[H = T = 0] = 1] = 0;
    while (H <= T) {
        int u = Q[H++];
        first[u] = T + 1;
        for (int _i = 0; _i < (int)next[u].size(); _i++) {
            int i = next[u][_i];
            if (i == f[u])continue;
            f[Q[T++] = i] = u, pos[i] = T;
        }
        last[u] = T;
    }
    Build(1, 0, n - 1);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &k, &b);
        long long ans = 0;
        if (f[x] > 0) {
            Modify(1, 0, n - 1, pos[f[x]], pos[f[x]], k, b);
            ans += Query(1, 0, n - 1, pos[f[x]], pos[f[x]]);
        }
        Modify(1, 0, n - 1, pos[x], pos[x], k, b);
        ans += Query(1, 0, n - 1, pos[x], pos[x]);
        if (first[x] <= last[x]) {
            Modify(1, 0, n - 1, first[x], last[x], k, b);
            ans += Query(1, 0, n - 1, first[x], last[x]);
        }
        ans %= MOD;
        printf("%lld\n", ans);
    }
    return 0;
}