#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MOD 1000000007
typedef long long lnt;

lnt n, m;
std::vector<std::pair<lnt, lnt>> a, b, A, B;
lnt gcd(lnt x, lnt y) { return y ? gcd(y, x % y) : x; }
lnt lcm(lnt x, lnt y) {
    return x / gcd(x, y) * y;
}
inline lnt fuck(lnt x, lnt p) {
    lnt y = 1;
    for (; p; p >>= 1) {
        if (p & 1) y = y * x % MOD;
        x = x * x % MOD;
    }
    return y;
}
void split(lnt x, std::vector<std::pair<lnt, lnt>> &out) {
    for (lnt i = 2, j; i * i < x; i++)
        if (!(x % i)) {
            j = 0;
            while (!(x % i)) x = x / i, j++;
            out.emplace_back(i, j);
        }
    if (x > 1) out.emplace_back(x, 1);
}
void dfs(lnt x, lnt y, lnt phi, std::vector<std::pair<lnt, lnt>> &in, std::vector<std::pair<lnt, lnt>> &out) {
    if (x >= (lnt)in.size()) {
        out.emplace_back(y, phi);
        return;
    }
    for (lnt i = 0; i <= in[x].second; i++) {
        dfs(x + 1, y, phi, in, out);
        y = y * in[x].first;
        phi *= in[x].first - (i == 0);
    }
}

int main() {
    scanf("%lld%lld", &n, &m);
    split(n, a);
    split(m, b);
    dfs(1, 1, 1, a, A);
    dfs(1, 1, 1, b, B);
    lnt ans = 0;
    for (lnt i = 0; i < (int)A.size(); i++)
        for (lnt j = 0; j < (int)B.size(); j++) {
            lnt k = A[i].first, l = B[j].first;
            lnt L = lcm(k, l);
            lnt x = 1LL * n * m / L;
            if ((L / l) & 1) x -= m / l;
            if ((L / k) & 1) x -= n / k;
            if (((L / k) & 1) && ((L / l) & 1)) x++;
            ans = (ans + A[i].second * B[j].second % MOD * fuck(2, x) % MOD) % MOD;
        }
    ans = ans * fuck(n, MOD - 2) % MOD * fuck(m, MOD - 2) % MOD;
    printf("%lld\n", ans);
    return 0;
}