#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
typedef long long lnt;
#define MAXN 1000010

lnt p[MAXN], cnt;
bool vis[MAXN];
void shai() {
    for (lnt i = 2; i < MAXN; i++) {
        if (!vis[i]) cnt++, p[cnt] = i;
        for (lnt j = 1; j <= cnt && i * p[j] < MAXN; j++) {
            vis[i * p[j]] = true;
            if (i % p[j] == 0) break;
        }
    }
}
lnt a[610], v[610];
std::map<lnt, lnt> _1;
std::map<lnt, bool> _2[610];
lnt gcd(lnt a, lnt b) { return b ? gcd(b, a % b) : a; }
inline bool check(lnt x) {
    lnt t = sqrt(x);
    return t * t == x;
}
inline lnt rand(lnt n) {
    return (((lnt)rand() << 30) + rand()) % n;
}
inline lnt mul(lnt a, lnt b, lnt p) {
    lnt tmp = a * b - (lnt)((long double)a / p * b + 1e-7) * p;
    return (tmp + p) % p;
}
inline lnt pow(lnt n, lnt m, lnt p) {
    lnt res = 1;
    for (; m; m >>= 1) {
        if (m & 1) res = mul(res, n, p);
        n = mul(n, n, p);
    }
    return res;
}
const lnt test_case = 50;
inline bool mr(lnt n) {
    if (n < 2) return false;
    if (n == 2) return true;
    for (lnt i = 0; i < test_case; i++) {
        lnt test_num = rand(n - 2) + 2;
        if (pow(test_num, n, n) != test_num) return false;
    }
    return true;
}
lnt n;
struct BigInteger {
    typedef unsigned long long lnt;

    static const lnt BASE = 1000000000000000000LL;
    static const lnt WIDTH = 18;
    std::vector<lnt> s;
    inline BigInteger& clean() {
        while (!s.back() && s.size() > 1) s.pop_back();
        return *this;
    }
    inline BigInteger(lnt num = 0) { *this = num; }
    inline BigInteger& operator=(long long num) {
        s.clear();
        do {
            s.push_back(num % BASE);
            num /= BASE;
        } while (num > 0);
        return *this;
    }

    inline BigInteger operator+(const BigInteger& b) const {
        BigInteger c;
        c.s.clear();
        for (lnt i = 0, g = 0;; i++) {
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;
            lnt x = g;
            if (i < s.size()) x += s[i];
            if (i < b.s.size()) x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }
    inline BigInteger operator-(const BigInteger& b) const {
        BigInteger c;
        c.s.clear();
        for (lnt i = 0, g = 0;; i++) {
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;
            lnt x = s[i] + g;
            if (i < b.s.size()) x -= b.s[i];
            if (x < 0) {
                g = -1;
                x += BASE;
            } else
                g = 0;
            c.s.push_back(x);
        }
        return c.clean();
    }
    inline BigInteger operator*(const BigInteger& b) const {
        lnt i, j;
        lnt g;
        std::vector<lnt> v(s.size() + b.s.size(), 0);
        BigInteger c;
        c.s.clear();
        for (i = 0; i < s.size(); i++)
            for (j = 0; j < b.s.size(); j++) v[i + j] += lnt(s[i]) * b.s[j];
        for (i = 0, g = 0;; i++) {
            if (g == 0 && i >= v.size()) break;
            lnt x = v[i] + g;
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c.clean();
    }
    inline BigInteger& operator+=(const BigInteger& b) {
        *this = *this + b;
        return *this;
    }
    inline BigInteger& operator-=(const BigInteger& b) {
        *this = *this - b;
        return *this;
    }
    inline BigInteger& operator*=(const BigInteger& b) {
        *this = *this * b;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& out, const BigInteger& x) {
    out << x.s.back();
    for (lnt i = x.s.size() - 2; i >= 0; i--) {
        char buf[20];
        sprintf(buf, "%018lld", x.s[i]);
        for (lnt j = 0; j < (lnt)strlen(buf); j++) out << buf[j];
    }
    return out;
}
BigInteger d(1);
int main() {
    shai();
    scanf("%lld", &n);
    for (lnt i = 1, j; i <= n; i++) {
        scanf("%lld", &a[i]);
        j = 1;
        while (a[i] != 1 && j <= cnt) {
            while (a[i] % p[j] == 0) {
                a[i] /= p[j];
                _1[p[j]]++;
            }
            j++;
        }
    }
    std::sort(a + 1, a + n + 1);
    for (lnt i = 1; i < n; i++) {
        if (a[i + 1] == a[i]) {
            v[i]++;
            for (lnt j = i + 1; j < n; j++)
                a[j] = a[j + 1];
            n--;
            i--;
        }
    }
    for (lnt i = 1; i <= n; i++)
        v[i]++;
    for (lnt i = 1; i <= n; i++)
        for (lnt j = i + 1; j <= n; j++) {
            lnt x = gcd(a[i], a[j]);
            if (x != 1) _2[i][x] = _2[j][x] = true;
        }
    lnt maxn = 1, ans = 0;
    for (lnt i = 1; i <= n; i++)
        if (a[i] != 1) {
            if (check(a[i]))
                _1[(lnt)sqrt(a[i])] += v[i] * 2;
            else {
                if (_2[i].size() == 2) {
                    auto it = _2[i].begin();
                    _1[it->first] += v[i];
                    it++;
                    _1[it->first] += v[i];
                } else if (_2[i].size() == 1) {
                    auto it = _2[i].begin();
                    _1[it->first] += v[i];
                    if (it->first != a[i]) {
                        if (v[i] > maxn)
                            maxn = v[i], ans = 1;
                        else if (v[i] == maxn)
                            ans++;
                    }
                } else if (mr(a[i])) {
                    if (v[i] > maxn)
                        maxn = v[i], ans = 1;
                    else if (v[i] == maxn)
                        ans++;
                } else {
                    if (v[i] > maxn)
                        maxn = v[i], ans = 2;
                    else if (v[i] == maxn)
                        ans += 2;
                }
            }
        }
    for (auto x : _1) {
        if (x.second == maxn)
            ans++;
        else if (x.second > maxn)
            maxn = x.second, ans = 1;
    }
    printf("%lld\n", maxn);
    // printf("%lld\n", ans);
    for (lnt i = 0; i < ans; i++) d *= 2;
    d -= 1;
    std::cout << d << std::endl;
}
