#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
const long long INF = 1e18;
int n;
std::vector<int> v, v0, v1;
std::vector<long long> r0, r1;
void dfs(int i, long long x, std::vector<int> &v, std::vector<long long> &r) {
    if (i == (int)v.size()) {
        r.push_back(x);
        return;
    }
    dfs(i + 1, x, v, r);
    for (; x <= INF / v[i]; x *= v[i]) {
        dfs(i + 1, x * v[i], v, r);
    }
}
long long k;
int main() {
    scanf("%d", &n);
    for (int i = 0, x; i < n; i++) {
        scanf("%d", &x);
        v.push_back(x);
    }
    for (int i = 0; i < n; i++) (i & 1 ? v1 : v0).push_back(v[i]);
    dfs(0, 1, v0, r0);
    dfs(0, 1, v1, r1);
    std::sort(r0.begin(), r0.end());
    std::sort(r1.begin(), r1.end());
    scanf("%lld", &k);
    long long l = 1, r = INF, ans = INF;
    while (l <= r) {
        long long mid = (l + r) >> 1;
        long long count = 0;
        int cur = 0;
        for (int i = (int)r0.size() - 1; i >= 0; i--) {
            while (cur < (int)r1.size() && r1[cur] <= mid / r0[i]) cur++;
            // printf("DBG : %lld\t%lld\n", r0[i], r1[cur]);
            count += cur;
        }
        if (count >= k)
            ans = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}