#include <algorithm>
#include <cstdio>
#define EPS 1E-8

struct point {
    int x, y;
} a[300010];

int n, atk, sum = 0;

bool cmp1(point a, point b) {
    int k = (a.y % atk == 0) ? (a.y / atk) : (a.y / atk + 1);
    int s = (b.y % atk == 0) ? (b.y / atk) : (b.y / atk + 1);
    if ((1ll * (k - 1) * a.x) < (1ll * (s - 1) * b.x)) return 1;
    if ((1ll * (k - 1) * a.x == 1ll * (s - 1) * b.x) && (a.x < b.x)) return 1;
    if ((1ll * (k - 1) * a.x == 1ll * (s - 1) * b.x) && (a.x == b.x) && (a.y < b.y)) return 1;
    return 0;
}

bool cmp2(point a, point b) {
    double k1 = a.x, k2 = a.y;
    double s1 = b.x, s2 = b.y;
    return ((k1 / k2) > (s1 / s2)) || ((abs(k1 / k2 - s1 / s2) < EPS) && (a.x > b.x));
}

bool cmp3(point a, point b) {
    return a.x > b.x;
}

int main() {
    scanf("%d%d", &n, &atk);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].x, &a[i].y);
        sum += a[i].x;
    }
    long long pre = 0;
    std::sort(a + 1, a + n + 1, cmp3);
    long long t = 0;
    for (int i = 3; i <= n; i++) {
        int ddd = (a[i].y + atk - 1) / atk;
        t += ddd;
        pre += (t - 1) * a[i].x;
    }
    std::sort(a + 1, a + n + 1, cmp1);
    sum -= a[n].x + a[n - 1].x;
    std::sort(a + 1, a + n - 1, cmp2);
    long long ans = 0;
    for (int i = 1; i <= n - 2; i++) {
        int k = (a[i].y % atk == 0) ? (a[i].y / atk) : (a[i].y / atk + 1);
        ans += 1ll * sum * (k - 1) + sum - a[i].x;
        sum -= a[i].x;
    }
    printf("%lld\n", std::min(ans, pre));
    return 0;
}
