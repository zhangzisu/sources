#include <iostream>
#include <string>
#define MAXS 50010
#define MOD 1000000007
std::string s, l, r;
int son[MAXS][10], fail[MAXS], sum[MAXS], root, cnt, d;
inline void insert(int pos) {
    int p = root;
    for (int i = pos; i < pos + (d / 2); i++) {
        const int x = s[i] - '0';
        if (!son[p][x]) son[p][x] = ++cnt;
        p = son[p][x];
    }
    sum[p]++;
}
int Q[MAXS], H, T;
inline void build() {
    Q[H = T = 0] = root;
    fail[root] = 0;
    while (H <= T) {
        int p = Q[H++];
        for (int i = 0; i < 10; i++) {
            int &s = son[p][i];
            if (!s)
                s = son[fail[p]][i];
            else {
                fail[s] = son[fail[p]][i];
                Q[++T] = s;
            }
        }
    }
}
int f[55][MAXS][2][2][2];
int main() {
    std::cin >> s;
    std::cin >> l >> r;
    d = l.length();
    root = ++cnt;
    for (int i = 0; i < 10; i++) son[0][i] = root;
    for (unsigned i = 0; i + (d / 2) <= s.length(); i++) insert(i);
    build();
    f[0][root][1][1][0] = 1;
    for (int i = 0; i < d; i++) {
        for (int j = 1; j <= cnt; j++) {
            for (int s = 0; s <= 1; s++) {
                for (int e = 0; e <= 1; e++) {
                    for (int q = 0; q <= 1; q++) {
                        if (!f[i][j][s][e][q]) continue;
                        int S = s ? l[i] - '0' : 0;
                        int E = e ? r[i] - '0' : 9;
                        for (int k = S; k <= E; k++) {
                            int next = son[j][k];
                            (f[i + 1][next][s && k == S][e && k == E]
                              [q || sum[next]] += f[i][j][s][e][q]) %= MOD;
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= cnt; i++)
        for (int j = 0; j <= 1; j++)
            for (int k = 0; k <= 1; k++) (ans += f[d][i][j][k][1]) %= MOD;
    std::cout << ans << std::endl;
}