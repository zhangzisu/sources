#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define MAXN 1000010
int n, k, ans = 0, pos = 0;
struct interval {
    int l, r, id;
    inline friend bool operator<(const interval &a, const interval &b) {
        return a.r > b.r;
    }
} d[MAXN];
inline bool cmp(const interval &a, const interval &b) { return a.l < b.l; }
std::priority_queue<interval> Q;
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d%d", &d[i].l, &d[i].r), d[i].id = i;
    if (k == 1) {
        for (int i = 1; i <= n; i++)
            if (d[i].r - d[i].l > ans) ans = d[i].r - d[i].l, pos = i;
        printf("%d\n", ans);
        if (pos) printf("%d", pos);
        return puts(""), 0;
    }
    std::sort(d + 1, d + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        if ((int)Q.size() >= k - 1) {
            int tmp = std::min(Q.top().r, d[i].r) - d[i].l;
            if (tmp > ans) {
                ans = tmp;
                pos = i;
            }
            if (d[i].r > Q.top().r) Q.pop(), Q.push(d[i]);
        } else {
            Q.push(d[i]);
        }
    }
    printf("%d\n", ans);
    if (pos) {
        while (Q.size()) Q.pop();
        for (int i = 1; i <= n; i++) {
            if (i == pos) {
                printf("%d", d[i].id);
                while (Q.size()) printf(" %d", Q.top().id), Q.pop();
                puts("");
            }
            if ((int)Q.size() >= k - 1) {
                if (d[i].r > Q.top().r) Q.pop(), Q.push(d[i]);
            } else {
                Q.push(d[i]);
            }
        }
    }
    return 0;
}