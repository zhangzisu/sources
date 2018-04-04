#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define M 50500
using namespace std;
typedef unsigned long long ll;
struct abcd {
    abcd *ls, *rs, *fa;
    ll num, size;
    ll sum, lsum, rsum, exp;
    bool rev_mark;
    ll add_mark;
    abcd(int x);
    void Push_Up();
    void Push_Down();
    void Reverse();
    void Add(ll x);
} *null = new abcd(0), *tree[M];
abcd ::abcd(int x) {
    ls = rs = fa = null;
    num = x;
    size = null ? 1 : 0;
    sum = lsum = rsum = exp = x;
    rev_mark = false;
    add_mark = 0;
}
void abcd ::Push_Up() {
    size = ls->size + rs->size + 1;
    sum = ls->sum + rs->sum + num;
    lsum = ls->lsum + num * (ls->size + 1) + rs->lsum + rs->sum * (ls->size + 1);
    rsum = rs->rsum + num * (rs->size + 1) + ls->rsum + ls->sum * (rs->size + 1);
    exp = ls->exp + rs->exp + (rs->size + 1) * ls->lsum + (ls->size + 1) * rs->rsum + (ls->size + 1) * (rs->size + 1) * num;
}
void abcd ::Push_Down() {
    if (fa->ls == this || fa->rs == this)
        fa->Push_Down();
    if (rev_mark) {
        ls->Reverse();
        rs->Reverse();
        rev_mark = 0;
    }
    if (add_mark) {
        ls->Add(add_mark);
        rs->Add(add_mark);
        add_mark = 0;
    }
}
void abcd ::Reverse() {
    swap(lsum, rsum);
    swap(ls, rs);
    rev_mark ^= 1;
}
void abcd ::Add(ll x) {
    if (this == null)
        return;
    num += x;
    sum += x * size;
    lsum += x * size * (size + 1) / 2;
    rsum += x * size * (size + 1) / 2;
    exp += x * size * (size + 1) * (size + 2) / 6;
    add_mark += x;
}
void Zig(abcd *x) {
    abcd *y = x->fa;
    y->ls = x->rs;
    x->rs->fa = y;
    x->rs = y;
    x->fa = y->fa;
    if (y == y->fa->ls)
        y->fa->ls = x;
    else if (y == y->fa->rs)
        y->fa->rs = x;
    y->fa = x;
    y->Push_Up();
}
void Zag(abcd *x) {
    abcd *y = x->fa;
    y->rs = x->ls;
    x->ls->fa = y;
    x->ls = y;
    x->fa = y->fa;
    if (y == y->fa->ls)
        y->fa->ls = x;
    else if (y == y->fa->rs)
        y->fa->rs = x;
    y->fa = x;
    y->Push_Up();
}
void Splay(abcd *x) {
    x->Push_Down();
    while (x->fa->ls == x || x->fa->rs == x) {
        abcd *y = x->fa, *z = y->fa;
        if (x == y->ls) {
            if (y == z->ls)
                Zig(y);
            Zig(x);
        } else {
            if (y == z->rs)
                Zag(y);
            Zag(x);
        }
    }
    x->Push_Up();
}
void Access(abcd *x) {
    abcd *y = null;
    while (x != null) {
        Splay(x);
        x->rs = y;
        x->Push_Up();
        y = x;
        x = x->fa;
    }
}
void Move_To_Root(abcd *x) {
    Access(x);
    Splay(x);
    x->Reverse();
}
abcd *Find_Root(abcd *x) {
    while (x->fa != null)
        x = x->fa;
    return x;
}
void Link(abcd *x, abcd *y) {
    if (Find_Root(x) == Find_Root(y))
        return;
    Move_To_Root(x);
    x->fa = y;
}
void Cut(abcd *x, abcd *y) {
    if (x == y || Find_Root(x) != Find_Root(y))
        return;
    Move_To_Root(x);
    Access(y);
    Splay(y);
    if (y->ls == x && x->rs == null) {
        x->fa = null;
        y->ls = null;
        y->Push_Up();
    }
}
struct edge {
    int to, next;
} table[M << 1];
int head[M], tot;
int n, m;
void Add(int x, int y) {
    table[++tot].to = y;
    table[tot].next = head[x];
    head[x] = tot;
}
void DFS(int x, int from) {
    int i;
    if (from) tree[x]->fa = tree[from];
    for (i = head[x]; i; i = table[i].next) {
        if (table[i].to == from)
            continue;
        DFS(table[i].to, x);
    }
}
void Modify(abcd *x, abcd *y) {
    int z;
    scanf("%d", &z);
    if (Find_Root(x) != Find_Root(y))
        return;
    Move_To_Root(x);
    Access(y);
    Splay(y);
    y->Add(z);
}
ll GCD(ll x, ll y) {
    return y ? GCD(y, x % y) : x;
}
void Query(abcd *x, abcd *y) {
    if (Find_Root(x) != Find_Root(y)) {
        puts("-1");
        return;
    }
    Move_To_Root(x);
    Access(y);
    Splay(y);
    ll a = y->exp;
    ll b = y->size * (y->size + 1) >> 1;
    ll gcd = GCD(a, b);
    //cout<<(a/gcd)<<'/'<<(b/gcd)<<endl;
    //不能写cout 否则RE TM一上午就卡在这了
    printf("%lld/%lld\n", a / gcd, b / gcd);
}
int main() {
    ///freopen("travel.in","r",stdin);
    ///freopen("travel.out","w",stdout);

    int i, p, x, y;
    cin >> n >> m;
    for (i = 1; i <= n; i++)
        scanf("%d", &x), tree[i] = new abcd(x);
    for (i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        Add(x, y);
        Add(y, x);
    }
    DFS(1, 0);
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &p, &x, &y);
        switch (p) {
            case 1:
                Cut(tree[x], tree[y]);
                break;
            case 2:
                Link(tree[x], tree[y]);
                break;
            case 3:
                Modify(tree[x], tree[y]);
                break;
            case 4:
                Query(tree[x], tree[y]);
                break;
        }
    }
}
