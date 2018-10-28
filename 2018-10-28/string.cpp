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
        char ch = getchar();
        while (!isdigit(ch)) ch = getchar();
        return ch ^ 48;
    }
    inline int getint() {
        int x = 0, f = 0;
        char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned getuint() {
        unsigned x = 0;
        char ch = getchar();
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return x;
    }
    inline void putint(int x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void putint64(long long x) {
        if (!x) return putchar('0');
        if (x < 0) putchar(45), x = -x;
        int _6;
        for (_6 = 0; x; x /= 10) tmp[++_6] = (x % 10) ^ 48;
        while (_6) putchar(tmp[_6--]);
    }
    inline void puts(const char *s) {
        for (; *s; s++) putchar(*s);
    }
};
#include <queue>
#define MOD 1000000007
#define MAXN 10
struct trie {
    int son[2], danger, fail;
    inline int &operator[](int index) {
        return son[index];
    }
} acm[MAXN];
int cnt, n, m, p, mask, ans, f[10][1010], g[10][1010];
inline void init() { cnt = 1, memset(acm, 0, sizeof(acm)); }
inline void insert(int i) {
    int q = cnt;
    for (int d = 0; d < p; d++) {
        int &next = acm[q][(i >> d) & 1];
        if (!next) next = ++cnt;
        q = next;
    }
    acm[q].danger = 1;
}
std::queue<int> Q;
inline void build() {
    Q.push(1);
    while (Q.size()) {
        int x = Q.front();
        Q.pop();
        for (int i = 0; i < 2; i++) {
            int &y = acm[x][i];
            if (y) {
                acm[y].fail = acm[x].fail ? acm[acm[x].fail][i] : 1;
                Q.push(y);
            } else {
                y = acm[x].fail ? acm[acm[x].fail][i] : 1;
            }
            if (acm[x].fail) acm[x].danger |= acm[acm[x].fail].danger;
        }
    }
}
inline void up(int &x, int y) {
    if ((x += y) >= MOD) x -= MOD;
}
int main() {
    IOX io = IOX();
    n = io.getint(), m = io.getint(), p = io.getint();
    if (n < 2 * p) return puts("0"), 0;
    mask = (1 << p) - 1;
    for (int i = 0; i < (1 << p); i++) {
        init(), insert(i), build();
        memset(f, 0, sizeof(f));
        f[1][0] = 1;
        for (int j = p + 1; j <= n; j++) {
            memset(g, 0, sizeof(g));
            for (int k = 1; k <= cnt; k++) {
                for (int l = 0; l <= n; l++) {
                    if (!f[k][l]) continue;
                    for (int d = 0; d < 2; d++) {
                        int next = acm[k][d];
                        up(g[next][l + acm[next].danger], f[k][l]);
                    }
                }
            }
            memcpy(f, g, sizeof(g));
        }
        for (int j = 1; j <= cnt; j++) {
            for (int k = m; k <= n; k++) {
                up(ans, f[j][k]);
            }
        }
    }
    io.putint(ans);
    io.putchar(10);
    return 0;
}