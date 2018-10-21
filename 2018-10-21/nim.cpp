#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
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
    inline BigInteger& operator=(lnt num) {
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
    inline void print() {
        printf("%llu", s.back());
        for (int i = s.size() - 2; i >= 0; i--) {
            printf("%018llu", s[i]);
        }
    }
};
int n, m, k, t, a[1010], b[10100], c[1010];
BigInteger tmp, ans;
char buf[1010];
int main() {
    freopen("nim.in", "r", stdin);
    freopen("nim.out", "w", stdout);
    for (scanf("%d", &t); t; t--) {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        m = 0;
        scanf("%s", buf + 1);
        n = strlen(buf + 1);
        for (int i = 1; i <= n; i++) a[n - i + 1] = buf[i] - '0';
        memcpy(c, a, sizeof(c));
        k = n;
        while (n) {
            int pre = 0;
            for (int i = n; i >= 1; i--) {
                int now = pre * 10 + a[i];
                a[i] = now / 2;
                pre = now - a[i] * 2;
            }
            b[++m] = pre;
            while (!a[n] && n) n--;
        }
        // for (int i = 1; i <= m; i++) printf("%d", b[i]);
        // puts("");
        if (b[1]) {
            if (b[2]) {
                puts("0");
            } else {
                for (int i = k, pre = 0; i >= 1; i--) {
                    int now = pre * 10 + c[i];
                    c[i] = now / 2;
                    pre = now - c[i] * 2;
                }
                c[1]++;
                for (int p = 1; c[p] > 9; p++) {
                    c[p + 1] += c[p] / 10;
                    c[p] %= 10;
                }
                while (c[k + 1]) k++;
                while (k) putchar(c[k--] + 48);
                putchar(10);
            }
        } else {
            b[m--] = 0;
            while (!b[m] && m) m--;
            b[1]++;
            for (int p = 1; b[p] > 1; p++) {
                b[p + 1] += b[p] / 2;
                b[p] %= 2;
            }
            while (b[m + 1]) m++;
            tmp = 1;
            ans = 0;
            for (int i = 1; i <= m; i++) {
                if (b[i]) ans += tmp;
                tmp *= 2;
            }
            ans.print();
            puts("");
        }
    }
    return 0;
}