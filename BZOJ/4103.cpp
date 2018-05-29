#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MAXM 300010
int n, m, q, x[MAXN], root[MAXM * 35], cnt = 0;
struct node {
    int cnt, son[2];
} trie[MAXN * 35];
void insert(int &n, int N, int p, int v) {
    if (p < 0) return;
    trie[n = ++cnt] = trie[N];
    int x = (v >> p) & 1;
    insert(trie[n].son[x], trie[N].son[x], p - 1, v);
    trie[n].cnt++;
}
inline int getNum(int n, int N) {
    return trie[N].cnt - trie[n].cnt;
}
int count(int n, int N, int p, int v, int mask) {
    if (p < 0) return getNum(n, N);
    int x = ((v >> p) & 1);
    int y = ((mask >> p) & 1);
    if (x) return count(trie[n].son[x ^ y], trie[N].son[x ^ y], p - 1, v, mask);
    return count(trie[n].son[y], trie[N].son[y], p - 1, v, mask) + getNum(trie[n].son[!y], trie[N].son[!y]);
}
inline int get(int x, int y, int l, int r, int mid) {
    int ret = 0;
    for (int i = x; i <= y; i++) {
        ret += count(root[l - 1], root[r], 31, mid, ::x[i]);
    }
    return ret;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
    for (int i = 1, y; i <= m; i++) {
        scanf("%d", &y);
        insert(root[i], root[i - 1], 31, y);
    }
    scanf("%d", &q);
    while (q--) {
        int x, y, l, r, k;
        scanf("%d%d%d%d%d", &x, &y, &l, &r, &k);
        int L = 0, R = (~0u) >> 2, ans = -1;
        while (L <= R) {
            int mid = (0LL + L + R) >> 1;
            if (get(x, y, l, r, mid) >= k) {
                ans = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}