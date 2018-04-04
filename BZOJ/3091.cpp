#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50010
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
template <typename T>
void swap(T a, T b) {
    T c = a;
    a = b;
    b = c;
}
struct splay {
    splay *l, *r, *f;
    int size, val, rev, tag;
    long long suml, sumr, sum, ans;
    inline splay();
    inline splay(int);
    inline bool isRoot();
    inline void pushDown();
    inline void pushUp();
    inline void reverse();
    inline void add(int);
} *null = new splay(), *node[MAXN];
inline splay::splay() {
    l = r = f = null, size = rev = tag = suml = sumr = sum = val = 0;
}
inline splay::splay(int w) {
    l = r = f = null, size = 1, rev = tag = 0, suml = sumr = sum = val = w;
}
inline bool splay::isRoot() { return f == null || f->l == this || f->r == this; }
inline void splay::pushDown() {
    if (!isRoot()) f->pushDown();
    if (rev) l->reverse(), r->reverse(), rev ^= 1;
    if (tag) l->add(tag), r->add(tag), tag = 0;
}
inline void splay::pushUp() {
    size = 1 + l->size + r->size, sum = val + l->sum + r->sum;
    suml = l->suml + (l->size + 1LL) * val + r->suml + (l->size + 1LL) * r->sum;
    sumr = r->sumr + (r->size + 1LL) * val + l->sumr + (r->size + 1LL) * l->sum;
    ans = l->ans + r->ans + (r->size + 1LL) * l->suml + (l->size + 1LL) * r->sumr + (l->size + 1LL) * (r->size + 1LL) * val;
}
inline void splay::reverse() { swap(l, r), swap(suml, sumr), rev ^= 1; }
inline void splay::add(int x) {
    if (this == null) return;
    val += x, tag += x;
    sum += 1LL * x * size;
    suml += 1LL * x * size * (size + 1) / 2;
    sumr += 1LL * x * size * (size + 1) / 2;
    ans += 1LL * x * size * (size + 1) * (size + 2) / 6;
}
inline void l(splay *x) {
    splay *y = x->f;
    (y->r = x->l)->f = y;
    if (y->f->l == y) y->f->l = x;
    if (y->f->r == y) y->f->r = x;
    x->f = y->f, y->f = x, x->l = y;
    y->pushUp(), x->pushUp();
}
inline void r(splay *x) {
    splay *y = x->f;
    (y->l = x->r)->f = y;
    if (y->f->l == y) y->f->l = x;
    if (y->f->r == y) y->f->r = x;
    x->f = y->f, y->f = x, x->r = y;
    y->pushUp(), x->pushUp();
}
inline void ss(splay *x) {
    x->pushDown();
    while (!x->isRoot()) {
        splay *y = x->f;
        if (y->isRoot()) {
            x == y->l ? r(x) : l(x);
        } else {
            y == y->f->l ? (x == y->l ? r(y), r(x) : l(x), r(x)) : (x == y->l ? r(x), l(x) : l(y), l(x));
        }
    }
}
inline void access(splay *x) {
    for (splay *t = null; !x->isRoot(); x = x->f) ss(x), x->r = t, x->pushUp(), t = x;
}
inline void set(splay *x) { access(x), ss(x), x->reverse(); }
inline splay *symbol(splay *x) {
    while (x->f != null) x = x->f;
    return x;
}
inline void link(int x, int y) {
    splay *u = symbol(node[x]), *v = symbol(node[y]);
    if (u == v) return;
    set(u), u->f = v;
}
inline void cut(int x, int y) {
    splay *u = symbol(node[x]), *v = symbol(node[y]);
    if (u != v) return;
    set(u), access(v), ss(v);
    if (v->l == u && u->r == null) v->l = u->f = null, v->pushUp();
}
inline void add(int x, int y, int w) {
    if (symbol(node[x]) != symbol(node[y])) return;
    set(node[x]), access(node[y]), ss(node[y]);
    node[y]->add(w);
}
inline void query(int x, int y) {
    if (symbol(node[x]) != symbol(node[y])) return puts("-1"), void();
    set(node[x]), access(node[y]), ss(node[y]);
    long long a = node[y]->ans;
    long long b = node[y]->size;
    b = b * (b + 1) >> 1;
    long long g = gcd(a, b);
    printf("%lld/%lld\n", a / g, b / g);
}
int n, m, k, u, v;
int main() {
    freopen("in.txt", "r", stdin);
    n = $(), m = $();
    for (int i = 1; i <= n; i++) node[i] = new splay($());
    for (int i = 1; i < n; i++) link($(), $());
    while (m--) {
        k = $(), u = $(), v = $();
        switch (k) {
            case 1:
                link(u, v);
                break;
            case 2:
                link(u, v);
                break;
            case 3:
                add(u, v, $());
                break;
            case 4:
                query(u, v);
                break;
        }
    }
    return 0;
}