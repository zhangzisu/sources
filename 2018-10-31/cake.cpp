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
    inline int getUpper() {
        char ch = getchar();
        while (!isupper(ch)) ch = getchar();
        return ch - 65;
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
#include <vector>
#define MAXN 500010
typedef long long lnt;
int n, a[MAXN], b[MAXN], c[MAXN], du[5], vis[MAXN], p[5];
int min[6] = {-1, -1, -1, -1, -1, -1};
inline int id(int u, int v) {
    if (u > v) std::swap(u, v);
    if (u == 1) return v - 2;
    if (u == 2) return v;
    return 5;
}
inline int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
lnt ans, sum[5];
int main() {
    IOX io = IOX();
    n = io.getint();
    for (int i = 1; i <= n; i++) {
        // a[i] = io.getint();
        c[i] = io.getint();
        // b[i] = io.getint();
        a[i] = io.getUpper() - 21;
        b[i] = io.getUpper() - 21;
        int p = id(a[i], b[i]);
        if (min[p] == -1 || c[i] < c[min[p]]) min[p] = i;
    }
    for (int d = 0; d < (1 << 6); d++) {
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < 6; i++) {
            if ((d >> i) & 1) {
                if (min[i] == -1) goto next;
                vis[min[i]] = 1;
            }
        }
        for (int i = 1; i <= 4; i++) p[i] = i;
        memset(sum, 0, sizeof(sum));
        memset(du, 0, sizeof(du));
        for (int i = 1; i <= n; i++) {
            if (vis[i]) continue;
            p[find(a[i])] = find(b[i]);
            printf("M %d %d\n", find(a[i]), find(b[i]));
        }
        for (int i = 1; i <= n; i++) {
            if (vis[i]) continue;
            sum[find(a[i])] += c[i], du[a[i]]++, du[b[i]]++;
        }
        for (int i = 1; i <= 4; i++) {
            if (find(i) != i) continue;
            int cnt = 0;
            for (int j = 1; j <= i; j++) {
                if (find(j) != i) continue;
                printf("[%d] ", du[j]);
                cnt += du[j] & 1;
            }
            printf("%d %d %lld\n", d, cnt, sum[i]);
            if (cnt == 0 || cnt == 2) ans = std::max(ans, sum[i]);
        }
    next:;
    }
    io.putint64(ans);
    io.putchar(10);
}