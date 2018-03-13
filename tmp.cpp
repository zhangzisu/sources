#include <bits/stdc++.h>
#define ll long long
#define N 1000005
using namespace std;

int n;
char s[N];
struct sam {
    int cnt, last, ch[N][26], len[N], fa[N], fst[N], nxt[N], sz[N];
    ll ans;
    sam() { cnt = last = 1; }
    void ins(int c) {
        int p = last, np = last = ++cnt;
        len[np] = len[p] + 1;
        sz[cnt] = 1;
        for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
        if (!p)
            fa[np] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q])
                fa[np] = q;
            else {
                int nq = ++cnt;
                len[nq] = len[p] + 1;
                memcpy(ch[nq], ch[q], sizeof(ch[q]));
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                for (; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
            }
        }
    }
    void dfs(int x) {
        int y;
        for (y = fst[x]; y; y = nxt[y]) {
            dfs(y);
            ans += (ll)len[x] * sz[x] * sz[y];
            sz[x] += sz[y];
        }
    }
    void solve() {
        int i;
        for (i = 2; i <= cnt; i++) {
             printf("link[%d]=%d-%d\n",i,fa[i],sz[i]);
            nxt[i] = fst[fa[i]];
            fst[fa[i]] = i;
        }
        dfs(1);
        printf("%d\n", ans);
        printf("%lld\n", ((ll)n * (n - 1) * (n + 1) >> 1) - (ans << 1));
    }
} sam;
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int i;
    for (i = n; i; i--) sam.ins(s[i] - 'a');
    sam.solve();
    return 0;
}