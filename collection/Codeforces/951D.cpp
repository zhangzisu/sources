#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n;
std::pair<int, int> v[MAXN];
inline bool D(int a, int b, int c) {
    int deltaX = v[b].first - v[a].first;
    int deltaY = v[b].second - v[a].second;
    int dX = v[c].first - v[a].first;
    int dY = v[c].second - v[a].second;
    return 1LL * deltaX * dY == 1LL * deltaY * dX;
}
inline bool DD(int a, int b, int c) {
    if (v[a].first > v[b].first) std::swap(a, b);
    if (v[b].first > v[c].first) std::swap(b, c);
    if (v[a].first > v[b].first) std::swap(a, b);
    if (v[b].first > v[c].first) std::swap(b, c);
    return D(a, b, c);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &v[i].first, &v[i].second);
    std::sort(v + 1, v + n + 1);
    int d[4] = {0, 1, 2, 0};
    for (int i = 3; i <= n; i++) {
        if (!D(1, 2, i)) {
            d[3] = i;
            break;
        }
    }
    if (!d[3]) return puts("YES"), 0;
    int t[3], tt;
    for (int i = 1; i <= 3; i++) {
        for (int j = i + 1; j <= 3; j++) {
            // printf("check line by (%3d,%3d) and (%3d,%3d)\n", v[d[i]].first, v[d[i]].second, v[d[j]].first, v[d[j]].second);
            for (int k = 1; k <= 3; k++) {
                if (d[k] != d[i] && d[k] != d[j]) t[tt = 1] = d[k];
            }
            for (int k = 1; k <= n; k++) {
                if (k != d[1] && k != d[2] && k != d[3]) {
                    if (DD(d[i], d[j], k)) continue;
                    if (tt == 1) {
                        t[++tt] = k;
                        continue;
                    } else {
                        if (DD(t[1], t[2], k)) continue;
                    }
                    goto fail;
                }
            }
            return puts("YES"), 0;
        fail:;
        }
    }
    return puts("NO"), 0;
}