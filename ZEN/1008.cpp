#pragma GCC optimize("O3")
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#define MAXK 2010
#define MAXN 1000100

namespace hashMap {
    const int hashBase = 999997;
    typedef std::pair<int, int> state;
    typedef unsigned long long ull;
    struct node {
        node *next;
        ull val;
        int ans;
        node(node *next, ull val, int ans): next(next), val(val), ans(ans) {}
        node() {}
    }pool[MAXN], *first[hashBase];
    inline ull getHash(const state &val) {
        return (ull)val.first * MAXK + val.second;
    }
    inline node* find(const ull &val) {
        int pos = val % hashBase;
        for (node *cur = first[pos]; cur; cur = cur->next)
            if (cur->val == val) return cur;
        return NULL;
    }
    inline int insert(const ull &val, const int &ans) {
        static node *pit;
        if (!pit) pit = pool;
        int pos = val % hashBase;
        first[pos] = new(pit++) node(first[pos], val, ans);
        return ans;
    }
}

int vis[MAXN], mu[MAXN], pri[MAXN], fi[MAXN], pfx[MAXN], cnt = 0;
inline int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
inline void shai() {
    mu[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (!vis[i]) pri[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt; j++) {
            if (i * pri[j] >= MAXN) break;
            vis[i * pri[j]] = 1;
            if (i % pri[j]) {
                mu[i * pri[j]] = -mu[i];
            } else {
                mu[i * pri[j]] = 0;
                break;
            }
        }
    }
    for (int i = 1; i < MAXN; i++) pfx[i] = pfx[i - 1] + mu[i];
}
inline int D(int n, int k) {
    if (n == 0 || (k == 1 && n < MAXN)) return pfx[n];
    unsigned long long val = hashMap::getHash(std::make_pair(n, k));
    hashMap::node *cur = hashMap::find(val);
    if (cur) return cur->ans;
    int ans;
    if (k == 1) {
        ans = 1;
        for (int i = 2, j = 2; i <= n; i = j + 1) {
            j = n / (n / i);
            ans -= (j - i + 1) * D(n / i, k);
        }
    } else {
        ans = 0;
        for (int i = 1; i * i <= k; ++i) if (k % i == 0) {
            if (mu[i]) ans += D(n / i, i);
            if (i * i != k && mu[k / i])ans += D(n / (k / i), k / i);
        }
    }
    hashMap::insert(val, ans);
    return ans;
}
inline long long F(int n, int k) { return 1LL * (n / k) * fi[k - 1] + fi[n % k]; }

int n, m, k;
long long ans = 0, pre = 0, now;
int main() {
    scanf("%d%d%d", &n, &m, &k); shai();
    for (int i = 1; i <= k; i++) fi[i] = fi[i - 1] + (gcd(i, k) == 1);
    for (int i = 1, j; i <= n && i <= m; i = j + 1) {
        j = std::min(n / (n / i), m / (m / i));
        now = D(j, k);
        ans += (now - pre) * (n / i) * F(m / i, k);
        pre = now;
    }
    printf("%lld\n", ans);
    return 0;
}