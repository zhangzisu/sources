#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 5010
char buf[MAXN];
int n, k = 1, m;
bool f[MAXN][1 << 12];
std::vector<std::pair<int, int>> a, b;
std::vector<char> ans;
int main() {
    scanf("%s", buf);
    n = strlen(buf);
    while ((1 << (k + 1)) <= n) k++;
    // printf("K : %d\n", k);
    m = n;
    for (int i = 1; i <= k; i++) m -= 1 << (i - 1);
    a.push_back({0, 0});
    f[0][0] = 1;
    while ((int)ans.size() < m) {
        char now = 'z';
        for (int _x = 0; _x < (int)a.size(); _x++) {
            auto x = a[_x];
            for (int d = 0; d < k; d++) {
                if ((x.second >> d) & 1) continue;
                if (!f[x.first + (1 << d)][x.second | (1 << d)]) {
                    a.push_back({x.first + (1 << d), x.second | (1 << d)});
                    f[x.first + (1 << d)][x.second | (1 << d)] = 1;
                    // printf("DDD (%d, %d)\n", x.first,x.second);
                }
            }
            now = std::min(now, buf[x.first]);
        }
        ans.push_back(now);
        b.clear();
        for (auto x : a) {
            if (buf[x.first] == now) {
                f[x.first + 1][x.second] = 1;
                b.push_back({x.first + 1, x.second});
                // printf("AAA (%d, %d)\n", x.first+1,x.second);
            }
        }
        std::swap(a, b);
    }
    for (auto c : ans) putchar(c);
    return puts(""), 0;
}