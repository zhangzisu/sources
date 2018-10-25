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
#include <bitset>
#define MAXN 90
#define MAXM 10010
#define MAXD 20
int n, m, k, ans = 0;
int head[MAXN], to[MAXM << 1], val[MAXM << 1], next[MAXM << 1], tot = 0;
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, val[tot] = w, head[v] = tot++;
}
int f[2][MAXN][1 << MAXD], flag = 1;
int main() {
    IOX io = IOX();
    n = io.getint(), m = io.getint(), k = io.getint();
    if (!m) return puts("0"), 0;
    memset(head, -1, sizeof(head));
    for (int i = 1, u, v, w; i <= m; i++) {
        u = io.getint() - 1, v = io.getint() - 1, w = io.getint();
        $(u, v, w);
        flag &= (w == 0);
    }
    if (flag) return puts("1"), 0;
    f[0][0][0] = 1;
    for (int d = 1; d <= k; d++) {
        int now = d & 1, pre = now ^ 1;
        memset(f[now], 0, sizeof(f[now]));
        for (int p = 0; p < (1 << (d - 1)); p++) {
            for (int x = 0; x < n; x++) {
                for (int i = head[x]; ~i; i = next[i]) {
                    f[now][x][p << 1 | val[i]] |= f[pre][to[i]][p];
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
        for (int p = 0; p < (1 << k); p++)
            ans += f[k & 1][i][p];
    io.putint(ans);
    io.putchar(10);
    return 0;
}