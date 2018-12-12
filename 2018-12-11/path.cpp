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
        putchar(10);
    }
};
#include <vector>
#define MAXN 100010
int n, m, d[MAXN], head[MAXN], next[MAXN << 1], to[MAXN << 1], use[MAXN << 1], tot = 0;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
    d[u]++, d[v]++;
}
int vis[MAXN], tim = 0, tmp;
void dfs(int x) {
    if (vis[x]) return;
    vis[x] = tim;
    ++tmp;
    for (int i = head[x]; ~i; i = next[i]) dfs(to[i]);
}
std::vector<int> ans, ans1, ans2;
void euler(int x) {
    for (int i = head[x]; ~i; i = next[i]) {
        if (use[i]) continue;
        use[i] = use[i ^ 1] = 1;
        head[x] = next[i];
        euler(to[i]);
        ans.push_back((i >> 1) + 1);
    }
}
int id[3], cnt = 0;
int main() {
    IOX io = IOX(fopen("input.txt", "r"), fopen("output.txt", "w"));
    n = 100000, m = io.getint();
    if (m <= 1) return io.puts("-1"), 0;
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= m; i++) $(io.getint(), io.getint());
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            ++tim;
            tmp = 0;
            dfs(i);
            if (tmp > 1) {
                if (++cnt > 2) return io.puts("-1"), 0;
                id[cnt] = tim;
            }
        }
    }
    if (cnt == 2) {
        int x = 0, y = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[i] == id[1]) {
                x += d[i] & 1;
                if (!y || d[i] & 1) y = i;
            }
        }
        if (x != 0 && x != 2) return io.puts("-1"), 0;
        euler(y);
        std::swap(ans, ans1);
        x = 0, y = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[i] == id[2]) {
                x += d[i] & 1;
                if (!y || d[i] & 1) y = i;
            }
        }
        if (x != 0 && x != 2) return io.puts("-1"), 0;
        euler(y);
        std::swap(ans, ans2);
        io.putint((int)ans1.size()), io.putchar(10);
        for (auto i : ans1) io.putint(i), io.putchar(32);
        io.puts("");
        io.putint((int)ans2.size()), io.putchar(10);
        for (auto i : ans2) io.putint(i), io.putchar(32);
        io.puts("");
        return 0;
    }
    int x = 0;
    for (int i = 1; i <= n; i++)
        if (vis[i] == id[1])
            x += d[i] & 1;
    if (x != 0 && x != 2 && x != 4) return io.puts("-1"), 0;
    if (x == 0 || x == 2) {
        for (int i = 1; i <= n; i++) {
            if (vis[i] == id[1] && (x == 0 || (d[i] & 1))) {
                euler(i);
                io.putint((int)ans.size() - 1), io.putchar(10);
                for (int i = 1; i < (int)ans.size(); i++) io.putint(ans[i]), io.putchar(32);
                io.puts("");
                io.puts("1");
                io.putint(ans[0]), io.putchar(10);
                return 0;
            }
        }
    }
    int u = 0, v = 0, w = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == id[1] && (d[i] & 1)) {
            (u ? v ? w : v : u) = i;
        }
    }
    $(u, v);
    euler(w);
    w = 0;
    for (auto x : ans) {
        if (x > m) {
            w = 1;
        } else {
            (w ? ans1 : ans2).push_back(x);
        }
    }
    io.putint((int)ans1.size()), io.putchar(10);
    for (auto i : ans1) io.putint(i), io.putchar(32);
    io.puts("");
    io.putint((int)ans2.size()), io.putchar(10);
    for (auto i : ans2) io.putint(i), io.putchar(32);
    io.puts("");
    return 0;
}