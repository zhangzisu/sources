#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1000010
struct node {
    int son[10];
    std::vector<int> pos;
    int now, max;
    inline node() {
        memset(son, 0, sizeof(son));
        pos.clear();
        now = max = 0;
    }
} trie[MAXN];
int n, tim, ans, len, cnt = 0, root, real;
char buf[MAXN];
inline void insert() {
    int p = root;
    for (int i = 1; i <= len; i++) {
        int &nxt = trie[p].son[buf[i] - 'a'];
        if (!nxt) nxt = ++cnt;
        p = nxt;
        if ((++trie[p].now) > trie[p].max) trie[p].pos.push_back(tim);
        trie[p].max = std::max(trie[p].max, trie[p].now);
    }
}
inline void del() {
    int p = root;
    for (int i = 1; i <= len; i++) {
        int &nxt = trie[p].son[buf[i] - 'a'];
        if (!nxt) return;
        p = nxt;
        --trie[p].now;
    }
}
inline void query() {
    int p = root;
    for (int i = 1; i <= len; i++) {
        int &nxt = trie[p].son[buf[i] - 'a'];
        if (!nxt) return printf("%d\n", ans = -1), void();
        p = nxt;
    }
    if ((int)trie[p].pos.size() < real) return printf("%d\n", ans = -1), void();
    printf("%d\n", ans = trie[p].pos[real - 1]);
}
int main() {
    scanf("%d", &n);
    root = ++cnt;
    tim = 1;
    for (int k; tim <= n; tim++) {
        scanf("%d%s", &k, buf + 1);
        len = strlen(buf + 1);
        if (k == 1) {
            insert();
        } else if (k == 2) {
            del();
        } else {
            if (ans < 0) ans = -ans;
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            real = (1LL * a * ans + b) % c + 1;
            query();
        }
    }
    return 0;
}