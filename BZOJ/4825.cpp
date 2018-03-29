#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#define MAXN 200010
int m, n;
struct oper {
    int kind, val;
} op[MAXN];
std::map<int, int> M;
std::set<int> S;
int deep[MAXN << 2];
inline void pushDown(int n) {
    if (deep[n]) {
        deep[n << 1] += deep[n];
        deep[n << 1 | 1] += deep[n];
        deep[n] = 0;
    }
}
void Modify(int n, int l, int r, int p, int v) {
    if (l == r) return deep[n] = v, void();
    int mid = (l + r) >> 1;
    pushDown(n);
    if (p <= mid) return Modify(n << 1, l, mid, p, v);
    return Modify(n << 1 | 1, mid + 1, r, p, v);
}
void Add(int n, int l, int r, int L, int R, int v) {
    if (L > R) return;
    if (l == L && r == R) return deep[n] += v, void();
    int mid = (l + r) >> 1;
    pushDown(n);
    if (R <= mid) return Add(n << 1, l, mid, L, R, v);
    if (L > mid) return Add(n << 1 | 1, mid + 1, r, L, R, v);
    return Add(n << 1, l, mid, L, mid, v), Add(n << 1 | 1, mid + 1, r, mid + 1, R, v);
}
int Query(int n, int l, int r, int p) {
    if (l == r) return deep[n];
    int mid = (l + r) >> 1;
    pushDown(n);
    if (p <= mid) return Query(n << 1, l, mid, p);
    return Query(n << 1 | 1, mid + 1, r, p);
}
int root, fa[MAXN], son[MAXN][2];
inline int insert(int val) {
    fa[val] = son[val][0] = son[val][1] = 0;
    int ret;
    if (S.empty()) {
        root = val;
        ret = 1;
    } else {
        auto iter = S.upper_bound(val);
        if (iter != S.end() && !son[*iter][0]) {
            fa[son[*iter][0] = val] = *iter;
            ret = Query(1, 1, n, *iter) + 1;
        } else {
            --iter;
            fa[son[*iter][1] = val] = *iter;
            ret = Query(1, 1, n, *iter) + 1;
        }
    }
    Modify(1, 1, n, val, ret);
    S.insert(val);
    return ret;
}
inline int splay(int val) {
    int x = val ? *S.rbegin() : *S.begin();
    int deep = Query(1, 1, n, x);
    if (deep == 1) return deep;
    int y = fa[x];
    Modify(1, 1, n, x, 1);
    if(y){
        if(val)Add(1, 1, n, 1, y, 1);
        else Add(1, 1, n, y, n, 1);
    }
    fa[son[y][val] = son[x][val ^ 1]] = y;
    son[fa[root] = x][val ^ 1] = root;
    return fa[root = x] = 0, deep;
}
inline void remove(int val) {
    Add(1, 1, n, 1, n, -1);
    fa[son[root][val ^ 1]] = 0;
    S.erase(root);
    root = son[root][val ^ 1];
}
inline void print(int x, int d = 0) {
    if (son[x][0]) print(son[x][0], d + 4);
    for (int i = 0; i < d; i++) putchar(' ');
    printf("%d\n", x);
    if (son[x][1]) print(son[x][1], d + 4);
}
int main() {
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &op[i].kind);
        if (op[i].kind == 1) {
            scanf("%d", &op[i].val);
            M[op[i].val] = 1;
        }
    }
    for (auto &x : M) x.second = ++n;
    for (int i = 1; i <= m; i++) {
        if (op[i].kind == 1) {
            printf("%d\n", insert(op[i].val = M[op[i].val]));
        } else {
            printf("%d\n", splay(op[i].kind & 1));
            if (op[i].kind > 3) remove(op[i].kind & 1);
        }
    }
    return 0;
}