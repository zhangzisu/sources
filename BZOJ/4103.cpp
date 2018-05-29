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

int main() {
    scanf("%d%d", &n, &m);
    root[0] = ++cnt;
    return 0;
}