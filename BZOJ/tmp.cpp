#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define inf 0x3f3f3f3f
#define N 1100
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
int n, k, a[N], l[N], r[N], h[N], num = 1, nn = 0, T = 1001, ans = 0, dis[N], path[N];
bool inq[N];
struct edge {
    int to, next, cap, val;
} data[5000];
inline void add(int x, int y, int cap, int val) {
    data[++num].to = y;
    data[num].next = h[x];
    h[x] = num;
    data[num].cap = cap;
    data[num].val = val;
    data[++num].to = x;
    data[num].next = h[y];
    h[y] = num;
    data[num].cap = 0;
    data[num].val = -val;
}
inline bool spfa() {
    queue<int> q;
    memset(dis, 128, sizeof(dis));
    memset(path, 0, sizeof(path));
    q.push(0);
    dis[0] = 0;
    inq[0] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        inq[x] = 0;
        for (int i = h[x]; i; i = data[i].next) {
            int y = data[i].to;
            if (!data[i].cap) continue;
            if (dis[x] + data[i].val > dis[y]) {
                dis[y] = dis[x] + data[i].val;
                path[y] = i;
                if (!inq[y]) inq[y] = 1, q.push(y);
            }
        }
    }
    return path[T];
}
inline void DebugEdge() {
    for(int i=1;i<=nn;i++)printf("%d ", path[i]);
    puts("");
    puts("✗");
    for (int i = 2; i <= num; i++) printf("%% %d\n", data[i].cap);
    puts("✗");
}
int main() {
    //	freopen("a.in","r",stdin);
    n = read();
    k = read();
    for (int i = 1; i <= n; ++i) {
        a[++nn] = l[i] = read(), a[++nn] = r[i] = read();
        if (l[i] > r[i]) swap(l[i], r[i]);
    }
    sort(a + 1, a + nn + 1);
    nn = unique(a + 1, a + nn + 1) - a - 1;
    add(0, 1, k, 0);
    add(nn, T, inf, 0);
    for (int i = 1; i <= n; ++i) {
        int x = lower_bound(a + 1, a + nn + 1, l[i]) - a;
        int y = lower_bound(a + 1, a + nn + 1, r[i]) - a;
        add(x, y, 1, r[i] - l[i]);
    }
    for (int i = 1; i < nn; ++i) add(i, i + 1, inf, 0);
    DebugEdge();
    while (spfa()) {
        int low = inf, now = T;
        while (path[now]) low = min(low, data[path[now]].cap), now = data[path[now] ^ 1].to;
        printf("➜  ~ %d\n", ans += low * dis[T]);
        printf("INFO ➜ %d\n", low);
        now = T;
        while (path[now]) data[path[now]].cap -= low, data[path[now] ^ 1].cap += low, now = data[path[now] ^ 1].to;
        DebugEdge();
    }
    printf("%d\n", ans);
    return 0;
}