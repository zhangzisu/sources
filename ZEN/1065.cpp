#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2000020
struct line {
    double k, b;
    inline line(double k = 0, double b = -1e51) : k(k), b(b) {}
    inline line(double x0, double y0, double x1, double y1) {
        k = (y0 - y1) / (x0 - x1);
        b = y0 - k * x0;
    }
};
inline double exec(const line &l, double x) {
    return x * l.k + l.b;
}
line val[MAXN << 2];
double calc(int n, int l, int r, int x) {
    if (l == r) return exec(val[n], x);
    int mid = (l + r) >> 1;
    if (x <= mid)
        return std::max(calc(n << 1, l, mid, x), exec(val[n], x));
    else
        return std::max(calc(n << 1 | 1, mid + 1, r, x), exec(val[n], x));
}
void set(int n, int l, int r, int L, int R, line v) {
    if (l == L && r == R) {
        if (exec(val[n], l) >= exec(v, l) && exec(val[n], r) >= exec(v, r)) return;
        if (exec(val[n], l) <= exec(v, l) && exec(val[n], r) <= exec(v, r)) return void(val[n] = v);
    }
    int mid = (l + r) >> 1;
    if (R <= mid)
        set(n << 1, l, mid, L, R, v);
    else if (L > mid)
        set(n << 1 | 1, mid + 1, r, L, R, v);
    else
        set(n << 1, l, mid, L, mid, v), set(n << 1 | 1, mid + 1, r, mid + 1, R, v);
}
int n, m;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int x0, y0, x1, y1;
        scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
        x0 += 1000010;
        x1 += 1000010;
        if (x0 > x1) std::swap(x0, x1), std::swap(y0, y1);
        if (x0 == x1) {
            line v(0, std::max(y0, y1));
            set(1, 1, 2000010, x0, x0, v);
        } else {
            line v(x0, y0, x1, y1);
            set(1, 1, 2000010, x0, x1, v);
        }
    }
    while (m--) {
        int x0, y0, x1, y1;
        scanf("%d", &x0);
        if (x0) {
            scanf("%d", &x0);
            x0 += 1000010;
            double ans = calc(1, 1, 2000010, x0);
            printf("%f\n", ans < -1e50 ? 0 : ans);
        } else {
            scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            x0 += 1000010;
            x1 += 1000010;
            if (x0 > x1) std::swap(x0, x1), std::swap(y0, y1);
            if (x0 == x1) {
                line v(0, std::max(y0, y1));
                set(1, 1, 2000010, x0, x0, v);
            } else {
                line v(x0, y0, x1, y1);
                set(1, 1, 2000010, x0, x1, v);
            }
        }
    }
    return 0;
}