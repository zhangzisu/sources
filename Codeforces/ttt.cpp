#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 200100
#define INF 0x3F3F3F3F
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
int head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
int dis[MAXN], vis[MAXN], da[MAXN], pa[MAXN], size[MAXN], ansX, ansY, ans, lim;
int N, T, L, R, n, root, Q[MAXN], deep[MAXN], last[MAXN], P[MAXN], F[MAXN];
void $(int k, int x, int y) {
    next[++tot] = head[x], to[tot] = y, val[tot] = k, head[x] = tot;
    next[++tot] = head[y], to[tot] = x, val[tot] = k, head[y] = tot;
    if (k > lim) lim = k;
}
void $(int x, int fa) {
    size[x] = F[x] = 1;
    for (int k = head[x]; k; k = next[k])
        if (!vis[to[k]] && to[k] != fa) {
            $(to[k], x);
            size[x] += size[to[k]];
            if (size[to[k]] > F[x]) F[x] = size[to[k]];
        }
    if (N - size[x] > F[x]) F[x] = N - size[x];
    if (F[x] <= F[root]) root = x;
}
bool calc(int root, int v) {
    int now, top = 0;
    pa[0] = root;
    for (int j = head[root], l, r; j; j = next[j])
        if (!vis[to[j]]) {
            dis[to[j]] = val[j] < v ? -1 : 1;
            last[Q[l = r = deep[Q[1] = to[j]] = 1]] = ++T;
            for (; l <= r; l++)
                for (int k = head[Q[l]]; k; k = next[k])
                    if (!vis[to[k]] && last[to[k]] < T) {
                        Q[++r] = to[k];
                        dis[to[k]] = dis[Q[l]] + (val[k] >= v ? 1 : -1);
                        deep[to[k]] = deep[Q[l]] + 1;
                        last[to[k]] = T;
                    }
            int _T = r;
            l = 1, r = 0;
            now = top;
            for (int i = 1; i <= _T; i++) {
                while (now >= 0 && deep[Q[i]] + now >= L) {
                    while (l <= r && da[P[r]] < da[now]) r--;
                    P[++r] = now--;
                }
                while (l <= r && P[l] + deep[Q[i]] > R) l++;
                if (l <= r && dis[Q[i]] + da[P[l]] >= 0) {
                    ansX = Q[i];
                    ansY = pa[P[l]];
                    return 1;
                }
            }
            for (int i = top + 1; i <= deep[Q[_T]]; i++) da[i] = -INF;
            for (int i = 1; i <= _T; i++)
                if (dis[Q[i]] > da[deep[Q[i]]]) {
                    da[deep[Q[i]]] = dis[Q[i]];
                    pa[deep[Q[i]]] = Q[i];
                }
            if (deep[Q[_T]] > top) top = deep[Q[_T]];
        }
    return 0;
}
void solve(int x) {
    int l = ans, r = lim;
    vis[x] = 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (calc(x, mid))
            ans = mid, l = mid + 1;
        else
            r = mid - 1;
    }
    for (int i = head[x]; i; i = next[i])
        if (!vis[to[i]]) {
            root = 0, N = size[to[i]];
            $(to[i], 0);
            if (size[to[i]] > L) solve(root);
        }
}
int main() {
    n = $(), L = $(), R = $();
    F[0] = n + 1, N = n;
    for (int i = 1; i < n; i++) $($(), $(), $());
    $(1, 0), solve(root);
    printf("%d %d\n", ansX, ansY);
    return 0;
}