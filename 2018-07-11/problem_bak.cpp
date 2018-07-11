#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef long long LL;

#pragma comment(linker, "/STACK:16777216")
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define For(i, a, b) for (int i = (a); i <= (b); ++i)
#define rev(i, a, b) for (int i = (a); i >= (b); --i)
#define clr(a, x) memset(a, x, sizeof a)
#define mid ((l + r) >> 1)
#define ls (o << 1)
#define rs (o << 1 | 1)
#define lson ls, l, m
#define rson rs, m + 1, r

const int MAXN = 100005;
const int MAXE = 200005;
const int INF = 0x3f3f3f3f;

struct Edge {
    int v, c, n;
    Edge() {}
    Edge(int v, int c, int n) : v(v), c(c), n(n) {}
};

struct Node {
    Node* c[2];
    LL num, sum;
    void push_up() {
        num = c[0]->num + c[1]->num;
        sum = c[0]->sum + c[1]->sum;
    }
};

Node pool[MAXN * 50];
Node* node[MAXN];
Node* cur;
Node* root[MAXN];
Edge E[MAXE];
int H[MAXN], cntE;
int n, m;

int dep[MAXN];
int siz[MAXN];
int pre[MAXN];
int top[MAXN];
int son[MAXN];

void clear() {
    cntE = 0;
    clr(H, -1);
    cur = pool;
    siz[0] = 0;
    pre[1] = 0;
}

void addedge(int u, int v, int c) {
    E[cntE] = Edge(v, c, H[u]);
    H[u] = cntE++;
}

void build(Node*& o, int l, int r) {
    o = cur++;
    o->num = o->sum = 0;
    if (l == r) return;
    int m = mid;
    build(o->c[0], l, m);
    build(o->c[1], m + 1, r);
}

void insert(Node* old, Node*& now, int x, int l, int r) {
    now = cur++;
    if (l == r) {
        now->num = old->num + 1;
        now->sum = old->sum + x;
        return;
    }
    int m = mid;
    if (x <= m) {
        now->c[1] = old->c[1];
        insert(old->c[0], now->c[0], x, l, m);
    } else {
        now->c[0] = old->c[0];
        insert(old->c[1], now->c[1], x, m + 1, r);
    }
    now->push_up();
}

int query_flow(Node* u, Node* v, Node* lca) {
    int l = 0, r = 10000;
    while (l < r) {
        int m = mid;
        int tmp = u->c[0]->num + v->c[0]->num - 2 * lca->c[0]->num;
        if (tmp) {
            u = u->c[0];
            v = v->c[0];
            lca = lca->c[0];
            r = m;
        } else {
            u = u->c[1];
            v = v->c[1];
            lca = lca->c[1];
            l = m + 1;
        }
    }
    return l;
}

LL query(Node* u, Node* v, Node* lca, int Num) {
    int l = 0, r = 10000;
    int ans = 0;
    LL num = 0, sum = 0;
    while (l < r) {
        int m = mid;
        LL tmp_num = u->c[0]->num + v->c[0]->num - 2 * lca->c[0]->num;
        LL tmp_sum = u->c[0]->sum + v->c[0]->sum - 2 * lca->c[0]->sum;
        if ((num + tmp_num) * m - (sum + tmp_sum) > Num) {
            u = u->c[0];
            v = v->c[0];
            lca = lca->c[0];
            r = m;
        } else {
            num += tmp_num;
            sum += tmp_sum;
            u = u->c[1];
            v = v->c[1];
            lca = lca->c[1];
            l = m + 1;
        }
    }
    return l - 1;
}

void dfs(int u) {
    son[u] = 0;
    siz[u] = 1;
    for (int i = H[u]; ~i; i = E[i].n) {
        int v = E[i].v;
        if (v == pre[u]) continue;
        dep[v] = dep[u] + 1;
        pre[v] = u;
        insert(root[u], root[v], E[i].c, 0, 10000);
        dfs(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void rebuild(int u, int top_element) {
    top[u] = top_element;
    if (son[u]) rebuild(son[u], top_element);
    for (int i = H[u]; ~i; i = E[i].n) {
        int v = E[i].v;
        if (v != pre[u] && v != son[u]) {
            rebuild(v, v);
        }
    }
}

int get_lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = pre[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
}

void solve() {
    int u, v, k, a, b;
    clear();
    scanf("%d%d", &n, &m);
    rep(i, 1, n) {
        scanf("%d%d%d", &u, &v, &a);
        addedge(u, v, a);
        addedge(v, u, a);
    }
    build(root[1], 0, 10000);
    dfs(1);
    rebuild(1, 1);
    while (m--) {
        scanf("%d%d%d%d%d", &u, &v, &k, &a, &b);
        int lca = get_lca(u, v);
        LL flow = query_flow(root[u], root[v], root[lca]);
        if (a <= b)
            printf("%I64d\n", flow + k / a);
        else {
            LL ans = 0;
            if (k >= a) ans = max(ans, flow + (k - a) / b + 1);
            ans = max(ans, query(root[u], root[v], root[lca], k / b));
            printf("%I64d\n", ans);
        }
    }
}

int main() {
    // int T , cas = 0 ;
    // scanf ( "%d" , &T ) ;
    // while ( T -- ) {
    // printf ( "Case #%d:\n" , ++ cas ) ;
    solve();
    // }
    return 0;
}
