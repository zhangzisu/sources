#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 51
const double EPS = 1e-4;
typedef long long lnt;
int n;
struct data {
    double a, b, c;
} d[MAXN];
double f[MAXN][MAXN], sa, sb;
inline bool check(double mid) {
    for (int i = 1; i <= n; i++) d[i].c = d[i].a - d[i].b * mid;
    for(int i=1;i<=n;i++)for(int j=0;j<=n;j++)f[i][j]=1e9;
    for(int i = 0;i < n;i++){
        for(int j = 0;j <= i;j++){
            f[i+1][j+1]=std::min(f[i+1][j+1]);
        }
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf", &d[i].a), sa += d[i].a;
    for (int i = 1; i <= n; i++) scanf("%lf", &d[i].b), sb += d[i].b;
    std::sort(d + 1, d + n + 1, [](const data& a, const data& b) { return a.a < b.a; });
    double l = 0, r = sa / sb;
    while (r - l > EPS) {
        double mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    printf("%.0lf\n", round((l + r) / 2 * 1000));
}