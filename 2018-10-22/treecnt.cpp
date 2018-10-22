#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2, _5[64];
int _0;
inline char gc() {
    if (_3 == _1 + BUF) _0 = fread(_1, 1, BUF, stdin), _3 = _1;
    return _3 == _1 + _0 ? 0 : *_3++;
}
inline void pc(char c) {
    if (_4 == _2 + BUF) fwrite(_2, 1, BUF, stdout), _4 = _2;
    *_4++ = c;
}
inline void rt() {
    fwrite(_2, 1, _4 - _2, stdout);
    exit(0);
}
inline int $() {
    register int x = 0;
    register char ch = gc();
    while (!isdigit(ch) && (ch ^ 45)) ch = gc();
    for (; isdigit(ch); ch = gc()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
inline void $(int x) {
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = (x % 10) ^ 48;
    while (_6) pc(_5[_6--]);
}
inline void $(long long x) {
    if (!x) return pc('0');
    if (x < 0) pc(45), x = -x;
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = (x % 10) ^ 48;
    while (_6) pc(_5[_6--]);
}
inline void $(const char *s) {
    for (; *s; s++) pc(*s);
}
#include <set>
#define MAXN 100010
typedef long long lnt;
int n, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int size[MAXN], deep[MAXN], fa[MAXN], top[MAXN], pfr[MAXN], dfn[MAXN], nfd[MAXN], dfsclk;
void pre(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x]) continue;
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        pre(to[i]);
        size[x] += size[to[i]];
    }
}
void split(int x) {
    nfd[dfn[x] = ++dfsclk] = x;
    if (!~top[x]) top[x] = x;
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && (!~pfr[x] || size[to[i]] > size[pfr[x]])) pfr[x] = to[i];
    if (~pfr[x]) top[pfr[x]] = top[x], split(pfr[x]);
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != fa[x] && to[i] != pfr[x]) split(to[i]);
}
lnt ans = 0, now;
std::set<std::pair<int, int>> ranges;
std::set<int> pos;
inline lnt suan(int len) {
    return 1LL * len * (len + 1) / 2;
}
inline void reinit() {
    pos.clear();
    ranges.clear();
    pos.insert(0);
    pos.insert(n + 1);
    now = suan(n);
}
inline void addPos(int x) {
    auto it = pos.lower_bound(x);
    int r = *it - 1, l = *--it + 1;
    now -= suan(r - l + 1);
    now += suan(x - l);
    now += suan(r - x);
    pos.insert(x);
}
inline void addRange(int x) {
    int l = x, r = x;
    auto it = ranges.upper_bound(std::make_pair(l, r));
    if (it != ranges.end() && it->first == r + 1) {
        r = it->second;
        now -= suan(it->second - it->first + 1);
        ranges.erase(it);
    }
    it = ranges.upper_bound(std::make_pair(l, r));
    if (it != ranges.begin() && (--it)->second == l - 1) {
        l = it->first;
        now -= suan(it->second - it->first + 1);
        ranges.erase(it);
    }
    ranges.insert(std::make_pair(l, r));
    now += suan(r - l + 1);
}
inline void add(int x) {
    addPos(x);
    addRange(x);
}
void dfs(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa[x] || to[i] == pfr[x]) continue;
        dfs(to[i]);
        reinit();
    }
    if (~pfr[x]) {
        dfs(pfr[x]);
        for (int p = dfn[x] + size[pfr[x]] + 1; p < dfn[x] + size[x]; p++) {
            add(nfd[p]);
        }
    }
    add(x);
    ans += now;
}
int main() {
    freopen("treecnt.in", "r", stdin);
    freopen("treecnt.out", "w", stdout);
    memset(head, -1, sizeof(head));
    memset(top, -1, sizeof(top));
    memset(pfr, -1, sizeof(pfr));
    n = $();
    for (int i = 1; i < n; i++) $($(), $());
    reinit(), pre(1), split(1), dfs(1);
    printf("%lld\n", 1LL * n * n * (n + 1) / 2 - ans);
    return 0;
}