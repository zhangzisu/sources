#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
#define MAXN 110
const int INF = (~0U) >> 1;
struct point_t {
    int x, y;
} p[MAXN];
int t, n, s, f[MAXN][MAXN][MAXN];
std::vector<int> V;
inline int div_s(int x, int y) {
    return y ? x / y : INF;
}
int dp(int l, int r, int h) {
    int &f = ::f[l][r][h];
    int H = V[h];
    if (~f) return f;
    while (l <= r && p[l].y <= H) l++;
    while (l <= r && p[r].y <= H) r--;
    if (l > r) return f = 0;
    if (l == r) return f = (H >= p[l].y ? 0 : 1);
    f = INF;
    int max = std::upper_bound(V.begin(), V.end(), div_s(s, p[r].x - p[l].x)) - V.begin() - 1;
    if (max > h) f = std::min(f, 1 + dp(l, r, max));
    for (int i = l; i < r; i++) f = std::min(f, dp(l, i, h) + dp(i + 1, r, h));
    return f;
}
int main() {
    for (t = $(); t; t--) {
        n = $(), s = $();
        V.clear();
        V.push_back(-1);
        for (int i = 1; i <= n; i++) p[i].x = $(), p[i].y = $();
        std::sort(p + 1, p + n + 1, [](point_t a, point_t b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });
        for (int i = 1; i <= n; i++) {
            if (i < n && p[i].x == p[i + 1].x) {
                for (int j = i; j < n; j++) p[j] = p[j + 1];
                n--;
            }
        }
        for (int i = 1; i <= n; i++) V.push_back(p[i].y);
        std::sort(V.begin(), V.end());
        V.erase(std::unique(V.begin(), V.end()), V.end());
        memset(f, -1, sizeof(f));
        printf("%d\n", dp(1, n, 0));
    }
    return 0;
}