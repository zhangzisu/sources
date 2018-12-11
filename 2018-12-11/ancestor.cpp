#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
#define MAXN 110
int n, ans = MAXN;
std::queue<std::string> Q;
std::string s1, s2, rule;
std::vector<char> map[256][256];
int son1[1000010][26], vis1[1000010], cnt1 = 1;
int son2[1000010][26], vis2[1000010], cnt2 = 1;
int main() {
    fropen("ancestor.in", "r", stdin);
    fropen("ancestor.out", "r", stdout);
    std::cin >> s1 >> s2 >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> rule;
        map[(int)rule[3]][(int)rule[4]].push_back(rule[0]);
    }
    Q.push(s1);
    while (Q.size()) {
        auto s = Q.front();
        Q.pop();
        int p = 1;
        for (int i = 1; i < (int)s.length(); i++) {
            for (auto c : map[(int)s[i - 1]][(int)s[i]]) {
                int q = son1[p][c - 'a'];
                if (!q) q = son1[p][c - 'a'] = ++cnt1;
                for (int j = i + 1; j < (int)s.length(); j++) {
                    int &nx = son1[q][s[j] - 'a'];
                    if (!nx) nx = ++cnt1;
                    q = nx;
                }
                if (!vis1[q]) {
                    vis1[q] = 1;
                    Q.push(s.substr(0, i - 1) + c + s.substr(i + 1));
                }
            }
            int &nx = son1[p][s[i - 1] - 'a'];
            if (!nx) nx = ++cnt1;
            p = nx;
        }
    }
    Q.push(s2);
    while (Q.size()) {
        auto s = Q.front();
        Q.pop();
        int p = 1;
        for (int i = 0; i < (int)s.length(); i++) {
            if (!(p = son1[p][s[i] - 'a'])) break;
        }
        if (vis1[p]) ans = std::min(ans, (int)s.length());
        p = 1;
        for (int i = 1; i < (int)s.length(); i++) {
            for (auto c : map[(int)s[i - 1]][(int)s[i]]) {
                int q = son2[p][c - 'a'];
                if (!q) q = son2[p][c - 'a'] = ++cnt2;
                for (int j = i + 1; j < (int)s.length(); j++) {
                    int &nx = son2[q][s[j] - 'a'];
                    if (!nx) nx = ++cnt2;
                    q = nx;
                }
                if (!vis2[q]) {
                    vis2[q] = 1;
                    Q.push(s.substr(0, i - 1) + c + s.substr(i + 1));
                }
            }
            int &nx = son2[p][s[i - 1] - 'a'];
            if (!nx) nx = ++cnt2;
            p = nx;
        }
    }
    printf("%d\n", ans);
    return 0;
}