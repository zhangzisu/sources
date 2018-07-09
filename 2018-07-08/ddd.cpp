#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define popcount __builtin_popcount
int n, m, count;
int stk[9];
inline void dfs(int deep, int last) {
    stk[deep] = last;
    // calc
    if (deep >= m) return;
    for (int j = 0; j < (1 << n); j++) {
        if (last & j) {
            dfs(deep + 1, j);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    if (n > m) std::swap(n, m);
    for (int i = 0; i < (1 << n); i++) dfs(1, i);
    printf("%d\n", count);
    return 0;
}