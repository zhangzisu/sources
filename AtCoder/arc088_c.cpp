#include <iostream>
#include <string>
#include <vector>
int n, m, sum[200010], vis[200010];
std::vector<int> p[26];
inline int lowbit(int x) { return x & -x; }
inline void add(int x, int y) {
    for (; x <= n; x += lowbit(x)) sum[x] += y;
}
inline int qry(int x) {
    register int ret = 0;
    while (x) {
        ret += sum[x];
        x -= lowbit(x);
    }
    return ret;
}
long long ans = 0;
int main() {
    std::string s;
    std::cin >> s;
    n = s.length();
    for (int i = 0; i < n; i++) p[s[i] - 'a'].push_back(i + 1);
    for (int i = 0; i < 26; i++) m += p[i].size() & 1;
    if (m > 1) {
        puts("-1");
        return 0;
    }
    for (int i = 1; i <= n; i++) add(i, 1);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            const int c = s[i - 1] - 'a';
            int j = p[c][p[c].size() - 1];
            if (i == j)
                ans += (qry(n) - qry(j)) >> 1;
            else
                ans += qry(n) - qry(j);
            vis[i] = vis[j] = 1;
            add(i, -1);
            add(j, -1);
            p[c].pop_back();
        }
    }
    std::cout << ans << std::endl;
    return 0;
}