#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 200010

class FindingFriends {
    inline int lowbit(int x) { return x & -x; }
    int n, m, a[MAXN], bit[MAXN], k;
    inline void add(int x, int v) {
        for (int i = x; i <= n; i += lowbit(i)) bit[i] += v;
    }
    inline int sum(int x) {
        int y = 0;
        for (int i = x; i; i -= lowbit(i)) y += bit[i];
        return y;
    }
    inline int _(int x) {
        int l = 1, r = x - 1, ans = 0, t = sum(x - 1);
        if (!t) return 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (sum(mid) == t)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        return ans;
    }

    std::pair<int, int> dt[MAXN];
    int L[MAXN], R[MAXN];

    inline void _init() {
        for (int i = 1; i <= n; i++) dt[i] = {a[i], i};
        std::sort(dt + 1, dt + n + 1);
        int l = 1, r = 1;
        for (int i = 1; i <= n; i++) {
            while (r <= n && dt[r].first - dt[i].first <= k) add(dt[r++].second, 1);
            while (l <= n && dt[i].first - dt[l].first > k) add(dt[l++].second, -1);
            L[dt[i].second] = _(dt[i].second);
        }
        while (l < r) add(dt[l++].second, -1);
    }

    inline void init() {
        std::reverse(a + 1, a + n + 1);
        _init();
        memcpy(R, L, sizeof(R));
        std::reverse(a + 1, a + n + 1);
        _init();
        std::reverse(R + 1, R + n + 1);
        for (int i = 1; i <= n; i++) R[i] = n + 1 - R[i];
    }

    inline bool solve(int l, int r) {
        if (r - l + 1 < m) return 0;
        int _l = l, _r = r, bad = -1;
        for (;;) {
            if (_l > _r) break;
            if (L[_l] < l && R[_l] > r) {
                bad = _l;
                break;
            }
            ++_l;
            if (_l > _r) break;
            if (L[_r] < l && R[_r] > r) {
                bad = _r;
                break;
            }
            --_r;
        }
        if (!~bad) return 1;
        return solve(l, bad - 1) || solve(bad + 1, r);
    }

    inline bool judge() {
        init();
        // printf("K = %d\n", k);
        // for (int i = 1; i <= n; i++) printf("%3d\t%3d\n", L[i], R[i]);
        return solve(1, n);
    }
    int main() {
        int l = 0, r = 10000000, ans = -1;
        while (l <= r) {
            k = (l + r) >> 1;
            if (judge())
                ans = k, r = k - 1;
            else
                l = k + 1;
        }
        return ans;
    }

   public:
    int shortestDistance(int len, std::vector<int> init, int _a, int b, int c, int d, int ml) {
        n = len;
        m = ml;
        for (int i = 1; i <= (int)init.size(); i++) {
            a[i] = init[i - 1];
        }
        for (int i = init.size() + 1; i <= n; i++) {
            a[i] = (1LL * a[i - 1] * _a + 1LL * b * (i - 1) + c) % d;
        }
        return main();
    }
};