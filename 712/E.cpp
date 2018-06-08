#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, q;
double mul[MAXN << 2], ans[MAXN << 2], val[MAXN];
void pushUp(int n) {
    mul[n] = mul[n << 1] * mul[n << 1 | 1];
    ans[n] = ans[n << 1] + mul[n << 1] * ans[n << 1 | 1];
}
void build(int n, int l, int r) {
    if (l == r) {
        mul[n] = ans[n] = (1 - val[l]) / val[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(n << 1, l, mid);
    build(n << 1 | 1, mid + 1, r);
    pushUp(n);
}
void modify(int n, int l, int r, int p) {
    if (l == r) {
        mul[n] = ans[n] = (1 - val[l]) / val[l];
        return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid)
        modify(n << 1, l, mid, p);
    else
        modify(n << 1 | 1, mid + 1, r, p);
    pushUp(n);
}
double Mul, Ans;
void query(int n, int l, int r, int L, int R) {
    if (l == L && r == R) {
        Ans = Ans + Mul * ans[n];
        Mul = Mul * mul[n];
        return;
    }
    int mid = (l + r) >> 1;
    if (R <= mid)
        query(n << 1, l, mid, L, R);
    else if (L > mid)
        query(n << 1 | 1, mid + 1, r, L, R);
    else
        query(n << 1, l, mid, L, mid), query(n << 1 | 1, mid + 1, r, mid + 1, R);
}
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1, x, y; i <= n; i++) {
        scanf("%d%d", &x, &y);
        val[i] = 1. * x / y;
    }
    build(1, 1, n);
    while (q--) {
        int type, l, r, p;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d%d", &p, &l, &r);
            val[p] = 1. * l / r;
            modify(1, 1, n, p);
        } else {
            scanf("%d%d", &l, &r);
            Mul = 1;
            Ans = 0;
            query(1, 1, n, l, r);
            if (Ans <= 1e15)
                printf("%.10lf\n", 1 / (1 + Ans));
            else
                puts("0.0000000000");
        }
    }
    return 0;
}