#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 1010
#define MAXM 300010
int n, m, q, x[MAXN], root[MAXM * 35], cnt = 0;
struct node {
    int cnt, son[2];
} trie[MAXM * 35];
void insert(int &n, int N, int p, int v) {
    trie[n = ++cnt] = trie[N];
    int x = (v >> p) & 1;
    trie[n].cnt++;
    if (p < 0) return;
    insert(trie[n].son[x], trie[N].son[x], p - 1, v);
}
inline int getNum(int n, int N) {
    return trie[N].cnt - trie[n].cnt;
}
int posL[MAXN], posR[MAXN];
int get(int l, int r, int k, int d) {
    if (d < 0) return 0;
    int all = 0;
    for (int i = l; i <= r; i++) {
        int cur = ((x[i] >> d) & 1) ^ 1;
        all += getNum(trie[posL[i]].son[cur], trie[posR[i]].son[cur]);
    }
    for (int i = l; i <= r; i++) {
        int cur = ((x[i] >> d) & 1) ^ (all < k) ^ 1;
        posL[i] = trie[posL[i]].son[cur];
        posR[i] = trie[posR[i]].son[cur];
    }
    return get(l, r, k - (all >= k ? 0 : all), d - 1) | ((all >= k) << d);
}
void print(int x, int deep = 0) {
    if (!x) return;
    printf("#");
    for (int i = 0; i < deep; i++) putchar(' ');
    printf("id: %d, cnt = %d\n", x, trie[x].cnt);
    print(trie[x].son[0], deep + 2);
    print(trie[x].son[1], deep + 2);
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
        for (int i = x; i <= y; i++) posL[i] = root[l - 1], posR[i] = root[r];
        printf("%d\n", get(x, y, k, 31));
    }
    return 0;
}