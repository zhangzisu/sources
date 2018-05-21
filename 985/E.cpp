#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>
#define MAXN 1000010
int n, k, d, a[MAXN], r[MAXN], c[MAXN];
std::vector<std::pair<int, int>> V;
int main() {
    scanf("%d%d%d", &n, &k, &d);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        r[i] = std::upper_bound(a + 1, a + n + 1, a[i] + d) - a - 1;
        if (r[i] - i + 1 >= k) V.push_back({i, i + r[i]});
    }
    if(V.front().first != 1)return puts("NO"), 0;
    int cur = 1, tot = 1, id = 1;
    while(id < (int)V.size()){
        //
    }
    return 0;
}