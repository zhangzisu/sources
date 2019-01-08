#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
const double EPS = 1e-6;
int t, n, m, maxW;
struct man {
    int d, v, w, id;
    double val;
    inline friend bool operator<(const man &a, const man &b) {
        return a.d < b.d;
    }
} sb[MAXN], bs[MAXN], tmp[MAXN];
int can[MAXN];
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
int last = 0;
inline bool judge(double t) {
    memcpy(bs, sb, sizeof(bs));
    memset(can, 0, sizeof(can));
    for (int i = 1; i <= n; i++) bs[i].val = t * bs[i].v + bs[i].d;
    CDQ(1, n);
    for (int i = 1; i <= n; i++) {
        if (sb[i].w != maxW && !can[i]) {
            last = i;
            return 0;
        }
    }
    return 1;
}

inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
void update(man a, man b, int &x, int &y) {
    if (a.v < b.v) std::swap(a, b);
    int X = (a.d < b.d ? b.d - a.d : m + b.d - a.d), Y = a.v - b.v;
    if (1LL * X * y <= 1LL * x * Y) x = X, y = Y;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &sb[i].d);
        for (int i = 1; i <= n; i++) scanf("%d", &sb[i].v);
        for (int i = 1; i <= n; i++) scanf("%d", &sb[i].w);
        std::sort(sb + 1, sb + n + 1);
        maxW = 0x80000000;
        last = 0;
        for (int i = 1; i <= n; i++) {
            sb[i].id = i;
            maxW = std::max(maxW, sb[i].w);
        }
        double l = 0, r = m;
        while (r - l > EPS) {
            double mid = (l + r) / 2;
            if (judge(mid)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        if (!last) {
            puts("0");
            continue;
        }
        int x = 0, y = 0;
        for (int i = 1; i <= n; i++)
            if (sb[i].w > sb[last].w) update(sb[i], sb[last], x, y);
        int g = gcd(x, y);
        printf("%d/%d\n", x / g, y / g);
    }
    return 0;
}