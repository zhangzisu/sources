#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
int n, k, MOD, m[26], f[30], g[30], ans;
char buf[26][200];
std::vector<int> val[26];
inline void build(int level) {
    for (int i = 4; i <= m[level]; i++) {
        if (isalpha(buf[level][i])) {
            int pr = buf[level][i] - 'A';
            for (auto x : val[pr]) val[level].push_back(x);
        } else {
            int num = buf[level][i] - '0';
            val[level].push_back(num);
        }
    }
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int main() {
    scanf("%d%d%d", &n, &MOD, &k);
    for (int i = 0; i < k; i++) {
        scanf("%s", buf[i] + 1);
        m[i] = strlen(buf[i] + 1);
    }
    for (int i = k - 1; ~i; i--) build(i);
    for (int i = 0; i < (int)val[0].size(); i++) {
        memset(g, 0, sizeof(g));
        for (int j = 0; j < n; j++) {
            g[(j * 10 + val[0][i]) % n] += f[j];
        }
        if (val[0][i])
            up(g[val[0][i] % n], 1);
        else
            up(ans, 1);
        std::swap(f, g);
        up(ans, f[0]);
    }
    printf("%d\n", ans);
    return 0;
}