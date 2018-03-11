#include <algorithm>
#include <cstdio>
#include <cstring>
#define MAXN 400010
double x[MAXN], y[MAXN], data[MAXN][4], tag0[MAXN][2], tag1[MAXN];
inline double sum2(int x) { return 1. * x * (x + 1) * (2 * x + 1) / 6; }
inline void _Reset(int n, int l, int r) {
    data[n][0] = data[n][1] = 1. * (l + r) * (r - l + 1) / 2;
    data[n][2] = data[n][3] = sum2(r) - sum2(l - 1);
    tag0[n][0] = tag0[n][1] = 0;
    return void(tag1[n] = 1);
}
inline void _Add(int n, int l, int r, double vx, double vy) {
    data[n][2] += data[n][0] * vy + data[n][1] * vx + vx * vy * (r - l + 1);
    data[n][3] += data[n][0] * 2 * vx + vx * vx * (r - l + 1);
    data[n][0] += vx * (r - l + 1);
    data[n][1] += vy * (r - l + 1);
    tag0[n][0] += vx;
    tag0[n][1] += vy;
}
inline void pushDown(int n, int l, int r) {
    int mid = (l + r) >> 1;
    if (tag1[n]) {
        _Reset(n << 1, l, mid);
        _Reset(n << 1 | 1, mid + 1, r);
        tag1[n] = 0;
    }
    _Add(n << 1, l, mid, tag0[n][0], tag0[n][1]);
    _Add(n << 1 | 1, mid + 1, r, tag0[n][0], tag0[n][1]);
    tag0[n][0] = tag0[n][1] = 0;
}
inline void pushUp(int n) {
    for (int i = 0; i < 4; i++) data[n][i] = data[n << 1][i] + data[n << 1 | 1][i];
}
void Build(int n, int l, int r) {
    if (l == r) {
        data[n][0] = x[l];
        data[n][1] = y[l];
        data[n][2] = x[l] * y[l];
        data[n][3] = x[l] * x[l];
        return;
    }
    int mid = (l + r) >> 1;
    Build(n << 1, l, mid);
    Build(n << 1 | 1, mid + 1, r);
    return pushUp(n);
}
double Sigma(int n, int l, int r, int L, int R, int d) {
    if (l != r) pushDown(n, l, r);
    if (l == L && r == R) return data[n][d];
    int mid = (l + r) >> 1;
    if (R <= mid)
        return Sigma(n << 1, l, mid, L, R, d);
    else if (L > mid)
        return Sigma(n << 1 | 1, mid + 1, r, L, R, d);
    return Sigma(n << 1, l, mid, L, mid, d) + Sigma(n << 1 | 1, mid + 1, r, mid + 1, R, d);
}
void Reset(int n, int l, int r, int L, int R) {
    if (l != r) pushDown(n, l, r);
    if (l == L && r == R) return _Reset(n, l, r);
    int mid = (l + r) >> 1;
    if (R <= mid)
        Reset(n << 1, l, mid, L, R);
    else if (L > mid)
        Reset(n << 1 | 1, mid + 1, r, L, R);
    else
        Reset(n << 1, l, mid, L, mid), Reset(n << 1 | 1, mid + 1, r, mid + 1, R);
    pushUp(n);
}
void Add(int n, int l, int r, int L, int R, int vx, int vy) {
    if (l != r) pushDown(n, l, r);
    if (l == L && r == R) return _Add(n, l, r, vx, vy);
    int mid = (l + r) >> 1;
    if (R <= mid)
        Add(n << 1, l, mid, L, R, vx, vy);
    else if (L > mid)
        Add(n << 1 | 1, mid + 1, r, L, R, vx, vy);
    else
        Add(n << 1, l, mid, L, mid, vx, vy), Add(n << 1 | 1, mid + 1, r, mid + 1, R, vx, vy);
    pushUp(n);
}
int n, m, l, r, s, t;
inline void print() {
    puts("NOW THE ARRAY IS:");
    for (int i = 1; i <= n; i++) printf("%5.0f ", Sigma(1, 1, n, i, i, 0));
    puts("");
    for (int i = 1; i <= n; i++) printf("%5.0f ", Sigma(1, 1, n, i, i, 1));
    puts("");
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lf", &x[i]);
    for (int i = 1; i <= n; i++) scanf("%lf", &y[i]);
    Build(1, 1, n);
    while (m--) {
        scanf("%d", &l);
        if (l == 1) {
            scanf("%d%d", &l, &r);
            double sx = Sigma(1, 1, n, l, r, 0);
            double sy = Sigma(1, 1, n, l, r, 1);
            double x0 = sx / (r - l + 1);
            double y0 = sy / (r - l + 1);
            double up = Sigma(1, 1, n, l, r, 2) - x0 * sy - y0 * sx + x0 * y0 * (r - l + 1);
            double dn = Sigma(1, 1, n, l, r, 3) - 2 * x0 * sx + x0 * x0 * (r - l + 1);
            printf("%.10f\n", up / dn);
        } else if (l == 2) {
            scanf("%d%d%d%d", &l, &r, &s, &t);
            Add(1, 1, n, l, r, s, t);
        } else {
            scanf("%d%d%d%d", &l, &r, &s, &t);
            Reset(1, 1, n, l, r);
            Add(1, 1, n, l, r, s, t);
        }
        //print();
    }
    return 0;
}