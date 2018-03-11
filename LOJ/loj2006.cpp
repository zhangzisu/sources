#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#define MAXN 300
int head[MAXN], to[90000], next[90000], val[90000], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
}
int n, m, k, vis[MAXN], match[MAXN], tim, lmt;
std::vector<int> V;
bool hgr(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (vis[to[i]] == tim || val[i] > lmt) continue;
        vis[to[i]] = tim;
        if (!~match[to[i]] || hgr(match[to[i]])) {
            match[to[i]] = x;
            return 1;
        }
    }
    return 0;
}
inline bool judge(int mid) {
    memset(match, -1, sizeof(match));
    lmt = mid;
    register int ans = 0;
    for (int i = 1; i <= n; i++) {
        ++tim;
        if (hgr(i)) ans++;
    }
    return ans >= n - k + 1;
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            scanf("%d", &x);
            $(i, j, x);
            V.push_back(x);
        }
    }
    std::sort(V.begin(), V.end());
    register int l = 0, r = V.size() - 1, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (judge(V[mid]))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%d\n", V[ans]);
    return 0;
}