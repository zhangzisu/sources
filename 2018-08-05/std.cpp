#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define P pair<int, int>
#define fir first
#define sec second
using namespace std;
const int N = 100000 * 64 + 5;
const int _N = 100005;
const int M = 3200;
P Q[10];
int cnt, head[N], n, p[M], a[_N], pos, prime[1000], mm[_N], Cnt, size[N << 1], Head[N << 1], top, tot, vis[N], dfn[N], sc, low[N], bel_id, q[N], sum, cMax, Max;
map<int, int> mp;
typedef long long ll;
struct node {
    int to, next;
} num[N << 1], e[N << 1];
int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
void add(int x, int y) {
    num[++cnt].to = y;
    num[cnt].next = head[x];
    head[x] = cnt;
}
void Add(int x, int y) {
    e[++Cnt].to = y;
    e[Cnt].next = Head[x];
    Head[x] = Cnt;
}
void shai() {
    for (int i = 2; i < M; i++) {
        if (!p[i]) prime[++tot] = i;
        for (int j = 1; j <= tot && (ll)prime[j] * i < M; j++) {
            p[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
void dvd(int x) {
    for (int i = 1; i <= tot; i++)
        if (x % prime[i] == 0) {
            int cc = 0;
            while (x % prime[i] == 0) x /= prime[i], cc++;
            Q[++top] = P(prime[i], cc);
        }
    if (x > 1) Q[++top] = P(x, 1);
}
void ins(int x, int val) {
    if (!mp.count(val)) mp[val] = ++bel_id;
    add(mp[val], x);
    add(x, mp[val]);
}
void build() {
    mp.clear();
    for (int i = 1; i <= n; i++) {
        top = 0;
        dvd(a[i]);
        for (int j = 1; j <= top; j++)
            if (Q[j].sec >= 2) ins(i, Q[j].fir * Q[j].fir);
        for (int j = 1; j <= top; j++)
            for (int k = j + 1; k <= top; k++)
                ins(i, Q[j].fir * Q[k].fir);
    }
}
void dfs(int x) {
    vis[x] = 1;
    sum += size[x];
    for (int i = head[x]; i; i = num[i].next)
        if (!vis[num[i].to]) dfs(num[i].to);
}
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++sc;
    q[++top] = x;
    for (int i = head[x]; i; i = num[i].next)
        if (num[i].to != fa)
            if (!dfn[num[i].to]) {
                tarjan(num[i].to, x);
                low[x] = min(low[x], low[num[i].to]);
                if (dfn[x] <= low[num[i].to]) {
                    int v = -1;
                    ++bel_id;
                    while (v != num[i].to) v = q[top--], Add(bel_id, v);
                    Add(x, bel_id);
                }
            } else
                low[x] = min(low[x], dfn[num[i].to]);
}
void dfs2(int x, int fa) {
    if (x <= n) mm[x] = 0;
    for (int i = Head[x]; i; i = e[i].next)
        if (e[i].to != fa) {
            fprintf(stderr, "\t%d %d\n", x, e[i].to);
            dfs2(e[i].to, x);
            size[x] += size[e[i].to];
            if (x <= n) mm[x] = max(mm[x], size[e[i].to]);
        }
    if (x > n) return;
    mm[x] = max(mm[x], sum - size[x]);
    Max = min(Max, mm[x]);
}
void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), size[i] = 1;
    bel_id = n;
    build();
    Max = cMax = sc = 0;
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            sum = 0;
            dfs(i);
            if (sum > Max)
                cMax = Max, Max = sum, pos = i;
            else
                cMax = max(cMax, sum);
        }
    for (int i = 1; i <= bel_id; i++) vis[i] = dfn[i] = 0;
    sum = Max;
    fprintf(stderr, "> %d %d %d %d\n", Max, cMax, pos, Max);
    tarjan(pos, -1);
    dfs2(pos, -1);
    fprintf(stderr, "> %d %d %d %d\n", Max, cMax, pos, Max);
    printf("%d\n", max(Max, cMax));
    for (int i = 1; i <= bel_id; i++) size[i] = Head[i] = head[i] = 0;
}
int main() {
    shai();
    int T;
    scanf("%d", &T);
    while (T--) {
        cnt = Cnt = top = 0;
        solve();
    }
    return 0;
}