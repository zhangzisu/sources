#include <bits/stdc++.h>
using namespace std;
int p = 1000000007;
vector<pair<int, int> > A, B;
vector<pair<int, int> > a, b;
int n, m;
int fuck(int x, long long y) {
    assert(y >= 0);
    int re = 1;
    for (; y; y >>= 1) {
        if (y & 1) {
            re = (long long)re * x % p;
        }
        x = (long long)x * x % p;
    }
    return re;
}

void fac(int n, vector<pair<int, int> > &a) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                n /= i;
                cnt++;
            }
            a.push_back(make_pair(i, cnt));
        }
    }
    if (n > 1) {
        a.push_back(make_pair(n, 1));
    }
}

long long gcd(int x, int y) {
    return y ? gcd(y, x % y) : x;
}

long long lcm(int x, int y) {
    return x / gcd(x, y) * y;
}

void gen(const vector<pair<int, int> > &A, vector<pair<int, int> > &a, int d, int x, int y) {
    if (d == A.size()) {
        a.push_back(make_pair(x, y));
        return;
    }
    for (int i = 0; i <= A[d].second; i++) {
        gen(A, a, d + 1, x, y);
        x *= A[d].first;
        if (i == 0) {
            y *= A[d].first - 1;
        } else {
            y *= A[d].first;
        }
    }
}

int calc(int n, int m) {
    int ans = 0;
    printf("%d %d\n", a.size(), b.size());
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            long long l = lcm(a[i].first, b[j].first);
            long long cnt = (long long)n * m / l;
            int d0 = (l / a[i].first) & 1;
            int d1 = (l / b[j].first) & 1;
            printf("FUCK %lld %lld\n", l, cnt);
            if (d0 && d1) {
                cnt -= n / a[i].first + m / b[j].first - 1;
            } else if (d0) {
                cnt -= n / a[i].first;
            } else if (d1) {
                cnt -= m / b[j].first;
            }
            printf("R %d\n",cnt);
            ans += (long long)fuck(2, cnt) * a[i].second % p * b[j].second % p;
            if (ans >= p) {
                ans -= p;
            }
            printf("%d\n", ans);
        }
    }
    printf("D %d\n", ans);
    ans = (long long)ans * fuck((long long)n * m % p, p - 2) % p;
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    fac(n, A);
    fac(m, B);
    gen(A, a, 0, 1, 1);
    gen(B, b, 0, 1, 1);
    printf("%d\n", calc(n, m));
    return 0;
}