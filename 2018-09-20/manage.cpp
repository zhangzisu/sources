#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int n, m, ans = (~0U) >> 1;
struct task_t {
    int s, t;
    inline bool friend operator<(const task_t& a, const task_t& b) {
        return a.t < b.t;
    }
} tasks[MAXN];
int main() {
    freopen("manage.in", "r", stdin);
    freopen("manage.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &tasks[i].s, &tasks[i].t);
    std::sort(tasks + 1, tasks + n + 1);
    for (int i = n; i >= 1; i--) {
        ans = std::min(ans, tasks[i].t);
        ans -= tasks[i].s;
    }
    printf("%d\n", ans >= 0 ? ans : -1);
    return 0;
}