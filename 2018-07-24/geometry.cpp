#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#define MAXN 1010
int t, n, x[MAXN], y[MAXN];
std::set<std::pair<int, int>> s;
int main() {
    freopen("geometry.in", "r", stdin);
    freopen("geometry.out", "w", stdout);
    for (scanf("%d", &t); t; t--) {
        scanf("%d", &n);
        s.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &x[i], &y[i]);
            s.insert(std::make_pair(x[i], y[i]));
        }
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                int x1 = x[i], y1 = y[i];
                int x2 = x[j], y2 = y[j];
                if (x1 > x2) {
                    std::swap(x1, x2);
                    std::swap(y1, y2);
                }
                if (y1 < y2) {
                    int dx = x2 - x1;
                    int dy = y2 - y1;
                    if (s.count(std::make_pair(x1 - dy, y1 + dx)) && s.count(std::make_pair(x2 - dy, y2 + dx))) goto succ;
                } else {
                    int dx = x2 - x1;
                    int dy = y1 - y2;
                    if (s.count(std::make_pair(x1 + dy, y1 + dx)) && s.count(std::make_pair(x2 + dy, y2 + dx))) goto succ;
                }
            }
        }
        puts("-1");
        continue;
    succ:
        puts("4");
    }
    return 0;
}