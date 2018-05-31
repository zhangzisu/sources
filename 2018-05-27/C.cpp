#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define BUF 65536
char _1[BUF], _2[BUF], *_3 = _1 + BUF, *_4 = _2;
inline char gc() {
    if (_3 == _1 + BUF) fread(_1, 1, BUF, stdin), _3 = _1;
    return *_3++;
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
    register int x = 0, f = 0;
    register char ch = getchar();
    while (!isdigit(ch) && (ch ^ 45)) ch = getchar();
    if (!(ch ^ 45)) f = 1, ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return f ? -x : x;
}
inline void pi(int x) {
    static int _5[32];
    if (!x) {
        pc('0');
        return;
    }
    if (x < 0) {
        pc(45);
        x = -x;
    }
    register int _6;
    for (_6 = 0; x; x /= 10) _5[++_6] = x % 10;
    while (_6) pc(_5[_6--] ^ 48);
}
#define MAXN 10010
int t, n, m, p[MAXN], ans;
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
class tree {
   private:
    int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot, fa[MAXN];
    void dfs(int x) {
        for (int i = head[x]; ~i; i = next[i]) {
            if (to[i] == fa[x]) continue;
            fa[to[i]] = x;
            dfs(to[i]);
        }
    }

   public:
    std::pair<int, int> info[MAXN];
    inline void reset() {
        memset(head, -1, sizeof(head));
        memset(fa, 0, sizeof(fa));
        tot = 0;
    }
    inline void $(int u, int v) {
        next[tot] = head[u], to[tot] = v, head[u] = tot++;
        next[tot] = head[v], to[tot] = u, head[v] = tot++;
    }
    inline void build() {
        dfs(1);
    }
    inline void fuck(int x) {
        while (x) {
            int U = find(info[x].first);
            int V = find(info[x].second);
            if (U != V) {
                ans--;
                p[U] = V;
            }
            x = fa[x];
        }
    }
} tr0, tr1;

int main() {
    t = $();
    while (t--) {
        n = $(), m = $();
        tr0.reset();
        tr1.reset();
        for (int i = 1; i <= n; i++) tr0.info[i].first = $(), tr0.info[i].second = $();
        for (int i = 1; i < n; i++) tr0.$($(), $());
        for (int i = 1; i <= n; i++) tr1.info[i].first = $(), tr1.info[i].second = $();
        for (int i = 1; i < n; i++) tr1.$($(), $());
        tr0.build();
        tr1.build();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) p[j] = j;
            ans = m;
            tr0.fuck(i);
            tr1.fuck(i);
            pi(ans);
            pc(10);
        }
    }
    rt();
}