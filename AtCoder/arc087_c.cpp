#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
struct trie {
    trie *son[2];
    inline trie() { son[0] = son[1] = NULL; }
} * root;
int n, l, ans = 0;
char buf[100010];
inline void Insert() {
    trie *p = root;
    for (int i = 0; buf[i]; i++) {
        const int x = buf[i] - '0';
        if (p->son[x])
            p = p->son[x];
        else
            p = (p->son[x] = new trie());
    }
}
void DFS(trie *node, int d) {
    if (!node || (!node->son[0] && !node->son[1])) return;
    if (node->son[0] && node->son[1]) {
        DFS(node->son[0], d + 1);
        DFS(node->son[1], d + 1);
        return;
    }
    int now = l - d, cnt = 1;
    while (now && !(now & 1)) cnt++, now >>= 1;
    ans ^= cnt;
    if (node->son[0])
        DFS(node->son[0], d + 1);
    else
        DFS(node->son[1], d + 1);
}
int main() {
    scanf("%d%d", &n, &l);
    root = new trie();
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf);
        Insert();
    }
    DFS(root, 0);
    puts(ans ? "Alice" : "Bob");
    return 0;
}