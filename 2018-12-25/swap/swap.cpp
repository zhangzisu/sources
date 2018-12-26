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
    inline char getalpha() {
        register char ch = getchar();
        while (!isalpha(ch)) ch = getchar();
        return ch;
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
    inline long long getint64() {
        register long long x = 0, f = 0;
        register char ch = getchar();
        for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
        for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
        return f ? -x : x;
    }
    inline unsigned long long getuint64() {
        register unsigned long long x = 0;
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
    inline void print(const char *s) {
        for (; *s; s++) putchar(*s);
    }
    inline void puts(const char *s) {
        print(s);
        putchar(10);
    }
} io(fopen("swap.in", "r"), fopen("swap.out", "w"));
#include <queue>
#include <set>
#define MAXN 100010
#define MAXM 25000010
std::priority_queue<std::pair<int, int> > Q;
std::set<std::pair<int, int> > S;
int n, k, a[MAXN], d[MAXN];
int head[MAXN], to[MAXM], next[MAXM], tot = 0;
inline void $(int u, int v) { next[tot] = head[u], to[tot] = v, head[u] = tot++, d[v]++; }
int main() {
    memset(head, -1, sizeof(head));
    n = io.getint(), k = io.getint();
    for (int i = 1; i <= n; i++) a[i] = io.getint();
    if (n <= 5000) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                if (std::abs(a[i] - a[j]) > k) {
                    $(j, i);
                }
            }
        }
    } else {
        for (int i = 1; i <= n; i++) {
            int pre = 0;
            std::set<std::pair<int, int> >::iterator it = S.lower_bound(std::make_pair(a[i] + k, i));
            if (it != S.end()) pre = std::max(pre, it->second);
            it = S.upper_bound(std::make_pair(a[i] - k, 0));
            if (it != S.begin()) pre = std::max(pre, (--it)->second);
            if (pre) $(pre, i);
            S.insert(std::make_pair(a[i], i));
        }
    }
    for (int i = 1; i <= n; i++)
        if (!d[i]) Q.push(std::make_pair(-a[i], i));
    while (Q.size()) {
        int x = Q.top().second;
        Q.pop();
        io.putint(a[x]);
        io.putchar(32);
        for (int i = head[x]; ~i; i = next[i]) {
            if (!--d[to[i]]) {
                Q.push(std::make_pair(-a[to[i]], to[i]));
            }
        }
    }
    io.putchar(10);
    return 0;
}