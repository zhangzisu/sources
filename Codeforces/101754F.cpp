#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 500010
int n, m, k;
std::pair<int, int> p[MAXN];

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++) scanf("%d%d", &p[i].first, &p[i].second);
    std::sort(p + 1, p + k + 1);
    return 0;
}