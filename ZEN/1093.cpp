#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#define _B 65536
char _1[_B], *_3 = _1 + _B;
inline char _getchar() { if (_3 == _1 + _B)fread(_1, 1, _B, stdin), _3 = _1; return *_3++; }
inline int $() {
	register int __ = 0; register char _ = _getchar(); while (!isdigit(_))_ = _getchar();
	for (; isdigit(_); _ = _getchar())__ = ((__ << 3) + (__ << 1)) + (_ ^ 48);
	return __;
}

#define MAXN 100010
#define BLOCK 840

int n, m, q, opt, x, k, maxd;
int head[MAXN], to[MAXN], next[MAXN], val[MAXN], tot = 0;
int deep[MAXN], size[MAXN];
inline void $(int u, int v, int w) {
    next[tot] = head[u], to[tot] = v, val[tot] = w, head[u] = tot++;
}
int dfn[MAXN], pos[MAXN], time = 0;
void dfs(int x) {
    size[x] = 1;
    pos[dfn[x] = ++time] = x;
    maxd = std::max(maxd, deep[x]);
    for (int i = head[x]; ~i; i = next[i]) {
        deep[to[i]] = deep[x] + val[i];
        dfs(to[i]);
        size[x] += size[to[i]];
    }
}

int tag[MAXN], orz[MAXN], srt[MAXN], end[MAXN], bel[MAXN];
inline int _b(int x) { return (x - 1) / BLOCK + 1; }
inline int _s(int block) { return (block - 1) * BLOCK + 1; }
inline int _e(int block) { return _s(block + 1) - 1; }

short f[121][2000010];

int main() {
    n = $(), q = $(); $();
    memset(head, -1, sizeof(head));
    register int i, l, r, ans, mid, tmp, L, R, cnt, LL, RR;
    for (i = 2; i <= n; i++) {
        l = $(); r = $();
        $(l, i, r);
    }
    dfs(1);
    m = _b(n);
    for(i = 1;i <= n;i++){
        end[i] = _e(i);
        srt[i] = _s(i);
        f[bel[i] = _b(i)][deep[pos[i]]]++;
        orz[i] = deep[pos[i]];
    }
    for(i = 1;i <= m;i++){
        for(l = 1;l < 2000010;l++){
            f[i][l] += f[i][l - 1];
        }
    }

    while (q--) {
        opt = $(); x = $(); k = $();
        if (opt == 1) {
            if (size[x] < k) {
                puts("-1");
                continue;
            }
            ans = -1;
            LL = dfn[x], RR = LL + size[x] - 1;
            l = deep[x], r = maxd;
            L = bel[LL], R = bel[RR];
            while (l <= r) {
                mid = (l + r) >> 1;
                cnt = 0;
                for (i = L + 1; i < R; i++)
                    if(mid >= tag[i])cnt += f[i][mid - tag[i]];
                if (L == R) {
                    tmp = mid - tag[L];
                    for (i = LL; i <= RR; i++)
                        cnt += (orz[i] <= tmp);
                } else {
                    tmp = mid - tag[L];
                    for (i = LL; i <= end[L]; i++)
                        cnt += (orz[i] <= tmp);
                    tmp = mid - tag[R];
                    for (i = srt[R]; i <= RR; i++)
                        cnt += (orz[i] <= tmp);
                }
                if (cnt >= k)
                    ans = mid, r = mid - 1;
                else
                    l = mid + 1;
            }
            printf("%d\n", ans);
        } else {
            l = dfn[x], r = dfn[x] + size[x] - 1;
            L = bel[l], R = bel[r];
            assert(L); assert(R);
            for (i = L + 1; i < R; i++) tag[i] += k;
            if (L == R) {
                for (i = l; i <= r; i++) {
                    for(LL = orz[i];LL < orz[i] + k;LL++)f[L][LL]--;
                    orz[i] += k;
                }
            } else {
                for (i = l; i <= end[L]; i++) {
                    for(LL = orz[i];LL < orz[i] + k;LL++)f[L][LL]--;
                    orz[i] += k;
                }
                for (i = srt[R]; i <= r; i++) {
                    for(LL = orz[i];LL < orz[i] + k;LL++)f[R][LL]--;
                    orz[i] += k;
                }
            }
            maxd += k;
        }
    }
    return 0;
}