#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 10010
std::vector<int> val[MAXN << 2];
int n, q;
void add(int n, int l, int r, int L, int R, int x) {
    if (l == L && r == R) return val[n].push_back(x), void();
    int mid = (l + r) >> 1;
    if (R <= mid) return add(n << 1, l, mid, L, R, x);
    if (L > mid) return add(n << 1 | 1, mid + 1, r, L, R, x);
    add(n << 1, l, mid, L, mid, x);
    add(n << 1 | 1, mid + 1, r, mid + 1, R, x);
}
std::bitset<MAXN> ans, tmp;
void solve(int n, int l, int r) {
    std::bitset<MAXN> bak = tmp;
    for (int x : val[n]) tmp = tmp | (tmp << x);
    if (l == r) {
        ans |= tmp;
        tmp = bak;
        return;
    }
    int mid = (l + r) >> 1;
    solve(n << 1, l, mid);
    solve(n << 1 | 1, mid + 1, r);
    tmp = bak;
}
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1, l, r, x; i <= q; i++) {
        scanf("%d%d%d", &l, &r, &x);
        add(1, 1, n, l, r, x);
    }
    tmp.set(0);
    solve(1, 1, n);
    int x = 0;
    for (int i = 1; i <= n; i++)
        if (ans[i]) x++;
    printf("%d\n", x);
    for (int i = 1; i <= n; i++)
        if (ans[i]) printf("%d ", i);
    puts("");
    return 0;
}