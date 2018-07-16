#include <cstdio>
#include <cstring>
#include <queue>
#define MAX_KEY_SIZE 2000000
#define MAX_QUEUE_SIZE 5000000
#define MAX_TEXT_SIZE 2000000
struct trie {
    int son[10], fail, sum;
    inline int &operator[](int index) {
        return son[index];
    }
} ac[MAX_KEY_SIZE];
int root = 1, cnt = 1;
inline void insert(int *x, int len, int val) {
    int p = root;
    for (int i = 1; i <= len; i++) {
        int &y = ac[p][x[i]];
        if (!y) y = ++cnt;
        p = y;
    }
    ac[p].sum += val;
}
std::queue<int> Q;
inline void getFail() {
    Q.push(root);
    while (Q.size()) {
        int p = Q.front();
        Q.pop();
        for (int i = 0; i < 10; i++) {
            if (!ac[p][i]) continue;
            if (p == root) {
                ac[ac[p][i]].fail = root;
            } else {
                int q = ac[p].fail;
                while (q && !ac[q].son[i]) q = ac[q].fail;
                if (q) {
                    ac[ac[p][i]].fail = ac[q][i];
                } else {
                    ac[ac[p][i]].fail = root;
                }
            }
            Q.push(ac[p][i]);
        }
    }
}
int n;
char t[MAX_TEXT_SIZE];
int a[MAX_TEXT_SIZE];
int main() {
    root = cnt = 1;
    scanf("%d", &n);
    while (n--) {
        int x, y;
        scanf("%d", &x);
        for(int i = 1;i <= x;i++)scanf("%d", &a[i]);
        scanf("%d", &y);
        insert(a, x, y);
    }
    getFail();
    scanf("%s", t);
    int ans = 0;
    int p = root;
    for (int i = 0; t[i]; i++) {
        int c = t[i] - '0';
        while (p != root && !ac[p][c]) p = ac[p].fail;
        p = ac[p][c];
        if (!p) p = root;
        int q = p;
        for (; q != root && ac[q].sum >= 0; q = ac[q].fail) {
            ans += ac[q].sum;
        }
    }
    printf("%d\n", ans);
    return 0;
}