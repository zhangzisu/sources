#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
class IO {
   protected:
    const static int BUF = 65536;
    FILE *in, *out;
    char ibuf[BUF], obuf[BUF], *icur, *ocur;
    int ilimit;

   public:
    inline IO(FILE *in = stdin, FILE *out = stdout) {
        this->in = in;
        this->out = out;
        this->icur = this->ibuf + BUF;
        this->ocur = this->obuf;
    }
    inline int getchar() {
        if (icur == ibuf + BUF) {
            ilimit = fread(ibuf, 1, BUF, in);
            icur = ibuf;
        }
        return (icur < ibuf + ilimit) ? *icur++ : -1;
    }
    inline void putchar(char c) {
        if (ocur == obuf + BUF) {
            fwrite(obuf, 1, BUF, out);
            ocur = obuf;
        }
        *ocur++ = c;
    }
    inline ~IO() {
        fwrite(obuf, 1, ocur - obuf, out);
    }
};
class IOX : public IO {
   public:
    inline IOX(FILE *in = stdin, FILE *out = stdout) : IO(in, out) {}
    inline int getint() {
        register int x = 0;
        register char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline long long getint64() {
        register long long x = 0;
        register char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline char getAlpha() {
        register char ch = getchar();
        while (!isalpha(ch)) ch = getchar();
        return ch;
    }
    inline void putint(int x) {
        if (x == 0) return putchar(48);
        if (x < 0) putchar(45), x = -x;
        static int s[32];
        int t = 0;
        for (; x; x /= 10) s[++t] = x % 10;
        for (; t; t--) putchar(s[t] ^ 48);
    }
    inline void putint64(long long x) {
        if (x == 0) return putchar(48);
        if (x < 0) putchar(45), x = -x;
        static int s[32];
        int t = 0;
        for (; x; x /= 10) s[++t] = x % 10;
        for (; t; t--) putchar(s[t] ^ 48);
    }
};
#include <queue>
#define MAXN 100010
typedef long long lnt;
int n, fa[MAXN], d[MAXN], v[MAXN], size[MAXN];
lnt cnt[MAXN], ans = 0;
std::queue<int> Q;
int main() {
    IOX io(fopen("lca.in", "r"), fopen("lca.out", "w"));
    n = io.getint();
    for (int i = 2; i <= n; i++) d[fa[i] = io.getint()]++;
    for (int i = 1; i <= n; i++) v[i] = io.getint();
    for (int i = 1; i <= n; i++)
        if (!d[i]) Q.push(i);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        size[fa[x]] += ++size[x];
        cnt[x] += 1LL * size[x] * size[x];
        cnt[fa[x]] -= 1LL * size[x] * size[x];
        ans += cnt[x] * v[x];
        if (!--d[fa[x]]) Q.push(fa[x]);
    }
    io.putint64(ans);
    io.putchar(10);
    for (int m = io.getint(), x, y, z; m; m--) {
        if (io.getAlpha() == 'P') {
            x = io.getint();
            z = y = io.getint();
            while (z && z != x) z = fa[z];
            if (z != x) std::swap(x, y);
            int pre = size[y];
            for (z = fa[y]; z; z = fa[z]) {
                cnt[z] += 2LL * pre * pre;
                ans += 2LL * pre * pre * v[z];
                cnt[z] -= 2LL * size[z] * pre;
                ans -= 2LL * size[z] * pre * v[z];
                std::swap(pre, size[z]);
                size[z] = pre - size[z];
            }
            for (z = fa[y]; fa[z]; z = fa[z]) {
                cnt[fa[z]] += 2LL * size[z] * size[fa[z]];
                ans += 2LL * size[z] * size[fa[z]] * v[fa[z]];
                size[fa[z]] += size[z];
            }
            pre = size[x];
            for (z = fa[x]; z; z = fa[z]) {
                cnt[z] += 2LL * pre * pre;
                ans += 2LL * pre * pre * v[z];
                cnt[z] -= 2LL * size[z] * pre;
                ans -= 2LL * size[z] * pre * v[z];
                std::swap(pre, size[z]);
                size[z] = pre - size[z];
            }
            cnt[x] += 2LL * size[x] * size[y];
            ans += 2LL * size[x] * size[y] * v[x];
            size[x] += size[y];
            for (z = x; z; z = fa[z]) {
                cnt[fa[z]] += 2LL * size[z] * size[fa[z]];
                ans += 2LL * size[z] * size[fa[z]] * v[fa[z]];
                size[fa[z]] += size[z];
            }
            fa[y] = x;
        } else {
            x = io.getint();
            y = io.getint();
            ans -= cnt[x] * v[x];
            ans += cnt[x] * (v[x] = y);
        }
        io.putint64(ans);
        io.putchar(10);
    }
}