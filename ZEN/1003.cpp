#include <algorithm>
#include <cstdio>
#include <cstring>
#define MAXN 50010
#define BLOCK 223
int val[MAXN], add[MAXN], srt[MAXN], n;
inline int bel(int x) { return x / BLOCK; }
inline void slove(int l) {
    l = l * BLOCK;
    memcpy(srt + l, val + l, sizeof(int) * BLOCK);
    std::sort(srt + l, srt + l + BLOCK);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (int i = 1; i <= n; i++) {
        int op, l, r, c;
        scanf("%d%d%d%d", &op, &l, &r, &c);
        if (op == 0) {
            if (bel(l) == bel(r)) {
                for (int i = l; i <= r; i++) val[i] += c;
                slove(bel(l));
            } else {
                int L = bel(l), R = bel(r);
                for (int i = l; bel(i) == L; i++) val[i] += c;
                slove(L);
                for (int i = r; bel(i) == R; i--) val[i] += c;
                slove(R);
                for (int i = L + 1; i < R; i++) add[i] += c;
            }
        } else {
            c *= c;
            int ans = 0;
            if (bel(l) == bel(r)) {
                for (int i = l; i <= r; i++) ans += val[i] + add[bel(l)] < c;
            } else {
                int L = bel(l), R = bel(r);
                for (int i = l; bel(i) == L; i++) ans += val[i] + add[L] < c;
                for (int i = r; bel(i) == R; i--) ans += val[i] + add[R] < c;
                for (int i = L + 1; i < R; i++)
                    ans += std::lower_bound(srt + i * BLOCK,
                                            srt + (i + 1) * BLOCK, c - add[i]) -
                           (srt + i * BLOCK);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}