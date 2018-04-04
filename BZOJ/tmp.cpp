#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 50010
#define _ unsigned long long
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
struct splay {
    splay *l, *r, *f;
    int size, val, rev, tag;
    _ suml, sumr, sum, ans;
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
inline bool splay::isRoot() { return f == null || (f->l != this && f->r != this); }
inline void splay::pushDown() {
    if (!isRoot()) f->pushDown();
    if (rev) l->reverse(), r->reverse(), rev ^= 1;
    if (tag) l->add(tag), r->add(tag), tag = 0;
}
inline void splay::pushUp() {
    size = 1 + l->size + r->size, sum = val + l->sum + r->sum;
    suml = l->suml + (l->size + 1ULL) * val + r->suml + (l->size + 1ULL) * r->sum;
    sumr = r->sumr + (r->size + 1ULL) * val + l->sumr + (r->size + 1ULL) * l->sum;
    ans = l->ans + r->ans + (r->size + 1ULL) * l->suml + (l->size + 1ULL) * r->sumr + (l->size + 1ULL) * (r->size + 1ULL) * val;
}
inline void splay::reverse() { std::swap(l, r), std::swap(suml, sumr), rev ^= 1; }
inline void splay::add(int x) {
    if (this == null) return;
    val += x, tag += x;
    sum += 1ULL * x * size;
    suml += 1ULL * x * size * (size + 1) / 2;
    sumr += 1ULL * x * size * (size + 1) / 2;
    ans += 1ULL * x * size * (size + 1) * (size + 2) / 6;
}
inline void l(splay *x) {
    splay *y = x->f;
    (y->r = x->l)->f = y;
    if (y->f->l == y) y->f->l = x;
    if (y->f->r == y) y->f->r = x;
    x->f = y->f, y->f = x, x->l = y;
    y->pushUp();
}
inline void r(splay *x) {
    splay *y = x->f;
    (y->l = x->r)->f = y;
    if (y->f->l == y) y->f->l = x;
    if (y->f->r == y) y->f->r = x;
    x->f = y->f, y->f = x, x->r = y;
    y->pushUp();
}
inline void ss(splay *x) {
    x->pushDown();
    while (!(x->isRoot())) {
        splay *y = x->f;
        if (y->isRoot()) {
            if (x == y->l)
                r(x);
            else
                l(x);
        } else {
            if (y == y->f->l) {
                if (x == y->l)
                    r(y), r(x);
                else
                    l(x), r(x);
            } else {
                if (x == y->l)
                    r(x), l(x);
                else
                    l(y), l(x);
            }
        }
    }
    x->pushUp();
}
inline void access(splay *x) {
    for (splay *t = null; x != null; x = x->f) ss(x), x->r = t, x->pushUp(), t = x;
}
inline void set(splay *x) {
    access(x), ss(x), x->reverse();
}
inline splay *symbol(splay *x) {
    while (x->f != null) x = x->f;
    return x;
}
inline _ gcd(_ a, _ b) { return b ? gcd(b, a % b) : a; }
inline void link(splay *x, splay *y) {
    if (symbol(x) == symbol(y)) return;
    set(x), x->f = y;
}
inline void cut(splay *x, splay *y) {
    if (x == y || symbol(x) != symbol(y)) return;
    set(x), access(y), ss(y);
    if (y->l == x && x->r == null) y->l = x->f = null, y->pushUp();
}
inline void add(splay *x, splay *y) {
    int w = $();
    if (symbol(x) != symbol(y)) return;
    set(x), access(y), ss(y);
    y->add(w);
}
inline void query(splay *x, splay *y) {
    if (symbol(x) != symbol(y)) return puts("-1"), void();
    set(x), access(y), ss(y);
    _ a = y->ans, b = y->size;
    b = b * (b + 1) >> 1;
    _ g = gcd(a, b);
    printf("%lld/%lld\n", a / g, b / g);
}
int main() {
    int n = $(), m = $();
    for (int i = 1; i <= n; i++) node[i] = new splay($());
    for (int i = 1; i < n; i++) link(node[$()], node[$()]);
    while (m--) {
        int p = $(), x = $(), y = $();
        switch (p) {
            case 1:
                cut(node[x], node[y]);
                break;
            case 2:
                link(node[x], node[y]);
                break;
            case 3:
                add(node[x], node[y]);
                break;
            case 4:
                query(node[x], node[y]);
                break;
        }
    }
    return 0;
}