#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 800010
typedef long long lnt;
const double INFDB = 1e20;
const double EPS = 1e-8;

int n, m;
struct d {
    lnt w, t, c;
} a[MAXN], b[MAXN];
lnt ans, res, sum, pfx[MAXN];
double slope(lnt x, lnt y) {
    if (!x) return y > 0 ? INFDB : 0;
    return 1. * y / x;
}
void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid);
    solve(mid + 1, r);
    std::sort(a + l, a + mid + 1, [](const d &a, const d &b) {
        return a.t < b.t;
    });
    std::sort(a + mid + 1, a + r + 1, [](const d &a, const d &b) {
        return a.w > b.w;
    });
    int top = 0;
    for (int i = l; i <= mid; i++) {
        while (top >= 2 &&
               slope(b[top].t - b[top - 1].t, b[top].c - b[top - 1].c) <
                   slope(a[i].t - b[top].t, a[i].c - b[top].c) + EPS) top--;
        b[++top] = a[i];
    }
    for (int i = mid + 1, cur = 1; i <= r; i++) {
        while (cur < top && slope(b[cur + 1].t - b[cur].t, b[cur + 1].c - b[cur].c) + EPS > a[i].w) cur++;
        res = std::min(res, ans - b[cur].c - a[i].c + b[cur].t * a[i].w);
    }
}
int main() {
    freopen("C:\\Users\\admin\\Downloads\\fittest3.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &a[i].w, &a[i].t);
        a[i].t = (a[i].t + m - 1) / m;
    }
    fprintf(stderr, "Pass %d\n", __LINE__);
    std::sort(a + 1, a + n + 1, [](const d &a, const d &b) {
        return a.w * b.t > b.w * a.t;
    });
    fprintf(stderr, "Pass %d\n", __LINE__);
    sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += a[i].t;
        ans += (sum - 1) * a[i].w;
        pfx[i] = pfx[i - 1] + a[i].t;
    }
    sum = 0;
    for (int i = n; i >= 1; i--) {
        a[i].c = sum * a[i].t + (pfx[i] - 1) * a[i].w;
        sum += a[i].w;
    }
    fprintf(stderr, "Pass %d\n", __LINE__);
    res = ans;
    solve(1, n);
    printf("%lld\n", res);
    return 0;
}