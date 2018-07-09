#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 10
int n, m, k, x, y;
struct path {
    int top[MAXN];
} tmp;
std::vector<path> paths;
int stk[MAXN], lmt[MAXN], max;
void dfs(int x, int t) {
    if (x >= n) {
        if (!t) return;
        memcpy(tmp.top, stk, sizeof(stk));
        paths.push_back(tmp);
        return;
    }
    for (int i = t; i <= std::max(t, lmt[x]); i++) {
        stk[x] = i;
        dfs(x + 1, i);
    }
    if (std::max(t, lmt[x]) == max) return;
    stk[x] = max;
    dfs(x + 1, max);
}

struct node {
    int deep;
    long long v[2];
    inline node() { deep = v[0] = v[1] = 0; }
    inline int getVal(int pos) {
        return (v[pos >> 6] >> (pos & 63)) & 1;
    }
    inline void xorVal(int pos) {
        v[pos >> 6] ^= (1 << (pos & 63));
    }
    inline void setVal(int pos, int val) {
        int tmp = getVal(pos);
        if (tmp != val) xorVal(pos);
    }
    inline int getVal(int x, int y) {
        return getVal(x * m + y);
    }
    inline void xorVal(int x, int y) {
        return xorVal(x * m + y);
    }
    inline void setVal(int x, int y, int val) {
        return setVal(x * m + y, val);
    }
    inline bool judge() { return v[0] || v[1]; }
};
std::queue<node> Q;
void BFS(node x) {
    Q.push(x);
    while (Q.size()) {
        node fr = Q.front();
        Q.pop();
        for (int i = 0; i < (int)paths.size(); i++) {
            node nxt(fr);
            nxt.deep++;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < paths[i].top[j]; k++) {
                    nxt.xorVal(j, k);
                }
            }
            if (fr.deep & 1) {
                if (!nxt.judge()) printf("%d\n", nxt.deep), exit(0);
            }
            Q.push(nxt);
        }
    }
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    node starter;
    while (k--) {
        scanf("%d%d", &x, &y);
        starter.xorVal(x, y);
        lmt[x] = std::max(lmt[x], y);
        max = std::max(max, y);
    }
    max++;
    dfs(0, 0);

    // printf("PATHS : %lu\n", paths.size());
    // for(auto p : paths){
    //     for(int x=0;x<n;x++)printf("%d ", p.top[x]);
    //     puts("");
    // }

    if (!starter.judge()) return puts("0"), 0;
    BFS(starter);
    return 0;
}