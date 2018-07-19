#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, head[MAXN], to[MAXN], next[MAXN], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
}
int size[MAXN], fa[MAXN], deep[MAXN], top[MAXN];
void dfs(int x) {
    size[x] = 1;
    for (int i = head[x]; ~i; i = next[i]) {
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        dfs(to[i]);
        size[x] += size[to[i]];
    }
}
void split(int x) {
    if (!~top[x]) top[x] = x;
    int max = n + 1;
    for (int i = head[x]; ~i; i = next[i])
        if (size[to[i]] > size[max]) max = to[i];
    if (max <= n) {
        top[max] = top[x];
        split(max);
    }
    for (int i = head[x]; ~i; i = next[i])
        if (to[i] != max) split(to[i]);
}
struct splay {
    splay *l, *r, *f;
    int val, size;
    inline splay(int val = 0) {
        this->l = this->r = this->f = NULL;
        this->val = val;
        this->size = 1;
    }
    inline void update() {
        this->size = 1;
        if (this->l) this->size += this->l->size;
        if (this->r) this->size += this->r->size;
    }
} * root;
inline void l(splay *x) {
    splay *f = x->f;
    splay *p = f->f;
    if (f->r = x->l) f->r->f = f;
    (x->l = f)->f = x;
    if (p && p->l == f) p->l = x;
    if (p && p->r == f) p->r = x;
    x->f = p;
    f->update();
    x->update();
}
inline void r(splay *x) {
    splay *f = x->f;
    splay *p = f->f;
    if (f->l = x->r) f->l->f = f;
    (x->r = f)->f = x;
    if (p && p->l == f) p->l = x;
    if (p && p->r == f) p->r = x;
    x->f = p;
    f->update();
    x->update();
}
inline void splay(splay *x) {
    while (x->f) {
        splay *f = x->f;
        splay *p = f->f;
        if (p) {
            if (p->l == f) {
                if (f->l == x)
                    r(f), r(x);
                else
                    l(x), r(x);
            } else {
                if (f->l == x)
                    r(x), l(x);
                else
                    l(f), l(x);
            }
        } else {
            if (f->l == x)
                r(x);
            else
                l(x);
        }
    }
}
inline splay *find(splay *root, int val) {
    splay *p = NULL;
    while (root) {
        p = root;
        if (root->val >= val)
            root = root->l;
        else
            root = root->r;
    }
}
inline splay *insert(splay *root, int val) {
    //
}
inline splay *count(splay *root, int val) {
    //
}

int main() {
    memset(head, -1, sizeof(head));
    memset(top, -1, sizeof(top));
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) scanf("%d", &x), $(x, i);
    dfs(0);
    split(0);
    //
    return 0;
}