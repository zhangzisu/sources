#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void addEdge(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int n, d[MAXN], f[MAXN], m;
inline bool check(const std::vector<int> &v, int mid) {
    int l = 0, r = v.size() - 1;
    while (l < r) {
        if (l == mid) l++;
        if (r == mid) r--;
        if (v[l] + v[r] > m) return 0;
        l++;
        r--;
    }
    return 1;
}
bool DP(int x, int fa) {
    std::vector<int> g;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa) {
            if (!DP(to[i], x)) return false;
            g.push_back(f[to[i]]);
        }
    if (g.empty()) {
        f[x] = 1;
        return true;
    }
    if (!(g.size() & 1)) g.push_back(0);
    std::sort(g.begin(), g.end());
    register int l = 0, r = g.size(), ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(g, mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    if (!~ans) return false;
    f[x] = g[ans] + 1;
    return 1;
}
int root = 0;
inline bool judge(int mid) {
    m = mid;
    if (!DP(root, 0)) return 0;
    return f[root] <= m + 1;
}
int main() {
    std::cin >> n;
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        addEdge(u, v);
        d[u]++;
        d[v]++;
    }
    for (int i = 1; i <= n; i++) m += d[i] & 1;
    for (int i = 1; i <= n; i++)
        if (d[i] == 1) {
            root = i;
            break;
        }
    std::cout << (m >>= 1) << ' ';
    register int l = 0, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (judge(mid))
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    std::cout << ans << std::endl;
    return 0;
}