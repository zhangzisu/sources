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
    inline unsigned getuint() {
        register unsigned x = 0;
        register char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
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
typedef long long lnt;
const lnt INF = ~0U;
int head[MAXN], to[MAXN << 1], val[MAXN << 1], next[MAXN << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int n, k;
lnt mid, ans = 0;
inline void up(std::pair<lnt, int> &a, std::pair<lnt, int> b) {
    if (b.first > a.first || (b.first == a.first && b.second < a.second)) a = b;
}
inline std::pair<lnt, int> operator^(std::pair<lnt, int> a, std::pair<lnt, int> b) {
    up(a, b);
    return a;
}
inline std::pair<lnt, int> operator+(std::pair<lnt, int> a, std::pair<lnt, int> b) {
    return std::make_pair(a.first + b.first, a.second + b.second);
}
std::pair<lnt, int> f[MAXN][3], g[3];
void dp(int x, int fa) {
    f[x][0] = std::make_pair(0LL, 0);
    f[x][1] = f[x][2] = std::make_pair(-mid, 1);
    for (int i = head[x]; ~i; i = next[i]) {
        if (to[i] == fa) continue;
        dp(to[i], x);
        for (int j = 0; j < 3; j++) g[j] = f[x][j];
        auto max = f[to[i]][0] ^ f[to[i]][1] ^ f[to[i]][2];
        up(f[x][0], g[0] + max);
        up(f[x][1], g[0] + f[to[i]][1] + std::make_pair(val[i], 0));
        up(f[x][1], g[1] + max);
        up(f[x][2], g[1] + f[to[i]][1] + std::make_pair(val[i] + mid, -1));
        up(f[x][2], g[2] + max);
    }
}
int main() {
    IOX io = IOX(fopen("void.in", "r"), fopen("void.out", "w"));
    memset(head, -1, sizeof(head));
    n = io.getint(), k = io.getint();
    for (int i = 1; i < n; i++) {
        int u = io.getint(), v = io.getint(), w = io.getint();
        $(u, v, w);
    }
    lnt l = -INF, r = INF;
    while (l <= r) {
        mid = (l + r) >> 1;
        dp(1, 0);
        if ((f[1][0] ^ f[1][1] ^ f[1][2]).second <= k) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    mid = r + 1;
    dp(1, 0);
    io.putint64((f[1][0] ^ f[1][1] ^ f[1][2]).first + k * mid);
    io.putchar(10);
    return 0;
}