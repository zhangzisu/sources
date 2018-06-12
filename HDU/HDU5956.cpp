#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
typedef long long ll;
#define maxn 100005
#define INF 1e20
#define eps 1e-6
struct man {
    int d, v, w, id;
    double val;
    bool operator<(const man &b) const {
        return d < b.d;
    }
} sb[maxn], bs[maxn], tmp[maxn];
inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int T, n, m, maxW, last, can[maxn];
void CDQ(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    int curL = l, curR = mid + 1, cur = l;
    double minL, maxL, minR, maxR, MinL, MaxL, MinR, MaxR;
    minL = minR = MinL = MinR = 1e100;
    maxL = maxR = MaxL = MaxR = -1e100;
    while (cur <= r) {
        if (curR > r || (curL <= mid && bs[curL].w > bs[curR].w)) {
            if (cur != l && tmp[cur - 1].w != bs[curL].w)
                minL = MinL, maxL = MaxL, minR = MinR, maxR = MaxR;
            can[bs[curL].id] |= (bs[curL].val >= minR) || (bs[curL].val <= maxR - m);
            MinL = std::min(MinL, bs[curL].val);
            MaxL = std::max(MaxL, bs[curL].val);
            tmp[cur++] = bs[curL++];
        } else {
            if (cur != l && tmp[cur - 1].w != bs[curR].w)
                minL = MinL, maxL = MaxL, minR = MinR, maxR = MaxR;
            can[bs[curR].id] |= (bs[curR].val >= minL + m) || (bs[curR].val <= maxL);
            MinR = std::min(MinR, bs[curR].val);
            MaxR = std::max(MaxR, bs[curR].val);
            tmp[cur++] = bs[curR++];
        }
    }
    for (int i = l; i <= r; i++) bs[i] = tmp[i];
}
bool judge(double t) {
    for (int i = 1; i <= n; i++) bs[i] = sb[i], bs[i].val = bs[i].d + t * bs[i].v, can[i] = 0;
    CDQ(1, n);
    for (int i = 1; i <= n; i++)
        if (!can[i] && sb[i].w != maxW) {
            last = i;
            return 0;
        }
    return 1;
}
void update(man bs, man b, int &x, int &y) {
    if (bs.v < b.v) std::swap(bs, b);
    int tx, ty = bs.v - b.v;
    if (bs.d < b.d)
        tx = b.d - bs.d;
    else
        tx = m + b.d - bs.d;
    if (1ll * tx * y <= 1ll * x * ty) x = tx, y = ty;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &sb[i].d);
        for (int i = 1; i <= n; i++) scanf("%d", &sb[i].v);
        for (int i = 1; i <= n; i++) scanf("%d", &sb[i].w);
        std::sort(sb + 1, sb + n + 1);
        maxW = sb[1].w;
        for (int i = 2; i <= n; i++) maxW = std::max(maxW, sb[i].w);
        for (int i = 1; i <= n; i++) sb[i].id = i;
        double l = 0, r = m, mid;
        last = 0;
        while (l < r - eps) {
            mid = 0.5 * (l + r);
            if (judge(mid))
                r = mid;
            else
                l = mid;
        }
        if (!last)
            printf("0\n");
        else {
            int x = 0, y = 0;
            for (int i = 1; i <= n; i++)
                if (sb[i].w > sb[last].w) update(sb[i], sb[last], x, y);
            int g = gcd(x, y);
            printf("%d/%d\n", x / g, y / g);
        }
    }
    return 0;
}