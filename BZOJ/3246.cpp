#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
const static int BUF = 10485760, MAXN = 500010;
char _1[BUF], *_3 = _1 + BUF;
inline char _char() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
}
inline int _int() {
    register int x = 0;
    register char ch = _char();
    while (!isdigit(ch)) ch = _char();
    for (; isdigit(ch); ch = _char()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
int head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
int n = _int(), m = _int(), k = _int(), u, v, vis[MAXN], tim;
long long max1, max2, max3, ans, f[MAXN], len, res, dis[MAXN];
bool spc[MAXN];
std::queue<int> Q;
inline int F(int x) {
    Q.push(x);
    ++tim;
    vis[x] = tim;
    dis[x] = 0;
    register int ret = x;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        if (dis[x] > dis[ret]) ret = x;
        len = std::max(len, dis[x]);
        for (int i = head[x]; ~i; i = next[i]) {
            if (vis[to[i]] != tim) {
                vis[to[i]] = tim;
                dis[to[i]] = dis[x] + val[i];
                Q.push(to[i]);
            }
        }
    }
    return ret;
}
inline void $(int w, int u, int v) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
bool fill(int x, int fa) {
    if (x == v) return spc[x] = 1;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa && fill(to[i], x)) return spc[x] = 1;
    return 0;
}
void dp(int x, int fa) {
    f[x] = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa) dp(to[i], x), f[x] = std::max(f[x], f[to[i]] + val[i]);
}
void slove(int x, int fa) {
    f[x] = 0;
    for (int i = head[x]; ~i; i = next[i])
        if (!spc[to[i]] && to[i] != fa)
            dp(to[i], x), f[x] = std::max(f[x], f[to[i]] + val[i]);
    f[x] = std::max(f[x], std::max(dis[x], len - dis[x]));
    res = std::min(res, f[x]);
    for (int i = head[x]; ~i; i = next[i])
        if (spc[to[i]] && to[i] != fa) slove(to[i], x);
}
inline long long $(int x) {
    len = 0;
    u = F(x), v = F(u);
    fill(u, -1);
    ans = std::max(ans, len);
    res = 0x3F3F3F3F3F3F3F3F;
    slove(u, -1);
    return res;
}
int cnt = 0;
int main() {
    memset(head, -1, sizeof(head));
    for (int _ = 1; _ <= m; _++) $(_int(), _int(), _int());
    for (int _ = 0; _ < n; _++)
        if (!vis[_]) {
            cnt++;
            long long x = $(_);
            if (x > max1)
                max3 = max2, max2 = max1, max1 = x;
            else if (x > max2)
                max3 = max2, max2 = x;
            else if (x > max3)
                max3 = x;
        }
    if (cnt == 2)
        ans = std::max(ans, max1 + max2 + k);
    else if (cnt >= 3)
        ans = std::max(ans, std::max(max1 + max2 + k, max2 + max3 + k + k));
    printf("%lld\n", ans);
    return 0;
}