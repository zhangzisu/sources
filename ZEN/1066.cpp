#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
struct node {
    long long time, mt;
    inline friend bool operator<(const node &a, const node &b) {
        return a.time > b.time;
    }
};
long long l, n, m, ans;
std::priority_queue<node> A, B;
std::vector<long long> t0, t1;
node top;
int main() {
    scanf("%d%d%d", &l, &n, &m);
    for (long long i = 1, x; i <= n; i++) scanf("%d", &x), A.push({x, x});
    for (long long i = 1, x; i <= m; i++) scanf("%d", &x), B.push({x, x});
    for (long long i = 1; i <= l; i++) {
        top = A.top();
        A.pop();
        t0.push_back(top.time);
        A.push({top.time + top.mt, top.mt});
        top = B.top();
        B.pop();
        t1.push_back(top.time);
        B.push({top.time + top.mt, top.mt});
    }
    for (long long i = 0; i < l; i++) ans = std::max(ans, t0[i] + t1[l - i - 1]);
    printf("%d\n", ans);
}