#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 2000010
int son[MAXN][26], link[MAXN], len[MAXN], pos[MAXN], size[MAXN];
int pre = 1, cnt = 1;
inline int state(int _len = 0, int _pos = 0) {
    ++cnt;
    memset(son[cnt], 0, sizeof(son[cnt]));
    link[cnt] = 0, len[cnt] = _len, pos[cnt] = _pos;
    return cnt;
}
inline int clone(int pre, int _len = 0) {
    ++cnt;
    memcpy(son[cnt], son[pre], sizeof(son[cnt]));
    link[cnt] = link[pre], pos[cnt] = pos[pre], len[cnt] = _len;
    return cnt;
}
char buf[200010];
inline void insert(int val, int pos) {
    int p = state(len[pre] + 1, pos), q = pre, s;
    pre = cnt, size[p] = 1;
    for (; q && !son[q][val]; q = link[q]) son[q][val] = p;
    if (!q) return link[p] = 1, void();
    if (len[s = son[q][val]] == len[q] + 1) return link[p] = s, void();
    int c = clone(s, len[q] + 1);
    for (; q && son[q][val] == s; q = link[q]) son[q][val] = c;
    link[p] = link[s] = c;
}

std::vector<int> tr[MAXN];

inline void build() {
    for (int i = 2; i <= cnt; i++) {
        tr[link[i]].push_back(i);
    }
    for (int i = 1; i <= cnt; i++)
        std::sort(tr[i].begin(), tr[i].end(), [](int a, int b) {
            return buf[pos[a] + len[link[a]]] < buf[pos[b] + len[link[b]]];
        });
}

int dfn[MAXN], nfd[MAXN], time;
inline void dfs(int x) {
    nfd[dfn[x] = ++time] = x;
    for (auto i : tr[x]) dfs(i), size[x] += size[i];
}
long long val[MAXN];
inline long long sum(int l, int r) { return 1LL * (l + r) * (r - l + 1) / 2; }

int n, q, p, m, g, k;
int main() {
    scanf("%s", buf + 1);
    n = strlen(buf + 1);
    for (int i = n; i; i--) insert(buf[i] - 'a', i);
    build(), dfs(1);
    for (int i = 1; i <= cnt; i++)
        val[i] = val[i - 1] + sum(len[link[nfd[i]]] + 1, len[nfd[i]]);
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &p, &m);
        k = 1LL * p * g % m + 1;
        printf("FUCKING %d\n", k);
        int res = std::lower_bound(val + 1, val + cnt + 1, k) - val;
        printf("%d is fucked all the day.", res);
        register int l = len[link[nfd[res]]] + 1, r = len[nfd[res]], ans = -1;
        printf("%d is fucking %d\n", l, r);
        k -= val[res - 1];
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (1LL * size[nfd[res]] * sum(len[link[nfd[res]]] + 1, mid) >= k)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        k -= 1LL * size[nfd[res]] * sum(len[link[nfd[res]]] + 1, ans - 1);
        k = (k - 1) % ans + 1;
        ans = buf[pos[res] + k - 1];
        printf("%c\n", ans);
        g += ans;
    }
}