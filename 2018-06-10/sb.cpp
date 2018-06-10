#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

class SquadConstructor2 {
    static const int SIZE = 43046721;
    vector<vector<uint64_t>> reach;
    vector<int> w;
    int n, k;

   public:
    int teamget(int n, int k, vector<int> friends) {
        this->n = n;
        this->k = k;
        reach.resize(k + 1);
        w.resize(n + 1);
        w[0] = 1;
        for (int i = 1; i <= n; i++)
            w[i] = w[i - 1] * 9;
        vi scores;
        for (int i = 0; i <= k; i++)
            reach[i].resize(w[n] / 64 + 3);
        reach[0][0] = 1;
        vector<int> ss;
        for (int f : friends) {
            int s = 0;
            for (int i = 0; i < n; i++)
                if (f & (1 << i))
                    s += w[i];
            ss.push_back(s);
        }
        sort(ss.begin(), ss.end());

        vi top(k + 1);
        for (int s : ss) {
            int jump = s / 64;
            int shift = s % 64;
            for (int u = k - 1; u >= 0; u--) {
                if (shift != 0) {
                    int rshift = 64 - shift;
                    for (int i = 0; i <= top[u] && i + jump + 1 < SZ(reach[u]); i++) {
                        reach[u + 1][i + jump] |= reach[u][i] << shift;
                        reach[u + 1][i + jump + 1] |= reach[u][i] >> rshift;
                    }
                } else {
                    for (int i = 0; i <= top[u] && i + jump + 1 < SZ(reach[u]); i++)
                        reach[u + 1][i + jump] |= reach[u][i] << shift;
                }
                top[u + 1] = max(top[u + 1], top[u] + jump + 1);
            }
        }
        int ans = 0;
        for (int i = 0; i < w[n]; i++)
            if (reach[k][i >> 6] & 1LL << (i & 63)) {
                int score = 0;
                int v = i;
                for (int j = 0; j < n; j++) {
                    int m = v % 9;
                    v /= 9;
                    score += m * m;
                }
                ans = max(ans, score);
            }
        return ans;
    }
};

int main() {
    int n, m, k;
    vector<int> ss;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        ss.push_back(x);
    }
    SquadConstructor2 a;
    int Ans;
    printf("%d\n", Ans = a.teamget(m, k, ss));
    cerr << Ans << endl;
}