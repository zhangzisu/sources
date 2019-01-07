#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 2000010
#define MOD 1000000007
int n, head[MAXN], to[MAXN << 2], next[MAXN << 2], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
std::pair<int, int> d[MAXN], Q[MAXN];
int col[MAXN], ans = 1;
void color(int x, int c) {
    if (~col[x]) return col[x] == c ? void() : (puts("0"), exit(0));
    col[x] = c;
    for (int i = head[x]; ~i; i = next[i]) color(to[i], c ^ 1);
}
// std::pair<int -> r, int -> id>
std::set<std::pair<int, int>> S;
int nxt[MAXN];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &d[i].first, &d[i].second);
    std::sort(d + 1, d + n + 1);
    memset(head, -1, sizeof(head));
    memset(col, -1, sizeof(col));
    for (int i = 1; i <= n; i++) {
        while (S.size() && S.begin()->first < d[i].first) {
            int id = S.begin()->second;
            S.erase(S.begin());
            if (nxt[id]) S.insert({d[nxt[id]].second, nxt[id]});
        }
        auto it = S.insert({d[i].second, i}).first;
        int t = 0, right = 0x7FFFFFFF;
        while (it != S.begin()) Q[++t] = *--it;
        for (int j = 1; j <= t; j++) {
            if (d[Q[j].second].first > right) {
                return puts("0"), 0;
            } else {
                right = std::min(right, Q[j].first);
                $(Q[j].second, i);
            }
        }
        for (int j = 2; j <= t; j++) nxt[Q[j].second] = Q[j - 1].second;
        for (int j = 1; j < t; j++) S.erase(Q[j]);
    }
    for (int i = 1; i <= n; i++)
        if (!~col[i]) color(i, 0), ans = 1LL * ans * 2 % MOD;
    printf("%d\n", ans);
    return 0;
}
