#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#define N 100005
using namespace std;
int n, m, L, x, y, z, id[N], L2[N], p[N];
int first[N], ddd[N << 1], frm[N << 1], to[N << 1], val[N << 1], l;
int q[N], sid[N], st[N], h, dis[N];
bool fl[N], inQ[N];
struct T {
    int l, r;
};
bool operator<(T p, T b) { return p.l > b.l; }
priority_queue<T> S;
void link(int x, int y, int z) {
    frm[++l] = x;
    to[l] = y;
    val[l] = z;
    ddd[l] = first[x];
    first[x] = l;
}
void SPFA(int s, int t, int k) {
    int head = 0, tail = 1;
    q[1] = s;
    while (head != tail) {
        head %= N;
        int x = q[++head];
        inQ[x] = 0;
        for (int i = first[x]; i; i = ddd[i])
            if (i != k) {
                int y = to[i];
                if (id[y] >= id[t]) {
                    if (!fl[y])
                        fl[y] = 1, st[++h] = y, sid[y] = dis[x] + val[i];
                    else
                        sid[y] = min(sid[y], dis[x] + val[i]);
                } else if (dis[y] > dis[x] + val[i]) {
                    dis[y] = dis[x] + val[i];
                    if (!inQ[y])
                        inQ[y] = 1, tail %= N, q[++tail] = y;
                }
            }
    }
    for (int t; h; h--) t = st[h], S.push((T){sid[t] + L2[t], id[t]}), fl[t] = 0;
}
int main() {
    scanf("%d%d%d", &n, &m, &L);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &x, &y, &z), link(x, y, z);
    id[1] = 1;
    for (int i = 1; i <= L; i++)
        scanf("%d", &p[i]), id[to[p[i]]] = i + 1;
    for (int i = L; i >= 1; i--)
        printf("DDD #1 : %d\n", L2[frm[p[i]]] = L2[to[p[i]]] + val[p[i]]);
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0;
    for (int i = 1; i <= L; i++) {
        int u = frm[p[i]], v = to[p[i]];
        for (SPFA(u, v, p[i]); !S.empty() && S.top().r < id[v]; S.pop())
            ;
        puts("DDD #2");
        for(int i = 1;i <= n;i++)printf("%d ", dis[i]);
        puts("");
        puts("DDD #3");
        for(int i = 1;i <= n;i++)printf("%d ", sid[i]);
        puts("");
        printf("%d\n", S.empty() ? -1 : S.top().l);
        dis[v] = dis[u] + val[p[i]];
    }
    return 0;
}