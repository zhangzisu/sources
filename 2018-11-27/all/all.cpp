#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
class IO {
   protected:
    static const int BSIZE = 65536;
    int is;
    char ib[BSIZE], ob[BSIZE], *ip, *op;
    FILE *in, *out;

   public:
    inline IO(FILE *in = stdin, FILE *out = stdout) {
        ip = ib + BSIZE, op = ob, is = 0;
        this->in = in;
        this->out = out;
    }
    inline ~IO() {
        fwrite(ob, 1, op - ob, out);
    }
    inline char getchar() {
        if (ip == ib + BSIZE) is = fread(ib, 1, BSIZE, in), ip = ib;
        return ip == ib + is ? 0 : *ip++;
    }
    inline void putchar(char c) {
        if (op == ob + BSIZE) fwrite(ob, 1, BSIZE, out), op = ob;
        *op++ = c;
    }
};
class IOX : public IO {
   protected:
    int tmp[64];

   public:
    inline IOX(FILE *in = stdin, FILE *out = stdout) : IO(in, out) {}
    inline int getdigit() {
        register char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        return ch ^ 48;
    }
    inline int getint() {
        register int x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline long long getint64() {
        register long long x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline void putint(int x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void putint64(long long x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        register int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void puts(const char *s) {
        for (; *s; s++) putchar(*s);
    }
};
#define MAXN 100010
#define LOGN 60
typedef long long lnt;
int n, son[MAXN * LOGN][2], size[MAXN * LOGN], cnt = 1;
lnt a[MAXN], ans;
int query(int p, int d, lnt v, lnt l, lnt r, lnt msk) {
    if (!p) return 0;
    lnt L = v;
    lnt R = v + (1LL << (d + 1)) - 1;
    // printf("query %lld - %lld, %lld - %lld, %d, %d\n", L, R, l, r, p, d);
    if (L == l && R == r) return size[p];
    lnt mid = v + (1LL << d);
    if (r < mid) return query(son[p][(msk >> d) & 1], d - 1, v, l, r, msk);
    if (l >= mid) return query(son[p][(~msk >> d) & 1], d - 1, mid, l, r, msk);
    return query(son[p][(msk >> d) & 1], d - 1, v, l, mid - 1, msk) + query(son[p][(~msk >> d) & 1], d - 1, mid, mid, r, msk);
}
int main() {
    IOX io(fopen("all.in", "r"), fopen("all.out", "w"));
    n = io.getint();
    for (int i = 1; i <= n; i++) {
        a[i] = io.getint64();
        int p = 1;
        for (int j = LOGN; ~j; j--) {
            int t = (a[i] >> j) & 1;
            size[p]++;
            if (!son[p][t]) son[p][t] = ++cnt;
            p = son[p][t];
        }
        size[p]++;
    }
    for (int i = 1; i <= n; i++) {
        ans += 1LL * query(1, LOGN, 0, 1LL, 9LL, a[i]);
        ans += 2LL * query(1, LOGN, 0, 10LL, 99LL, a[i]);
        ans += 3LL * query(1, LOGN, 0, 100LL, 999LL, a[i]);
        ans += 4LL * query(1, LOGN, 0, 1000LL, 9999LL, a[i]);
        ans += 5LL * query(1, LOGN, 0, 10000LL, 99999LL, a[i]);
        ans += 6LL * query(1, LOGN, 0, 100000LL, 999999LL, a[i]);
        ans += 7LL * query(1, LOGN, 0, 1000000LL, 9999999LL, a[i]);
        ans += 8LL * query(1, LOGN, 0, 10000000LL, 99999999LL, a[i]);
        ans += 9LL * query(1, LOGN, 0, 100000000LL, 999999999LL, a[i]);
        ans += 10LL * query(1, LOGN, 0, 1000000000LL, 9999999999LL, a[i]);
        ans += 11LL * query(1, LOGN, 0, 10000000000LL, 99999999999LL, a[i]);
        ans += 12LL * query(1, LOGN, 0, 100000000000LL, 999999999999LL, a[i]);
        ans += 13LL * query(1, LOGN, 0, 1000000000000LL, 9999999999999LL, a[i]);
        ans += 14LL * query(1, LOGN, 0, 10000000000000LL, 99999999999999LL, a[i]);
        ans += 15LL * query(1, LOGN, 0, 100000000000000LL, 999999999999999LL, a[i]);
        ans += 16LL * query(1, LOGN, 0, 1000000000000000LL, 9999999999999999LL, a[i]);
        ans += 17LL * query(1, LOGN, 0, 10000000000000000LL, 99999999999999999LL, a[i]);
        ans += 18LL * query(1, LOGN, 0, 100000000000000000LL, 999999999999999999LL, a[i]);
        ans += 19LL * query(1, LOGN, 0, 1000000000000000000LL, 1152921504606846975LL, a[i]);
    }
    io.putint64(ans / 2);
    io.putchar(10);
    return 0;
}