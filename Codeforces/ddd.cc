#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;
const int N = 100100;
int h[N * 2], val[N * 2], n, tot, num, cnt, stack[N], e, adj[N * 2];
int f[N * 2][20], bin[25], fa[N * 2], l[N * 2], r[N * 2];
struct edge {
    int qi, zhong, val;
} intn[N * 5];
struct link {
    int zhong, next;
} s[N * 2];
inline void mission1(int rt) {
    for (int i = 1; bin[i] <= n; i++) f[rt][i] = f[f[rt][i - 1]][i - 1];
}
inline void add(int qi, int zhong) {
    s[++e].zhong = zhong;
    s[e].next = adj[qi];
    adj[qi] = e;
}
inline bool mt(const edge &a, const edge &b) { return a.val < b.val; }
int find(int a) { return (fa[a] == a) ? a : fa[a] = find(fa[a]); }
struct node {
    int cnt;
    node *ch[2];
    node() {
        cnt = 0;
        ch[0] = ch[1] = NULL;
    }
    inline void update() { cnt = ch[0]->cnt + ch[1]->cnt; }
} *null = new node(), *root[2 * N];
inline node *newnode() {
    node *o = new node();
    o->ch[0] = o->ch[1] = null;
    return o;
}
void insert(node *&o, node *old, int l, int r, int pos) {
    o->cnt = old->cnt + 1;
    if (l == r) return;
    int mi = (l + r) >> 1;
    if (pos <= mi)
        o->ch[1] = old->ch[1], o->ch[0] = newnode(), insert(o->ch[0], old->ch[0], l, mi, pos);
    else
        o->ch[0] = old->ch[0], o->ch[1] = newnode(), insert(o->ch[1], old->ch[1], mi + 1, r, pos);
    o->update();
}
inline int query(int a, int x, int k) {
    int le = 1, ri = tot;
    for (int j = 18; ~j; j--)
        　　　　if (f[a][j] && val[f[a][j]] <= x) a = f[a][j];
    node *a1 = root[r[a]], *a2 = root[l[a] - 1];
    if (a1->cnt - a2->cnt < k) return -1;
    while (le < ri) {
        int tmp = a1->ch[1]->cnt - a2->ch[1]->cnt, mi = (le + ri) >> 1;
        if (tmp >= k)
            a1 = a1->ch[1], a2 = a2->ch[1], le = mi + 1;
        else
            a1 = a1->ch[0], a2 = a2->ch[0], k -= tmp, ri = mi;
    }
    return stack[ri];
}
void dfs(int rt) {
    mission1(rt);
    l[rt] = ++num;
    if (rt <= n)
        insert(root[num], root[num - 1], 1, tot, h[rt]);
    else
        root[num] = root[num - 1];
    for (int i = adj[rt]; i; i = s[i].next) dfs(s[i].zhong);
    r[rt] = num;
}
int main() {
    int m, q, ans = 0, v, x, k;
    scanf("%d%d%d", &n, &m, &q);
    bin[0] = 1;
    for (int i = 1; i <= 22; i++) bin[i] = bin[i - 1] << 1;
    null->ch[0] = null->ch[1] = null;
    for (int i = 1; i <= n * 2; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]), stack[i] = h[i];
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &intn[i].qi, &intn[i].zhong, &intn[i].val);
    sort(stack + 1, stack + n + 1);
    tot = unique(stack + 1, stack + n + 1) - stack - 1;
    for (int i = 1; i <= n; i++) h[i] = lower_bound(stack + 1, stack + tot + 1, h[i]) - stack;
    sort(intn + 1, intn + m + 1, mt);
    cnt = n;
    for (int i = 1; i <= m; i++) {
        int u = find(intn[i].qi), v = find(intn[i].zhong);
        if (u != v) {
            val[++cnt] = intn[i].val, fa[u] = fa[v] = cnt;
            add(cnt, u), add(cnt, v), f[u][0] = f[v][0] = cnt;
            if (cnt - n == n - 1) break;
        }
    }
    for (int i = 0; i <= cnt; i++) root[i] = newnode();
    for (int i = 1; i <= cnt; i++)
        if (!l[i]) dfs(find(i));
    while (q--) {
        scanf("%d%d%d", &v, &x, &k);
        if (ans != -1) v ^= ans, x ^= ans, k ^= ans; /*去掉这句强制在线可以ACbzoj3545*/
        printf("%d\n", ans = query(v, x, k));
    }
}