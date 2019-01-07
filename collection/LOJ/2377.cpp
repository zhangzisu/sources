#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define MAXN 1000010
struct node {
    int son[26], link, len;
    inline node() {
        memset(son, 0, sizeof(son));
        link = len = 0;
    }
    inline node(node &arg) {
        memcpy(son, arg.son, sizeof(son));
        link = arg.link;
        len = arg.len;
    }
    inline int &operator[](int index) { return son[index]; }
} sam[MAXN];
int cnt = 1, last = 1, size[MAXN], n;
inline void insert(int x) {
    int now = ++cnt;
    sam[now].len = sam[last].len + 1;
    size[now] = 1;
    int pre = last;
    last = now;
    for (; pre && !sam[pre][x]; pre = sam[pre].link) sam[pre][x] = now;
    if (!pre) return sam[now].link = 1, void();
    int son = sam[pre][x];
    if (sam[pre].len + 1 == sam[son].len) return sam[now].link = son, void();
    int clone = ++cnt;
    sam[clone] = node(sam[son]);
    sam[clone].len = sam[pre].len + 1;
    for (; pre && sam[pre][x] == son; pre = sam[pre].link) sam[pre][x] = clone;
    sam[now].link = sam[son].link = clone;
}
char buf[MAXN];
long long ans = 0;
std::vector<int> V[MAXN];
void dfs(int x) {
    for (auto i : V[x]) {
        dfs(i);
        ans -= 1LL * size[x] * size[i] * sam[x].len * 2;
        size[x] += size[i];
    }
}

int main() {
    scanf("%s", buf + 1);
    n = strlen(buf + 1);
    std::reverse(buf + 1, buf + n + 1);
    for (int i = 1; i <= n; i++) insert(buf[i] - 'a');
    for (int i = 1; i <= n; i++) ans += 1LL * i * (n - 1);
    for (int i = 2; i <= cnt; i++) V[sam[i].link].push_back(i);
    dfs(1);
    printf("%lld\n", ans);
    return 0;
}