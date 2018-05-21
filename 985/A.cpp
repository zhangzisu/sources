#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>
int n, m, a[200], ans0, ans1;
int main() {
    scanf("%d", &n);
    m = n / 2;
    for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
    std::sort(a + 1, a + m + 1);
    for (int i = 1; i <= n; i += 2) {
        ans0 += std::abs(a[i / 2 + 1] - i);
    }
    for (int i = 2; i <= n; i += 2) {
        ans1 += std::abs(a[i / 2] - i);
    }
    printf("%d\n", std::min(ans0, ans1));
    return 0;
}