#include <cstdlib>
#include <iostream>
#include <vector>
#define MAXN 200010
using std::vector;
inline void fail() {
    puts("-1");
    exit(0);
}
int n, m, a[MAXN], ans[MAXN], pnt;
void slove(int l, int r, int L, int R) {
    if (l > r) return;
    if (L > R) {
        for (int i = r; i >= l; i--) ans[++pnt] = i;
        return;
    }
    int &x = a[L];
    if (x < l || x > r) fail();
    ans[++pnt] = x;
    slove(l, x - 1, L + 1, std::min(L + x - l, R));
    slove(x + 1, r, L + x - l + 1, R);
}
int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) std::cin >> a[i];
    slove(1, n, 1, m);
    for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
    return 0;
}