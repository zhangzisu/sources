#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 100010
int n, k, m, t[MAXN], ans;
std::vector<std::pair<int, int>> vec;
std::vector<int> delta;
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &t[i]);
    int l = t[1], r = t[1];
    for (int i = 2; i <= n; i++) {
        if (t[i] != t[i - 1] + 1) {
            m++;
            vec.push_back({l, r});
            ans += r - l + 1;
            l = r = t[i];
        }
        r = t[i];
    }
    m++;
    vec.push_back({l, r});
    ans += r - l + 1;
    for (int i = 1; i < (int)vec.size(); i++) delta.push_back(vec[i].first - vec[i - 1].second - 1);
    std::sort(delta.begin(), delta.end());
    for (int i = 0; i < m - k; i++) ans += delta[i];
    printf("%d\n", ans);
    return 0;
}