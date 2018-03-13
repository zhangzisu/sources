#include <bits/stdc++.h>
#define ll long long
#define mid (l + r >> 1)
#define N 200009
using namespace std;
char s[N];
int m, len, last = 1, pos[N << 1], fail[N << 1], st[N << 1];
ll p, mod, G;
bool cmp(int x, int y) {
    return s[pos[x] + st[fail[x]]] > s[pos[y] + st[fail[y]]];
}
struct sam {
    int son[N << 1][26], cnt, size[N << 1];
    int first[N << 1], number, dfn[N << 1], dfsclk, ps[N << 1];
    ll sum[N << 1];
    vector<int> tr[N << 1];
    struct edge {
        int to, next;
    } e[N << 1];
    void add(int x, int y) {
        e[++number] = (edge){y, first[x]};
        first[x] = number;
    }
    void csh() {
        cnt = 1;
    }
    void get_fa() {
        for (int i = 2; i <= cnt; i++)
            tr[fail[i]].push_back(i);
        for (int i = 1; i <= cnt; i++) sort(tr[i].begin(), tr[i].end(), cmp);
        for (int i = 1; i <= cnt; i++)
            for (int j = 0; j < (int)tr[i].size(); j++) add(i, tr[i][j]);
    }
    int extend(int k, int p, int c) {
        int np = ++cnt;
        st[np] = st[p] + 1, pos[np] = k, size[np] = 1;
        while (!son[p][c] && p) son[p][c] = np, p = fail[p];
        if (!p)
            fail[np] = 1;
        else {
            int q = son[p][c];
            if (st[q] == st[p] + 1)
                fail[np] = q;
            else {
                int nq = ++cnt;
                st[nq] = st[p] + 1, pos[nq] = pos[q];
                memcpy(son[nq], son[q], sizeof(son[q]));
                fail[nq] = fail[q];
                fail[q] = fail[np] = nq;
                while (son[p][c] == q) son[p][c] = nq, p = fail[p];
            }
        }
        return np;
    }
    ll get(ll x, ll y) {
        return (ll)(x + y) * (y - x + 1) / 2;
    }
    void dfs(int x) {
        ps[dfn[x] = ++dfsclk] = x;
        for (int i = first[x]; i; i = e[i].next) {
            dfs(e[i].to);
            size[x] += size[e[i].to];
        }
    }
    void Get() {
        for (int i = 1; i <= cnt; i++)
            sum[i] = sum[i - 1] + (ll)size[ps[i]] * get(st[fail[ps[i]]] + 1, st[ps[i]]);
    }
    void work(ll x) {
        printf("FUCKING %lld\n", x);
        int l = 1, r = cnt, ret = 0, Ret = 0;
        while (l <= r) {
            if (sum[mid] >= x)
                ret = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        printf("%d is fucked all the day.", ret);
        //cerr<<ps[ret]<<' '<<size[ps[ret]]<<endl;
        l = st[fail[ps[ret]]] + 1, r = st[ps[ret]];
        printf("%d fucked %d!\n", l, r);
        x -= sum[ret - 1];
        //cerr<<x<<' '<<l<<' '<<r<<endl;
        while (l <= r) {
            if ((ll)size[ps[ret]] * get(st[fail[ps[ret]]] + 1, mid) >= x)
                Ret = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        x -= (ll)size[ps[ret]] * get(st[fail[ps[ret]]] + 1, Ret - 1);
        x = (x - 1) % Ret + 1;
        putchar(s[pos[ps[ret]] + x - 1]);
        puts("");
        G += s[pos[ps[ret]] + x - 1];
    }
} Sam;
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    //scanf("%s",s+1);
    cin >> s + 1;
    len = strlen(s + 1);
    Sam.csh();
    for (int i = len; i; i--) last = Sam.extend(i, last, s[i] - 'a');
    Sam.get_fa();
    Sam.dfs(1);
    Sam.Get();
    cin >> m;
    while (m--) {
        cin >> p >> mod;
        ll x = p * G % mod + 1;
        //	ll x=p;
        Sam.work(x);
    }
    return 0;
}