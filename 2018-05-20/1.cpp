#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#define MAXN 100

int n, m, a[MAXN], ans = 0;
std::set<unsigned long long> S0, S1;
std::map<int, int> ls, mr;
const unsigned long long base = 23, mod = 998244353;

inline int fpow(int x, int p) {
    int y = 1;
    while (p) {
        if (p & 1) y = 1LL * y * x % mod;
        x = 1LL * x * x % mod;
        p >>= 1;
    }
    return y;
}

int main() {
    scanf("%d", &n);
    m = (n << 1) - 1;
    bool flag = 1;
    int ddd0 = 0, ddd1 = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
        flag &= (a[i] <= 2);
        if (a[i] == 1)
            ddd0++;
        else
            ddd1++;
    }
    if (flag) {
        printf("%d\n", fpow(2, std::min(ddd0, ddd1)));
        return 0;
    }
    std::sort(a + 1, a + m);
    unsigned long long hs0, hs1;

    do {
        hs0 = a[1], hs1 = a[1];
        ls.clear();
        mr.clear();
        int mid = a[1], cl = 0, cm = 0;

        for (int i = 1; i < n; i++) {
            int x = a[i << 1], y = a[i << 1 | 1];
            (x < mid ? ls : mr)[x]++;
            (x < mid ? cl : cm)++;
            (y < mid ? ls : mr)[y]++;
            (y < mid ? cl : cm)++;
            if (cl < cm) {
                ls[mid]++;
                cl++;
                mid = mr.begin()->first;
                if (!--mr.begin()->second) mr.erase(mr.begin()->first);
                cm--;
            }
            if (cm < cl) {
                mr[mid]++;
                cm++;
                mid = ls.rbegin()->first;
                if (!--ls.rbegin()->second) ls.erase(ls.rbegin()->first);
                cl--;
            }
            hs0 = hs0 * base + mid;
            hs1 = (hs1 * base + mid) % mod;
        }
        if (S0.count(hs0) && S1.count(hs1)) {
            continue;
        }
        ans++;
        S0.insert(hs0);
        S1.insert(hs1);
    } while (std::next_permutation(a + 1, a + m + 1));
    printf("%d\n", ans);
    return 0;
}