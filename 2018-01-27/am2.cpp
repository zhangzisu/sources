#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define SIGMA 26
#define MAXS 100010
#define MAXN 100010
struct state {
    int son[SIGMA], link, len, pos;
    inline state(int len = 0, int pos = 0) {
        memset(son, 0, sizeof(son));
        this->link = 0;
        this->len = len;
    }
    inline state(state &x, int len) {
        memcpy(son, x.son, sizeof(son));
        this->link = x.link;
        this->len = len;
    }
    inline int &operator[](int index) { return son[index]; }
} sam[MAXS << 1];
int root = 1, pre = 1, cur = 1;
inline void extend(int x, int pos) {
    int p, q, s, c;
    sam[p = ++cur] = state(sam[q = pre].len + 1, pos);
    pre = p;
    for (; q && !sam[q][x]; q = sam[q].link) sam[q][x] = p;
    if (!q) return void(sam[p].link = root);
    s = sam[q][x];
    if (sam[q].len + 1 == sam[s].len) return void(sam[p].link = s);
    sam[c = ++cur] = state(sam[s], sam[q].len + 1);
    for (; q && sam[q][x] == s; q = sam[q].link) sam[q][x] = c;
    sam[s].link = sam[p].link = c;
}
int n, sl, flag;
std::string buf;
std::deque<std::pair<int, int>> S;  // pair<int=>val, int=>pos>
std::vector<std::pair<std::pair<int, int>, std::string>> Q;
int head[MAXS << 1], to[MAXS << 1], next[MAXS << 1], tot;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> n;
    while (n--) {
        std::cin >> buf;
        sl = buf.size() - 1;
        if (buf[0] == '+') {
            if (flag) {
                // Reveral
                for (int i = sl; i; i--)
                    S.push_front(std::make_pair(
                        buf[i] - 'a', S.empty() ? 0 : S.begin()->second - 1));
            } else {
                for (int i = 1; i <= sl; i++)
                    S.push_back(std::make_pair(
                        buf[i] - 'a', S.empty() ? 0 : S.rbegin()->second + 1));
            }
        } else if (buf[0] == '?') {
            if (flag) {
                auto pos =
                    std::make_pair(S.begin()->second, S.rbegin()->second);
                std::string query = buf.substr(1);
                query.reserve();
                Q.push_back(std::make_pair(pos, query));
            } else {
                auto pos =
                    std::make_pair(S.begin()->second, S.rbegin()->second);
                std::string query = buf.substr(1);
                Q.push_back(std::make_pair(pos, query));
            }
        } else {
            flag = !flag;
        }
    }
    for (auto i : S) printf("%3c", i.first + 'a');
    puts("");
    for (auto i : S) printf("%3d", i.second);
    puts("");
    return 0;
}