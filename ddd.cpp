#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#define fi first
#define se second

using namespace std;

typedef pair<int, int> pii;

const int N = 1000010, P = 1e9 + 7;

inline char nc() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline void read(int &x) {
    char c = nc();
    x = 0;
    for (; c > '9' || c < '0'; c = nc())
        ;
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = nc())
        ;
}

int n, cnt, a[N], b[N], id[N], G[N], t;
set<pii> S;

pii q[N];

struct edge {
    int t, nx;
} E[N << 2];

inline bool cmp(const int &x, const int &y) {
    return a[x] < a[y];
}

inline void addedge(int x, int y) {
    E[++cnt].t = y;
    E[cnt].nx = G[x];
    G[x] = cnt;
    E[++cnt].t = x;
    E[cnt].nx = G[y];
    G[y] = cnt;
}

int cl[N];

void dfs(int x, int c) {
    if (cl[x]) {
        if (cl[x] != c) puts("0"), exit(0);
        return;
    }
    cl[x] = c;
    for (int i = G[x]; i; i = E[i].nx) dfs(E[i].t, c ^ 1);
}

int nxt[N];

int main() {
    read(n);
    for (int i = 1; i <= n; i++)
        read(a[i]), read(b[i]), id[i] = i;
    sort(id + 1, id + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        while (!S.empty() && S.begin()->fi < a[id[i]]) {
            int cur = S.begin()->se;
            S.erase(S.begin());
            if (nxt[cur]) S.insert(pii(b[nxt[cur]], nxt[cur]));
        }
        set<pii>::iterator cur = S.insert(pii(b[id[i]], id[i])).fi;
        t = 0;
        while (cur != S.begin()) {
            cur--;
            q[++t] = *cur;
        }
        int mx = 1 << 29;
        for (int j = 1; j <= t; j++)
            if (a[q[j].se] > mx)
                return puts("0"), 0;
            else {
                mx = min(mx, q[j].fi);
                addedge(q[j].se, id[i]);
            }
        for (int i = 1; i < t; i++) S.erase(q[i]);
        for (int i = 2; i <= t; i++) nxt[q[i].se] = q[i - 1].se;
    }
    int ans = 1;
    for (int i = 1; i <= n; i++)
        if (!cl[i]) {
            dfs(i, 2);
            ans = 2 * ans % P;
        }
    printf("%d\n", ans);
    return 0;
}