#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, n) for (int i = a; i < n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef vector<int> VI;
typedef long long ll;
typedef pair<int, int> PII;
const ll mod = 1000000007;
ll powmod(ll a, ll b) {
    ll res = 1;
    a %= mod;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}
// head

const int N = 101000;
int q[N], f[N], vis[N], sz[N], ms[N], brh[N];
int u, v, w, n, tot;
VI e[N], d[N];
long long ans;
set<int> ts[N];
int nd[N * 4], l[N], r[N], spe[N], p[N];
VI must;
int find(int u) {
    int t = 1;
    q[0] = u;
    f[u] = -1;
    rep(i, 0, t) {
        u = q[i];
        rep(j, 0, SZ(e[u])) {
            int v = e[u][j];
            if (!vis[v] && v != f[u]) f[q[t++] = v] = u;
        }
        ms[q[i]] = 0;
        sz[q[i]] = 1;
    }
    for (int i = t - 1; i >= 0; i--) {
        ms[q[i]] = max(ms[q[i]], t - sz[q[i]]);
        if (ms[q[i]] * 2 <= t) return q[i];
        sz[f[q[i]]] += sz[q[i]];
        ms[f[q[i]]] = max(ms[f[q[i]]], sz[q[i]]);
    }
    return 0;
}
void df(int u, int f, long long dep) {
    ans += dep;
    rep(j, 0, SZ(e[u])) {
        int v = e[u][j];
        if (v == f) continue;
        df(v, u, dep + d[u][j]);
    }
}
void dfs(int u, int f, int br) {
    l[u] = ++tot;
    brh[u] = br;
    sz[u] = 1;
    rep(i, 0, SZ(e[u])) {
        int v = e[u][i];
        if (v == f) continue;
        dfs(v, u, br);
        sz[u] += sz[v];
    }
    r[u] = tot;
}
void modify(int p, int l, int r, int x, int v) {
    if (l == r)
        nd[p] = v;
    else {
        int md = (l + r) >> 1;
        if (x <= md)
            modify(p + p, l, md, x, v);
        else
            modify(p + p + 1, md + 1, r, x, v);
        nd[p] = min(nd[p + p], nd[p + p + 1]);
    }
}
int query(int p, int l, int r, int tl, int tr) {
    if (l == tl && r == tr)
        return nd[p];
    else {
        int md = (l + r) >> 1;
        if (tr <= md)
            return query(p + p, l, md, tl, tr);
        else if (tl > md)
            return query(p + p + 1, md + 1, r, tl, tr);
        else
            return min(query(p + p, l, md, tl, md), query(p + p + 1, md + 1, r, md + 1, tr));
    }
}
int query(int u, int k) {
    if (k == 0) {
        if (r[u] == n)
            return query(1, 1, n, 1, l[u] - 1);
        else
            return min(query(1, 1, n, 1, l[u] - 1), query(1, 1, n, r[u] + 1, n));
    } else
        return query(1, 1, n, l[u], r[u]);
}
int main() {
    scanf("%d", &n);
    rep(i, 1, n) {
        scanf("%d%d%d", &u, &v, &w);
        e[u].pb(v);
        e[v].pb(u);
        d[u].pb(w);
        d[v].pb(w);
    }
    u = find(1);
    df(u, 0, 0);
    printf("%I64d\n", ans * 2);
    l[u] = ++tot;
    rep(i, 0, SZ(e[u])) {
        v = e[u][i];
        dfs(v, u, v);
        sz[v] *= 2;
        ts[sz[v]].insert(v);
    }
    r[u] = 1;
    brh[u] = u;
    spe[u] = 1;
    rep(i, 1, n + 1) modify(1, 1, n, l[i], i);
    rep(i, 1, n + 1) {
        must.clear();
        for (set<int>::iterator it = ts[n + 1 - i].begin(); it != ts[n + 1 - i].end(); it++)
            must.pb(*it);
        // printf("ML %d\n", i);
        // for (auto x : must) printf("\t- %d\n", x);
        if (SZ(must) == 2)
            p[i] = query(must[brh[i] == must[0]], 1);
        else if (SZ(must) == 1) {
            if (brh[i] == must[0])
                p[i] = query(brh[i], 0);
            else
                p[i] = query(must[0], 1);
        } else {
            if (spe[i])
                p[i] = nd[1];
            else
                p[i] = query(brh[i], 0);
        }
        // printf("[%d -> %d]\n", i, p[i]);
        // printf("MDF %d\n", l[p[i]]);
        modify(1, 1, n, l[p[i]], 1 << 30);
        u = brh[i], v = brh[p[i]];
        if (!spe[u]) ts[sz[u]].erase(u), ts[--sz[u]].insert(u);
        if (!spe[v]) ts[sz[v]].erase(v), ts[--sz[v]].insert(v);
    }
    rep(i, 1, n + 1) printf("%d%c", p[i], (i == n) ? '\n' : ' ');
}